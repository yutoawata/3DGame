#pragma once
#include "..\..\BaseClass\AIBase.h"

template<class Object>
class LongRangeAI : public AIBase<Object> {
	//�����o�֐�
public:
	//�R���X�g���N�^
	LongRangeAI(Object* holder_);
	//�f�X�g���N�^
	~LongRangeAI();

	//�ړ����I��
	Vector3 SelectMovePosition() override;
	//�U���\���菈��
	bool CanAttack();
private:
	//�ړ���𐶐�
	void CrelateMovePosition();

	//�����o�萔
	static const int listSize = 5;			//angleList�̗v�f��
	static const float angleList[listSize];	//�����_����������p�x�̃��X�g
	static const float POSITION_INTERVAL;	//�ړ���̍��W�X�V�̊Ԋu
	static const float ATTACK_INTERVAL;		//�U���̊��o
	static const float ATTACK_DISTANCE;		//�U�����鋗��

	//�����o�ϐ�
	Vector3 movePosition = Vector3::ZERO;	//�ړ���̍��W
	Vector3 angle = Vector3::ZERO;			//��]�p�x
	float positionTimer = POSITION_INTERVAL;//���W�X�V�̃^�C�}�[
	float attackTimer = 0;					//�U���Ԋu�̃^�C�}�[
	bool isAttack = false;					//�U�����t���O
};