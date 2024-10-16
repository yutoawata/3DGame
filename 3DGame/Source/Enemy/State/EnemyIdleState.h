#pragma once
#include "..\..\BaseClass\StateBase.h"

template<class Object>
//�G�l�~�[�̑ҋ@��ԃN���X
class EnemyIdleState : public StateBase<Object> {
	//�����o�֐�
public:
	//�R���X�g���N�^
	EnemyIdleState(Object* holder_);

	//�f�X�g���N�^
	~EnemyIdleState();

	//�ҋ@��Ԃ̏���
	StateBase<Object>* Run() override;

};