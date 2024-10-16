#pragma once
#include <vector>
#include "..\Math\MathMethod.h"
#include "..\Collider\ObjectCollider.h"
#include "..\Collider\CubeCollider.h"
#include "..\Collider\SphereCollider.h"

//当たり判定処理クラス
class ColliderManager {
	//メンバ関数
public:
	//デストラクタ
	~ColliderManager();

	//アクセサ

	//インスタンスを返す
	static ColliderManager* getInstance() { return instance; }

	//登録処理
	void AddList(ObjectCollider* collider_);

	//インスタンスの生成処理
	static void CreateInstance();
	//インスタンスの削除処理
	static void DeleteInstance();
	//登録された当たり判定を検索
	void CheckList() ;
private:
	//OBB同士での当たり判定処理
	bool CheckOBBToOBB(const CubeCollider& collider_01, const CubeCollider& collider_02);
	//OBBと球での当たり判定
	bool CheckOBBToSphere(const CubeCollider& cube_collider, const SphereCollider& sphere_collider);
	//Colider同士の判定検索
	void CheckCollider(CubeCollider* collider_01, CubeCollider* collider_02, int object_01_num, int object_02_num);
	//Colider同士の判定検索
	void CheckCollider(CubeCollider* cube_collider, SphereCollider* sphere_collider, int cube_object_num, int sphere_object_num);
	//正射影での判定処理
    static float GetShadowLineLength(Vector3& sep_, Vector3& len_01, Vector3& len_02, Vector3 len_03 = Vector3::ZERO);
	//内積を使った分離軸判定
	static bool CheckDotOBB(Vector3 dir_, Vector3 len_01, Vector3 len_02, Vector3 len_03, Vector3 len_04, Vector3 ingerval_);
	//外積を使った分離軸判定
	static bool CheckCrossOBB(Vector3 dir_01, Vector3 dir_02, Vector3 len_01, Vector3 len_02, Vector3 len_03, Vector3 Len_04, Vector3 interval_);
	
	//コンストラクタ
	ColliderManager();
	ColliderManager(ColliderManager&) = delete;

	//メンバ定数
	static const int directionValue = 3;//軸方向の数(x軸、y軸、z軸の三本)

	//メンバ変数
public:
	static ColliderManager* instance;//他ファイルでの呼び出し用のインスタンス
private:
	std::vector<ObjectCollider*> objectList;//オブジェクトの当たり判定リスト
};