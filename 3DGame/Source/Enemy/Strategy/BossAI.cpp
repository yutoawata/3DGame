#include "..\Strategy\BossAI.h"
#include "..\Mutant.h"
#include "..\Magician.h"

//�e���v���[�g�R���X�g���N�^�����̉�
template class BossAI<Mutant>;
template class BossAI<Magician>;

template<class Object >
const float BossAI<Object>::ATTACK_RANGE = 180.0f;//�U������

template<class Object>
//�R���X�g���N�^
BossAI<Object>::BossAI(Object* holder_)
	: AIBase<Object>(holder_) {
	this->routeList = { Vector3(100.0f,0.0f,100.0f), Vector3(-100.0f,0.0f,-100.0f) };
}

template<class Object>
//�ړ��ڕW�̍��W��I��
Vector3 BossAI<Object>::SelectMovePosition() {
	Vector3 targetPosition = Vector3::ZERO;

	if (this->holder->getTarget() != nullptr) {
		targetPosition = this->holder->getTarget()->getPosition();	
	}

	Vector3 direction = targetPosition - this->holder->getPosition();

	//1�t���[���ł̈ړ���
	float moveSpeed = this->holder->getSpeed() * FPSManager::getInstance()->getDeltaTime();

	//�ړI�n��1�t���[���ł̈ړ��ʂ��߂����
	if (direction.getSize() <= moveSpeed) {
		//�ړI�n�����g�̍��W�ɂ��āA�ړ����Ȃ��悤�ɂ���
		targetPosition = this->holder->getPosition();
	}

	return targetPosition;
}


template<class Object>
//�U���\���菈��
bool BossAI<Object>::CanAttack() {
	this->targetPosition = this->holder->getTarget()->getPosition();

	//������� ���� �U���͈͓��Ȃ�
	if (this->holder->IsFind() && (this->targetPosition - this->holder->getPosition()).getSize() <= ATTACK_RANGE) {
		return true;//�U���\
	}
	return false;
}