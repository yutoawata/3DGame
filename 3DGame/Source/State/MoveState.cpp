#include "MoveState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "..\Player\Soldier.h"

//�e���v���[�g�R���X�g���N�^�����̉�
template class MoveState<Soldier>;

//static�萔��`
template<class Object>
const float MoveState<Object>::MOVE_SPEED = 1.0f;	//�ړ����x
template<class Object>
const float MoveState<Object>::JUMP_POWER = 10.0f;	//�W�����v���̏���
template<class Object>
const float MoveState<Object>::AVOID_SPEED = 5.0f;	//������̑��x

//�R���X�g���N�^
template<class Object>
MoveState<Object>::MoveState(Object* holder_)
	: StateBase<Object>(holder_) {
	this->animationName = "Move";
	isRun = false;
}

//�f�X�g���N�^
template<class Object>
MoveState<Object>::~MoveState() {}

//�X�V����
template<class Object>
StateBase<Object>* MoveState<Object>::Run() {
	if (CheckHitKey(KEY_INPUT_LSHIFT)) {
		this->animationName = "Run";
		isRun = true;
	}
	
	Vector3 addVector = Move() + Jump() + Avoid();

	//model�̌��_���W�͓����蔻��̒�Ȃ̂ŁA�������𑫂��đ��
	Vector3 position = this->holder->getPosition();
	Vector3 centerPosition = Vector3(position.x, position.y, position.z);

	this->holderPosition = centerPosition + addVector;

	//�������삪�������IdleState�ɑJ��
	if (!isMove && !isJump && !isAvoid) {
		Object* holderAddress = this->holder;
		delete this;
		return new IdleState<Object>(holderAddress);
	}
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		//���N���b�N��AttackState�ɑJ��
		Object* holderAddress = this->holder;
		delete this;
		return new AttackState<Object>(holderAddress);
	}

	return this;
}

//�ړ�����
template<class Object>
Vector3 MoveState<Object>::Move() {
	moveVector = Vector3::ZERO;
	isMove = false;

	//��𒆂͈ړ��o���Ȃ�
	if (!isAvoid) {
		if (CheckHitKey(KEY_INPUT_W)) {
			moveVector += this->holder->getFrontDirection() * MOVE_SPEED;
		}
		if (CheckHitKey(KEY_INPUT_S)) {
			moveVector += Vector3(Matrix::GetRotateMatrix(Vector3(0.0f, DX_PI_F, 0.0f)) * this->holder->getFrontDirection());
		}
		if (CheckHitKey(KEY_INPUT_A)) {
			moveVector += Vector3(Matrix::GetRotateMatrix(Vector3(0.0f, -DX_PI_F / 2, 0.0f)) * this->holder->getFrontDirection());
		}
		if (CheckHitKey(KEY_INPUT_D)) {
			moveVector += Vector3(Matrix::GetRotateMatrix(Vector3(0.0f, DX_PI_F / 2, 0.0f)) * this->holder->getFrontDirection());
		}
	}

	if (moveVector != Vector3::ZERO) {
		isMove = true;
		Rotate();
	}
	
	float speed = isRun ? MOVE_SPEED * 3.0f : MOVE_SPEED;

	return moveVector * speed;
}

//�W�����v����
template<class Object>
Vector3 MoveState<Object>::Jump() {

	//���n������W�����v�������I��
	if (this->holder->IsGround() && isJump) {
		jumpVector = Vector3::ZERO;
		this->animationName = "Move";
		isJump = false;
	}
	//LeftShift�L�[�ŃW�����v���������s
	if (CheckHitKey(KEY_INPUT_SPACE) && !isJump) {
		this->animationName = "Jump";
		jumpVector.y += JUMP_POWER;
		isJump = true;
	}

	//�d�͏���
	if (isJump) {
		//�W�����v�͏�܂Ŕ�񂾂��ƒn�ʂɐ܂�Ԃ����ߎڂ̔����͉������ɂȂ�悤�Ɍ�������͓͂�{�ɂ��Ă���
		jumpVector.y -= (JUMP_POWER / this->holder->getTotalAnimationTime()) * 2.0f;
	}

	return jumpVector;
}

//�������
template<class Object>
Vector3 MoveState<Object>::Avoid() {
	//
	if (GetMouseInput() & MOUSE_INPUT_RIGHT && !isAvoid) {
		isAvoid = true;
		this->animationName = "Avoid";
		if (moveVector == Vector3::ZERO) {
			avoidVector += this->holder->getFrontDirection() * AVOID_SPEED;
		}
		else {
			avoidVector += moveVector.Normalized() * AVOID_SPEED;
		}
	}
	if (isAvoid) {
		Vector3 direction = avoidVector.Normalized();
		avoidVector -= (direction * AVOID_SPEED) / this->holder->getTotalAnimationTime();

		//�A�j���[�V�������I�����������������I��
		if (this->holder->IsFinish()) {
			avoidVector = Vector3::ZERO;
			this->animationName = "Move";
			isAvoid = false;
		}	
	}

	return avoidVector;
}

//��]����
template<class Object>
void MoveState<Object>::Rotate() {
	moveVector = moveVector.Normalized();
	this->holderAngle.y = GetAngleFromVector(moveVector);
}