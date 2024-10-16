#pragma once
#include "..\..\BaseClass\StateBase.h"

template<class Object>
//�G�l�~�[�̍U����ԃN���X
class EnemyAttackState : public StateBase<Object> {
	//�����o�֐�
public:
	//�R���X�g���N�^
	EnemyAttackState(Object* holder_);
	//�f�X�g���N�^
	~EnemyAttackState();

	//�U����Ԃ̏���
	StateBase<Object>* Run() override;
};