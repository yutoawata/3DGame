#include "EnemyIdleState.h"
#include "EnemyMoveState.h"
#include "EnemyAttackState.h"
#include "..\Mutant.h"
#include "..\Magician.h"

//�e���v���[�g�R���X�g���N�^�����̉�
template class EnemyIdleState<Mutant>;
template class EnemyIdleState<Magician>;

template<class Object>
//�R���X�g���N�^
EnemyIdleState<Object>::EnemyIdleState(Object* holder_)
	: StateBase<Object>(holder_) {
	this->animationName = "Idle";
}

template<class Object>
//�f�X�g���N�^
EnemyIdleState<Object>::~EnemyIdleState() {}

template<class Object>
//�ҋ@��Ԃ̏���
StateBase<Object>* EnemyIdleState<Object>::Run() {

	//�ړ��������Z�o
	Vector3 direction = this->holder->getAI<Object>()->SelectMovePosition() - this->holder->getPosition();
	//1�t���[���ł̈ړ��ʂ��Z�o
	float moveSpeed = this->holder->getSpeed() * FPSManager::getInstance()->getDeltaTime();

	//�ړ���̍��W���痣��Ă���Ȃ�
	if (direction.getSize() >= moveSpeed) {
		Object* holderAddress = this->holder;
		delete this;
		//�ړ���ԂɑJ��
		return new EnemyMoveState<Object>(holderAddress);
	}

	//�U���\�Ȃ�
	if (this->holder->getAI<Object>()->CanAttack()) {
		Object* holderAddress = this->holder;
		delete this;
		//�U����ԂɑJ��
		return new EnemyAttackState<Object>(holderAddress);
	}

	return this;
}