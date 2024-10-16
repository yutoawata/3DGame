#pragma once
#include "DxLib.h"
#include "AIBase.h"
#include "..\Collider\ObjectCollider.h"
#include "..\Animation\Animator.h"

//�ړ��I�u�W�F�N�g�̊��N���X
class MoverBase : public ObjectCollider, public Animator {
	//�����o�֐�
public:
	//�R���X�g���N�^
	MoverBase(int model_handle, ObjectTag tag_);
	MoverBase(Vector3 position_, int model_handle, ObjectTag tag_);
	MoverBase(Vector3 position_, Vector3 angle_, Vector3 scale_, int model_handle,  int hit_point, int attack_point,
				ObjectTag tag_);
	//�f�X�g���N�^
	virtual ~MoverBase();

	//�A�N�Z�T
	
	//�I�u�W�F�N�g���A�N�V�������N���������Ԃ�
	MoverBase* getTarget() const { return target; }
	//�O���̕����x�N�g����Ԃ�
	Vector3 getFrontDirection() const { return frontDirection; }
	//HP��Ԃ�
	int getHitPoint() const { return hitPoint; }
	//�U���͂�Ԃ�
	int getAttackPoint() const { return attackPoint; }
	//�ړ����x��Ԃ�
	float getSpeed() const { return speed; }
	//�ڒn�t���O��Ԃ�
	bool IsGround() const { return isGround; }
	//�ڕW�����t���O��Ԃ�
	bool IsFind() const { return isFind; }
public:
	//�X�V�O����
	virtual void Prepare() = 0;
	//�X�V����
	virtual void Update() = 0;
	//�`�揈��
	virtual void Draw() = 0;

	//�����o�ϐ�
protected:
	MoverBase* target = nullptr;			//�ڕW�ƂȂ�I�u�W�F�N�g
	Vector3 moveVector = Vector3::ZERO;		//�I�u�W�F�N�g�̈ړ�����
	Vector3 frontDirection = Vector3::ZERO;	//�O���̕����x�N�g��
	int hitPoint = 0;						//�I�u�W�F�N�g��HP
	int attackPoint = 0;					//�U����
	float speed = 0.0f;						//�ړ����x
	bool isGround = false;					//�ڒn�t���O
	bool isGravity = false;					//�d�͂̉e�����󂯂�t���O
	bool isFind = false;					//�����t���O
};