#pragma once
#include <vector>
#include "..\Math\Vector3.h"
#include "..\Math\MathMethod.h"
#include "..\Collider\CubeCollider.h"
#include "..\Collider\SphereCollider.h"

//�I�u�W�F�N�g�����R���C�_�[�̓����N���X
class ObjectCollider {
	//�񋓌^
public:
	//�I�u�W�F�N�g���ʗp�̃^�O
	enum class ObjectTag {
		NONE,
		PLAYER,	//�v���C���[
		FIELD,	//�t�B�[���h
		ENEMY,	//�G�l�~�[
		ATTACK	//�U������
	};

	//�����o�֐�

	//�R���X�g���N�^
	ObjectCollider(ObjectTag tag_ = ObjectTag::NONE);
	//�f�X�g���N�^
	virtual ~ObjectCollider();

	//�A�N�Z�T
	
	//���g���������Ă��闧����Collider�̔z��ŕԂ�
	std::vector<CubeCollider*> getCubeColliders() const { return cubeColliders; }
	//�������Ă��鋅��Collider�̔z���Ԃ�
	std::vector<SphereCollider*> getSphereColliders() const { return sphereColliders; }
	//���g��Ԃ�
	template<class Object>
	const Object* getComponent() const { return dynamic_cast<const Object*>(this); }
	//�w�肳�ꂽ������Collider��Ԃ�
	CubeCollider* getCubeCollider(int num_) const { return cubeColliders[num_]; }
	//�w�肳�ꂽ����Collider��Ԃ�
	SphereCollider* getSphereCollider(int num_) const { return sphereColliders[num_]; }
	//���g��Tag��Ԃ�
	ObjectTag getTag() const { return tag; }

	//�Փ˔��莞�̏���
	virtual void OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) {}
protected:
	//������Collider�̒ǉ�(�߂�l�͔z��̗v�f�ԍ�)
	int AddCubeColliderList(CubeCollider* add_collider);
	//����Collider�̒ǉ�(�߂�l�͔z��̗v�f�ԍ�)
	int AddSphereColliderList(SphereCollider* add_collider);

	//�����o�ϐ�
	Vector3 checkPosition = Vector3::ZERO;			//�Փ˔���p�̒��S���W
	Matrix rotation = Matrix::INDENT;				//�I�u�W�F�N�g�̉�]�s��
	std::vector<CubeCollider*> cubeColliders;		//�I�u�W�F�N�g����������Collider�̔z��
	std::vector<SphereCollider*> sphereColliders;	//�I�u�W�F�N�g�������`Collider�̔z��
	ObjectTag tag = ObjectTag::NONE;				//�I�u�W�F�N�g���ʗp�̂̃^�O
};