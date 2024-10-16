#pragma once
#include <vector>
#include "..\Math\MathMethod.h"
#include "..\Collider\ObjectCollider.h"
#include "..\Collider\CubeCollider.h"
#include "..\Collider\SphereCollider.h"

//�����蔻�菈���N���X
class ColliderManager {
	//�����o�֐�
public:
	//�f�X�g���N�^
	~ColliderManager();

	//�A�N�Z�T

	//�C���X�^���X��Ԃ�
	static ColliderManager* getInstance() { return instance; }

	//�o�^����
	void AddList(ObjectCollider* collider_);

	//�C���X�^���X�̐�������
	static void CreateInstance();
	//�C���X�^���X�̍폜����
	static void DeleteInstance();
	//�o�^���ꂽ�����蔻�������
	void CheckList() ;
private:
	//OBB���m�ł̓����蔻�菈��
	bool CheckOBBToOBB(const CubeCollider& collider_01, const CubeCollider& collider_02);
	//OBB�Ƌ��ł̓����蔻��
	bool CheckOBBToSphere(const CubeCollider& cube_collider, const SphereCollider& sphere_collider);
	//Colider���m�̔��茟��
	void CheckCollider(CubeCollider* collider_01, CubeCollider* collider_02, int object_01_num, int object_02_num);
	//Colider���m�̔��茟��
	void CheckCollider(CubeCollider* cube_collider, SphereCollider* sphere_collider, int cube_object_num, int sphere_object_num);
	//���ˉe�ł̔��菈��
    static float GetShadowLineLength(Vector3& sep_, Vector3& len_01, Vector3& len_02, Vector3 len_03 = Vector3::ZERO);
	//���ς��g��������������
	static bool CheckDotOBB(Vector3 dir_, Vector3 len_01, Vector3 len_02, Vector3 len_03, Vector3 len_04, Vector3 ingerval_);
	//�O�ς��g��������������
	static bool CheckCrossOBB(Vector3 dir_01, Vector3 dir_02, Vector3 len_01, Vector3 len_02, Vector3 len_03, Vector3 Len_04, Vector3 interval_);
	
	//�R���X�g���N�^
	ColliderManager();
	ColliderManager(ColliderManager&) = delete;

	//�����o�萔
	static const int directionValue = 3;//�������̐�(x���Ay���Az���̎O�{)

	//�����o�ϐ�
public:
	static ColliderManager* instance;//���t�@�C���ł̌Ăяo���p�̃C���X�^���X
private:
	std::vector<ObjectCollider*> objectList;//�I�u�W�F�N�g�̓����蔻�胊�X�g
};