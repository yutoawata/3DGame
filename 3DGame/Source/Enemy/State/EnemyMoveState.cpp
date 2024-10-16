#include "EnemyMoveState.h"
#include "EnemyIdleState.h"
#include "EnemyAttackState.h"
#include "..\Mutant.h"
#include "..\Magician.h"

//�e���v���[�g�R���X�g���N�^�����̉�
template class EnemyMoveState<Mutant>;
template class EnemyMoveState<Magician>;

template<class Object>
//�R���X�g���N�^
EnemyMoveState<Object>::EnemyMoveState(Object* holder_)
	: StateBase<Object>(holder_) {
	this->animationName = "Move";
}

template<class Object>
//�f�X�g���N�^
EnemyMoveState<Object>::~EnemyMoveState(){}


template<class Object>
//�ړ���Ԃ̏���
StateBase<Object>* EnemyMoveState<Object>::Run() {
	//�ړ�����
	Move();
	//��]����
	Rotate();
	
	//�ړ����Ă��Ȃ��Ȃ�
	if (isStop) {
		Object* holderAddress = this->holder;
		delete this;
		return new EnemyIdleState<Object>(holderAddress);
	}

	//�U�������܂ŖڕW�̃I�u�W�F�N�g�ɋ߂Â����Ȃ�
	if (this->holder->getAI<Object>()->CanAttack()) {
		Object* holderAddress = this->holder;
		delete this;
		return new EnemyAttackState<Object>(holderAddress);
	}

	return this;
}


template<class Object>
//�ړ�����
void EnemyMoveState<Object>::Move() {
	//�ڕW�̃I�u�W�F�N�g����������Ɉړ�����
	moveVector = this->holder->getAI<Object>()->SelectMovePosition() - this->holder->getPosition();
	moveVector.y = 0.0f;

	//1�t���[���ł̈ړ��ʂ��Z�o
	float moveSpeed = this->holder->getSpeed() * FPSManager::getInstance()->getDeltaTime();
	

	//�ړI�n�Ƃ̋�����1�t���[���̈ړ��ʂ�艓���Ȃ�
	if (moveVector.getSize() >= moveSpeed) {
		//�ړ�����
		moveVector = moveVector.Normalized() * moveSpeed;
		this->holderPosition = this->holder->getPosition() + moveVector;
		isStop = false;
	}
	else {
		moveVector = Vector3::ZERO;
		isStop = true;
	}
	
}

//��]����
template<class Object>
void EnemyMoveState<Object>::Rotate() {
	Vector3 direction = moveVector.Normalized();
	this->holderAngle.y = GetAngleFromVector(direction);
}