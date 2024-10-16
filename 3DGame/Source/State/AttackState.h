#pragma once
#include "..\BaseClass\StateBase.h"
#include "..\Collider\ObjectCollider.h"
#include "..\Collider\CubeCollider.h"
#include "..\Color\Color.h"

template<class Object>
//�U����ԃN���X
class AttackState : public StateBase<Object> {
public:
	//�R���X�g���N�^
	AttackState(Object* holder_);

	//�f�X�g���N�^
	~AttackState();

	//�X�V����
	StateBase<Object>* Run() override;
};