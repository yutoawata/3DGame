#include "ColliderManager.h"

//���t�@�C���ł̌Ăяo���p�̃C���X�^���X�𐶐�
ColliderManager* ColliderManager::instance = new ColliderManager();

//�R���X�g���N�^
ColliderManager::ColliderManager() {}

//�f�X�g���N�^
ColliderManager::~ColliderManager() {}

//�C���X�^���X�̐�������
void ColliderManager::CreateInstance() {
    if (instance == nullptr) {
        instance = new ColliderManager();
    }
}

//�C���X�^���X�̍폜����
void ColliderManager::DeleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

//���X�g�ǉ�����
void ColliderManager::AddList(ObjectCollider* collider_) {
    objectList.emplace_back(collider_);
}

//���X�g���̃R���C�_�[���`�F�b�N
void ColliderManager::CheckList() {

    for (int i = 0; i < static_cast<int>(objectList.size()) - 1; i++) {
        for (int j = i + 1; j < static_cast<int>(objectList.size()); j++) {
            //�Ώۂ̎��R���C�_�[������
            for (CubeCollider* collider01 : objectList[i]->getCubeColliders()) {

                //����̎��R���C�_�[������
                for (CubeCollider* collider02 : objectList[j]->getCubeColliders()) {

                    CheckCollider(collider01, collider02, i, j);
                }
                //����̎��R���C�_�[������
                for (SphereCollider* collider02 : objectList[j]->getSphereColliders()) {

                    CheckCollider(collider01, collider02, i, j);
                }
            }
            for (SphereCollider* collider01 : objectList[j]->getSphereColliders()) {
                //����̎��R���C�_�[������
                for (CubeCollider* collider02 : objectList[j]->getCubeColliders()) {

                    CheckCollider(collider02, collider01, i, j);
                }
            }
        }
        
    }
}

//Colider���m�̔��茟��
void ColliderManager::CheckCollider(CubeCollider* collider_01, CubeCollider* collider_02, int object_01_num, int object_02_num) {
    //�����蔻�肪�����ΏۂȂ画�菈�����s
    if (collider_01->IsActive() && collider_02->IsActive()) {

        //�����蔻����s���������Ă����
        if (CheckOBBToOBB(*collider_01, *collider_02)) {
            //�e�I�u�W�F�N�g�����Փˎ��̏��������s
            objectList[object_01_num]->OnCollision(*objectList[object_02_num], collider_02->getType());
            objectList[object_02_num]->OnCollision(*objectList[object_01_num], collider_01->getType());
        }
        else {
            collider_01->Update();
            collider_02->Update();
        }
    }
}

//Colider���m�̔��茟��
void ColliderManager::CheckCollider(CubeCollider* cube_collider, SphereCollider* sphere_collider, int cube_object_num, int sphere_object_num) {
    //�����蔻�肪�����ΏۂȂ画�菈�����s��
    if (cube_collider->IsActive() && sphere_collider->IsActive()) {

        //�����蔻����s���������Ă����
        if (CheckOBBToSphere(*cube_collider, *sphere_collider)) {
            //�e�I�u�W�F�N�g�����Փˎ��̏��������s
            objectList[cube_object_num]->OnCollision(*objectList[sphere_object_num], sphere_collider->getType());
            objectList[sphere_object_num]->OnCollision(*objectList[cube_object_num], cube_collider->getType());
        }
        else {
            cube_collider->Update();
            sphere_collider->Update();
        }
    }
}

//OBB�Ƌ��̓����蔻�菈��
bool ColliderManager::CheckOBBToSphere(const CubeCollider& cube_collider, const SphereCollider& sphere_collider) {
    Vector3 vec = Vector3::ZERO;

    float length[directionValue] = { cube_collider.getLength().x, cube_collider.getLength().y, cube_collider.getLength().z };

    for (int i = 0; i < directionValue; i++) {

        Vector3 direction = sphere_collider.getPosition() - cube_collider.getPosition();
        float dot = Vector3::Dot(direction, cube_collider.getDirectoin(i)) / length[i];

        dot = fabsf(dot);
        if (dot > 1) {
            //�����̉��̖ʂ���̋��������Z
            vec +=  cube_collider.getDirectoin(i) * (1 - dot) * length[i];
        }
    }
    return vec.getSize() <= sphere_collider.getRadius();
}

//�������ɓ��e���ꂽ���������瓊�e����n�̒������Z�o
float ColliderManager::GetShadowLineLength(Vector3& sep_, Vector3& len_01, Vector3& len_02, Vector3 len_03) {
    Vector3 normSep = sep_.Normalized();
    float length01 = fabsf(Vector3::Dot(normSep, len_01));
    float length02 = fabsf(Vector3::Dot(normSep, len_02));
    //���݂��Ȃ��ꍇ�ɏ������Ȃ����߁A�������ɂ��Ă���
    float length03 = (len_03 == Vector3::ZERO) ? 0 : GetAbsoluteFloat(Vector3::Dot(normSep, len_03));

    return length01 + length02 + length03;
}

//���ςŕ������̗L���𔻒�
bool ColliderManager::CheckDotOBB(Vector3 dir_, Vector3 len_01, Vector3 len_02, Vector3 len_03, Vector3 len_04, 
    Vector3 ingerval_) {

    float collider01Line = len_01.getSize();
    float collider02Line = GetShadowLineLength(dir_, len_02, len_03, len_04);
    float length = fabsf(Vector3::Dot(ingerval_, dir_));
    if (length > collider01Line + collider02Line)
        return false;

    return true;
}

//���ςŕ������̗L���𔻒�
bool ColliderManager::CheckCrossOBB(Vector3 dir_01, Vector3 dir_02, Vector3 len_01, Vector3 len_02, Vector3 len_03, 
    Vector3 Len_04, Vector3 interval_) {

    Vector3 cross = Vector3::Cross(dir_01, dir_02);
    float length01 = GetShadowLineLength(cross, len_01, len_02);
    float length02 = GetShadowLineLength(cross, len_03, Len_04);
    float L = fabsf(Vector3::Dot(interval_, cross));
    if ((L > length01 + length02))
        return false;//�Փ˂��ĂȂ�

    return true;
}

//OBB���m�̑��蔻��
bool ColliderManager::CheckOBBToOBB(const CubeCollider& c_c_01, const CubeCollider& c_c_02) {
    //�e�����x�N�g���̊m��
    //(n***:�W���������x�N�g��)
    Vector3 cC01Dir01 = c_c_01.getDirectoin(0);
    Vector3 cC01Dir02 = c_c_01.getDirectoin(1);
    Vector3 cC01Dir03 = c_c_01.getDirectoin(2);
    Vector3 cC02Dir01 = c_c_02.getDirectoin(0);
    Vector3 cC02Dir02 = c_c_02.getDirectoin(1);
    Vector3 cC02Dir03 = c_c_02.getDirectoin(2);

    //���������Z�o
    Vector3 cC01Len01 = cC01Dir01 * c_c_01.getLength().x;
    Vector3 cC01Len02 = cC01Dir02 * c_c_01.getLength().y;
    Vector3 cC01Len03 = cC01Dir03 * c_c_01.getLength().z;
    Vector3 cC02Len01 = cC02Dir01 * c_c_02.getLength().x;
    Vector3 cC02Len02 = cC02Dir02 * c_c_02.getLength().y;
    Vector3 cC02Len03 = cC02Dir03 * c_c_02.getLength().z;

    //���S�_�Ԃ̋���
    Vector3 interval = c_c_01.getPosition() - c_c_02.getPosition();

    //������������������Փ˂��ĂȂ��̂�false��Ԃ��A�������ĂȂ���Α��̕�����������

    //�������@
    if (!CheckDotOBB(cC01Dir01, cC01Len01, cC02Len01, cC02Len02, cC02Len03, interval))
        return false;

    //�������A
    if (!CheckDotOBB(cC01Dir02, cC01Len02, cC02Len01, cC02Len02, cC02Len03, interval))
        return false;

    //�������B
    if (!CheckDotOBB(cC01Dir03, cC01Len03, cC02Len01, cC02Len02, cC02Len03, interval))
        return false;

    //�������C
    if (!CheckDotOBB(cC02Dir01, cC02Len01, cC01Len01, cC01Len02, cC01Len03, interval))
        return false;

    //�������D
    if (!CheckDotOBB(cC02Dir02, cC02Len02, cC01Len01, cC01Len02, cC01Len03, interval))
        return false;

    //�������E
    if (!CheckDotOBB(cC02Dir03, cC02Len03, cC01Len01, cC01Len02, cC01Len03, interval))
        return false;

    //�������F
    if (!CheckCrossOBB(cC01Dir01, cC02Dir01, cC01Len02, cC01Len03, cC02Len02, cC02Len03, interval))
        return false;

    //�������G
    if (!CheckCrossOBB(cC01Dir01, cC02Dir02, cC01Len02, cC01Len03, cC02Len01, cC02Len03, interval))
        return false;

    //�������H
    if (!CheckCrossOBB(cC01Dir01, cC02Dir03, cC01Len02, cC01Len03, cC02Len01, cC02Len02, interval))
        return false;

    //�������I
    if (!CheckCrossOBB(cC01Dir02, cC02Dir01, cC01Len01, cC01Len03, cC02Len02, cC02Len03, interval))
        return false;

    //�������J
    if (!CheckCrossOBB(cC01Dir02, cC02Dir02, cC01Len01, cC01Len03, cC02Len01, cC02Len03, interval))
        return false;

    //�������K
    if (!CheckCrossOBB(cC01Dir02, cC02Dir03, cC01Len01, cC01Len03, cC02Len01, cC02Len02, interval))
        return false;

    //�������L
    if (!CheckCrossOBB(cC01Dir03, cC02Dir01, cC01Len01, cC01Len02, cC02Len02, cC02Len03, interval))
        return false;

    //�������M
    if (!CheckCrossOBB(cC01Dir03, cC02Dir02, cC01Len01, cC01Len02, cC02Len01, cC02Len03, interval))
        return false;

    //�������N
    if (!CheckCrossOBB(cC01Dir03, cC02Dir03, cC01Len01, cC01Len02, cC02Len01, cC02Len02, interval))
        return false;

    return true;
}