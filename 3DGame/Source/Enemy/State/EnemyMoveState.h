#pragma once
#include "..\..\BaseClass\StateBase.h"

template<class Object>
class EnemyMoveState : public StateBase<Object> {
	//�����o�֐�
public:
	//�R���X�g���N�^
	EnemyMoveState(Object* holder_);
	
	//�f�X�g���N�^
	~EnemyMoveState();

	//�ړ���Ԃ̏���
	StateBase<Object>* Run() override;
private:
	//�ǐՏ���
	void Move();
	//��]����
	void Rotate();

	//�����o�ϐ�
	Vector3 moveVector = Vector3::ZERO;	//�ړ�����
	int nextRuteIndex = 0;				//�p�j���̈ړ���̍��W�̗v�f�ԍ�
	bool isStop = false;				//�ړI�n�����t���O
};
