#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "..\Player\Soldier.h"

//�e���v���[�g�R���X�g���N�^�����̉�
template class IdleState<Soldier>;

//�R���X�g���N�^
template<class Object>
IdleState<Object>::IdleState(Object* holder_)
	: StateBase<Object>(holder_) {
	this->animationName = "Idle";
}

//�f�X�g���N�^
template<class Object>
IdleState<Object>::~IdleState() {}

//�X�V����
template<class Object>
StateBase<Object>* IdleState<Object>::Run() {
	if (IsMove()) {
		//�ړ��L�[���͂ňړ�State�ɑJ��
		Object* holderAddress = this->holder;
		delete this;
		return new MoveState<Object>(holderAddress);
	}
	else if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		//���N���b�N�ōU��State�ɑJ��
		Object* holderAddress = this->holder;
		delete this;
		return new AttackState<Object>(holderAddress);
	}

	//�������͂�������Αҋ@State�̂܂�
	return this;
}

template<class Object>
//�ړ����菈��
bool IdleState<Object>::IsMove() {

	return CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_A)
		|| CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_D)
		|| CheckHitKey(KEY_INPUT_SPACE) || GetMouseInput() & MOUSE_INPUT_RIGHT;
}