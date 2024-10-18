#include "LongRangeAI.h"
#include "DxLib.h"
#include "..\..\Enemy\Mutant.h"
#include "..\..\Enemy\Magician.h"

//�e���v���[�g�R���X�g���N�^�����̉�
template class LongRangeAI<Magician>;

template<class Object>
const float LongRangeAI<Object>::angleList[listSize] = {
		DX_PI_F / 2,//90
		DX_PI_F / 3,//60
		DX_PI_F / 4,//45
		DX_PI_F / 5,//30
		DX_PI_F / 6 //15
};
template<class Object>
const float LongRangeAI<Object>::POSITION_INTERVAL = 10.0f;
template<class Object>
const float LongRangeAI<Object>::ATTACK_INTERVAL = 3.0f;
template<class Object>
const float LongRangeAI<Object>::ATTACK_DISTANCE = 200.0f;

template<class Object>
//�R���X�g���N�^
LongRangeAI<Object>::LongRangeAI(Object* holder_)
	: AIBase<Object>(holder_){}

template<class Object>
//�f�X�g���N�^
LongRangeAI<Object>::~LongRangeAI() {}

template<class Object>
//�ړ����I��
Vector3 LongRangeAI<Object>::SelectMovePosition() {

	CrelateMovePosition();
	Vector3 result = movePosition;

	//�ړI�n�܂ł̋������Z�o
	float distance = (movePosition - this->holder->getPosition()).getSize();
	
	//�������߂����
	if (distance <= 0.1f) {
		//���g�̍��W����
		result = this->holder->getPosition();
	}

	return result;
}

template<class Object>
//�ڑ���̍��W���𐶐�
void LongRangeAI<Object>::CrelateMovePosition() {

	positionTimer += FPSManager::getInstance()->getDeltaTime();
	//���W�̍X�V���ԂɂȂ�����
	if (positionTimer >= POSITION_INTERVAL) {
		int max = (listSize - 1) * 2;	//�����̍ő�l(�p�x�̃��X�g�̗v�f���̓�{(+ or -))
		int randIndex = CreateRandom(0, max);
		float resultAngle = 0.0f;		//�ړ���̍��W�����߂�p�x

		if (max / 2 > randIndex) {
			resultAngle = this->angleList[randIndex % 2];
		}
		else {
			resultAngle = -this->angleList[randIndex % 2];
		}
		angle.y = resultAngle + this->holder->getTarget()->getAngle().y;

		Vector3 vec = this->holder->getPosition() - this->holder->getTarget()->getPosition();

		vec = vec.Normalized() * ATTACK_DISTANCE;

		Vector3 vector = Matrix::GetRotateMatrix(angle) * vec;
		movePosition = this->targetPosition + vector;
		positionTimer = 0;
	}
}


template<class Object>
//�U�����\���̔��菈��
bool LongRangeAI<Object>::CanAttack() {
	attackTimer += FPSManager::getInstance()->getDeltaTime();
	if (!this->holder->getMagic()->IsActive()&& attackTimer >= ATTACK_INTERVAL) {
		attackTimer = 0.0f;
		return true;
	}

	return false;
}