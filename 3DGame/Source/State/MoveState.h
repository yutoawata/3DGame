#pragma once
#include "..\Color\Color.h"
#include "..\BaseClass\StateBase.h"


template<class Object>
class MoveState : public StateBase<Object> {
public://�����o�֐�
	//�R���X�g���N�^
	MoveState(Object* holder_);

	//�f�X�g���N�^
	~MoveState();
	
	StateBase<Object>* Run() override;
	
private:
	//�ړ�����
	Vector3 Move();	//�ړ�����
	Vector3 Jump();	//�W�����v����
	Vector3 Avoid();//�������
	void Rotate();	//��]����

	//�����o�萔
	static const float MOVE_SPEED;	//�ړ����x
	static const float JUMP_POWER;	//�W�����v���̗�
	static const float AVOID_SPEED;	//������̑��x

	//�����o�ϐ�
	Vector3 moveVector = Vector3::ZERO;	//�ړ����̍��W�ψ�
	Vector3 jumpVector = Vector3::ZERO;	//�W�����v���̍��W�ψ�
	Vector3 avoidVector = Vector3::ZERO;//������̍��W�ψ�
	Vector3 angle = Vector3::ZERO;		//�e���̉�]��
	bool isMove = false;				//�ړ��t���O
	bool isJump = false;				//�W�����v���t���O
	bool isAvoid = false;				//��𒆃t���O
	bool isRun = false;					//���s���t���O
};