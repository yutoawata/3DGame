#include "AttackState.h"
#include "IdleState.h"
#include "MoveState.h"
#include "..\Player\Soldier.h"

//�e���v���[�g�R���X�g���N�^�����̉�
template class AttackState<Soldier>;

template<class Object>
//�R���X�g���N�^
AttackState<Object>::AttackState(Object* holder_)
	: StateBase<Object>(holder_){
	this->animationName = "Attack";
}

template<class Object>
//�f�X�g���N�^
AttackState<Object>::~AttackState() {}

template<class Object>
//�X�V����
StateBase<Object>* AttackState<Object>::Run() {
	
	if (GetMouseInput()&MOUSE_INPUT_RIGHT) {
		Object* holderAddress = this->holder;
		delete this;
		return new MoveState<Object>(holderAddress);
	}
	//�I�u�W�F�N�g�̍U���A�j���[�V�������I��������
	else if (this->holder->IsFinish()) {
		Object* holderAddress = this->holder;
		delete this;
		return new IdleState<Object>(holderAddress);
	}
	return this;
}