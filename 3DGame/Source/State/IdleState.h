#pragma once
#include "..\BaseClass\MoverBase.h"
#include "..\BaseClass\StateBase.h"
#include "..\Color\Color.h"

template<class Object>
//�ҋ@��ԃN���X
class IdleState : public StateBase<Object> {
public:
	//�R���X�g���N�^
	IdleState(Object* holder_);

	//�f�X�g���N�^
	~IdleState();

	//�X�V����
	StateBase<Object>* Run() override;
	//�ړ����菈��
	bool IsMove();
};