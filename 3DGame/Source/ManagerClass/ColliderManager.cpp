#include "ColliderManager.h"

//他ファイルでの呼び出し用のインスタンスを生成
ColliderManager* ColliderManager::instance = new ColliderManager();

//コンストラクタ
ColliderManager::ColliderManager() {}

//デストラクタ
ColliderManager::~ColliderManager() {}

//インスタンスの生成処理
void ColliderManager::CreateInstance() {
    if (instance == nullptr) {
        instance = new ColliderManager();
    }
}

//インスタンスの削除処理
void ColliderManager::DeleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

//リスト追加処理
void ColliderManager::AddList(ObjectCollider* collider_) {
    objectList.emplace_back(collider_);
}

//リスト内のコライダーをチェック
void ColliderManager::CheckList() {

    for (int i = 0; i < static_cast<int>(objectList.size()) - 1; i++) {
        for (int j = i + 1; j < static_cast<int>(objectList.size()); j++) {
            //対象の持つコライダーを検索
            for (CubeCollider* collider01 : objectList[i]->getCubeColliders()) {

                //相手の持つコライダーを検索
                for (CubeCollider* collider02 : objectList[j]->getCubeColliders()) {

                    CheckCollider(collider01, collider02, i, j);
                }
                //相手の持つコライダーを検索
                for (SphereCollider* collider02 : objectList[j]->getSphereColliders()) {

                    CheckCollider(collider01, collider02, i, j);
                }
            }
            for (SphereCollider* collider01 : objectList[j]->getSphereColliders()) {
                //相手の持つコライダーを検索
                for (CubeCollider* collider02 : objectList[j]->getCubeColliders()) {

                    CheckCollider(collider02, collider01, i, j);
                }
            }
        }
        
    }
}

//Colider同士の判定検索
void ColliderManager::CheckCollider(CubeCollider* collider_01, CubeCollider* collider_02, int object_01_num, int object_02_num) {
    //あたり判定が処理対象なら判定処理を行
    if (collider_01->IsActive() && collider_02->IsActive()) {

        //当たり判定を行い当たっていれば
        if (CheckOBBToOBB(*collider_01, *collider_02)) {
            //各オブジェクトが持つ衝突時の処理を実行
            objectList[object_01_num]->OnCollision(*objectList[object_02_num], collider_02->getType());
            objectList[object_02_num]->OnCollision(*objectList[object_01_num], collider_01->getType());
        }
        else {
            collider_01->Update();
            collider_02->Update();
        }
    }
}

//Colider同士の判定検索
void ColliderManager::CheckCollider(CubeCollider* cube_collider, SphereCollider* sphere_collider, int cube_object_num, int sphere_object_num) {
    //あたり判定が処理対象なら判定処理を行う
    if (cube_collider->IsActive() && sphere_collider->IsActive()) {

        //当たり判定を行い当たっていれば
        if (CheckOBBToSphere(*cube_collider, *sphere_collider)) {
            //各オブジェクトが持つ衝突時の処理を実行
            objectList[cube_object_num]->OnCollision(*objectList[sphere_object_num], sphere_collider->getType());
            objectList[sphere_object_num]->OnCollision(*objectList[cube_object_num], cube_collider->getType());
        }
        else {
            cube_collider->Update();
            sphere_collider->Update();
        }
    }
}

//OBBと球の当たり判定処理
bool ColliderManager::CheckOBBToSphere(const CubeCollider& cube_collider, const SphereCollider& sphere_collider) {
    Vector3 vec = Vector3::ZERO;

    float length[directionValue] = { cube_collider.getLength().x, cube_collider.getLength().y, cube_collider.getLength().z };

    for (int i = 0; i < directionValue; i++) {

        Vector3 direction = sphere_collider.getPosition() - cube_collider.getPosition();
        float dot = Vector3::Dot(direction, cube_collider.getDirectoin(i)) / length[i];

        dot = fabsf(dot);
        if (dot > 1) {
            //立方体化の面からの距離を加算
            vec +=  cube_collider.getDirectoin(i) * (1 - dot) * length[i];
        }
    }
    return vec.getSize() <= sphere_collider.getRadius();
}

//分離軸に投影された軸成分から投影線分nの長さを算出
float ColliderManager::GetShadowLineLength(Vector3& sep_, Vector3& len_01, Vector3& len_02, Vector3 len_03) {
    Vector3 normSep = sep_.Normalized();
    float length01 = fabsf(Vector3::Dot(normSep, len_01));
    float length02 = fabsf(Vector3::Dot(normSep, len_02));
    //存在しない場合に処理を省くため、条件式にしている
    float length03 = (len_03 == Vector3::ZERO) ? 0 : GetAbsoluteFloat(Vector3::Dot(normSep, len_03));

    return length01 + length02 + length03;
}

//内積で分離軸の有無を判定
bool ColliderManager::CheckDotOBB(Vector3 dir_, Vector3 len_01, Vector3 len_02, Vector3 len_03, Vector3 len_04, 
    Vector3 ingerval_) {

    float collider01Line = len_01.getSize();
    float collider02Line = GetShadowLineLength(dir_, len_02, len_03, len_04);
    float length = fabsf(Vector3::Dot(ingerval_, dir_));
    if (length > collider01Line + collider02Line)
        return false;

    return true;
}

//内積で分離軸の有無を判定
bool ColliderManager::CheckCrossOBB(Vector3 dir_01, Vector3 dir_02, Vector3 len_01, Vector3 len_02, Vector3 len_03, 
    Vector3 Len_04, Vector3 interval_) {

    Vector3 cross = Vector3::Cross(dir_01, dir_02);
    float length01 = GetShadowLineLength(cross, len_01, len_02);
    float length02 = GetShadowLineLength(cross, len_03, Len_04);
    float L = fabsf(Vector3::Dot(interval_, cross));
    if ((L > length01 + length02))
        return false;//衝突してない

    return true;
}

//OBB同士の足り判定
bool ColliderManager::CheckOBBToOBB(const CubeCollider& c_c_01, const CubeCollider& c_c_02) {
    //各方向ベクトルの確保
    //(n***:標準化方向ベクトル)
    Vector3 cC01Dir01 = c_c_01.getDirectoin(0);
    Vector3 cC01Dir02 = c_c_01.getDirectoin(1);
    Vector3 cC01Dir03 = c_c_01.getDirectoin(2);
    Vector3 cC02Dir01 = c_c_02.getDirectoin(0);
    Vector3 cC02Dir02 = c_c_02.getDirectoin(1);
    Vector3 cC02Dir03 = c_c_02.getDirectoin(2);

    //分離軸を算出
    Vector3 cC01Len01 = cC01Dir01 * c_c_01.getLength().x;
    Vector3 cC01Len02 = cC01Dir02 * c_c_01.getLength().y;
    Vector3 cC01Len03 = cC01Dir03 * c_c_01.getLength().z;
    Vector3 cC02Len01 = cC02Dir01 * c_c_02.getLength().x;
    Vector3 cC02Len02 = cC02Dir02 * c_c_02.getLength().y;
    Vector3 cC02Len03 = cC02Dir03 * c_c_02.getLength().z;

    //中心点間の距離
    Vector3 interval = c_c_01.getPosition() - c_c_02.getPosition();

    //分離軸が発生したら衝突してないのでfalseを返し、発生してなければ他の分離軸を検索

    //分離軸①
    if (!CheckDotOBB(cC01Dir01, cC01Len01, cC02Len01, cC02Len02, cC02Len03, interval))
        return false;

    //分離軸②
    if (!CheckDotOBB(cC01Dir02, cC01Len02, cC02Len01, cC02Len02, cC02Len03, interval))
        return false;

    //分離軸③
    if (!CheckDotOBB(cC01Dir03, cC01Len03, cC02Len01, cC02Len02, cC02Len03, interval))
        return false;

    //分離軸④
    if (!CheckDotOBB(cC02Dir01, cC02Len01, cC01Len01, cC01Len02, cC01Len03, interval))
        return false;

    //分離軸⑤
    if (!CheckDotOBB(cC02Dir02, cC02Len02, cC01Len01, cC01Len02, cC01Len03, interval))
        return false;

    //分離軸⑥
    if (!CheckDotOBB(cC02Dir03, cC02Len03, cC01Len01, cC01Len02, cC01Len03, interval))
        return false;

    //分離軸⑦
    if (!CheckCrossOBB(cC01Dir01, cC02Dir01, cC01Len02, cC01Len03, cC02Len02, cC02Len03, interval))
        return false;

    //分離軸⑧
    if (!CheckCrossOBB(cC01Dir01, cC02Dir02, cC01Len02, cC01Len03, cC02Len01, cC02Len03, interval))
        return false;

    //分離軸⑨
    if (!CheckCrossOBB(cC01Dir01, cC02Dir03, cC01Len02, cC01Len03, cC02Len01, cC02Len02, interval))
        return false;

    //分離軸⑩
    if (!CheckCrossOBB(cC01Dir02, cC02Dir01, cC01Len01, cC01Len03, cC02Len02, cC02Len03, interval))
        return false;

    //分離軸⑪
    if (!CheckCrossOBB(cC01Dir02, cC02Dir02, cC01Len01, cC01Len03, cC02Len01, cC02Len03, interval))
        return false;

    //分離軸⑫
    if (!CheckCrossOBB(cC01Dir02, cC02Dir03, cC01Len01, cC01Len03, cC02Len01, cC02Len02, interval))
        return false;

    //分離軸⑬
    if (!CheckCrossOBB(cC01Dir03, cC02Dir01, cC01Len01, cC01Len02, cC02Len02, cC02Len03, interval))
        return false;

    //分離軸⑭
    if (!CheckCrossOBB(cC01Dir03, cC02Dir02, cC01Len01, cC01Len02, cC02Len01, cC02Len03, interval))
        return false;

    //分離軸⑮
    if (!CheckCrossOBB(cC01Dir03, cC02Dir03, cC01Len01, cC01Len02, cC02Len01, cC02Len02, interval))
        return false;

    return true;
}