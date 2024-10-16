#include "EnemyAttackState.h"
#include "EnemyIdleState.h"
#include "..\Mutant.h"
#include "..\Magician.h"

//�e���v���[�g�R���X�g���N�^�����̉�
template class EnemyAttackState<Mutant>;
template class EnemyAttackState<Magician>;

template<class Object>
//�R���X�g���N�^
EnemyAttackState<Object>::EnemyAttackState(Object* holder_)
	: StateBase<Object>(holder_) {
	this->animationName = "Attack";
	Vector3 direction = this->holder->getTarget()->getPosition() - this->holderPosition;
	this->holderAngle.y = GetAngleFromVector(direction);
}

template<class Object>
//�f�X�g���N�^
EnemyAttackState<Object>::~EnemyAttackState() {}


template<class Object>
//�U����Ԏ��̏���
StateBase<Object>* EnemyAttackState<Object>::Run() {

	//�U���A�j���[�V�������I��������
	if (this->holder->IsFinish()) {
		//IdleState�ɑJ�ڂ���
		Object* holderAddress = this->holder;
		delete this;
		return new EnemyIdleState<Object>(holderAddress);
	}

	return this;
}