#pragma once
#include "..\..\BaseClass\AIBase.h"

template<class Object>
class BossAI : public AIBase<Object> {
	//�����o�֐�
public:
	//�R���X�g���N�^
	BossAI(Object* holider_);

	//�ړ����I��
	Vector3 SelectMovePosition() override;
	//�U���\���菈��
	bool CanAttack();

private:
	static const float ATTACK_RANGE;//�U������
	
	//�����o�ϐ�
	int ruteNum = 0;//�ړ���̏��H�̗v�f�ԍ�
};