#include "AIBase.h"
#include "..\Enemy\Mutant.h"
#include "..\Enemy\Magician.h"

//�e���v���[�g�R���X�g���N�^�����̉�
template class AIBase<Mutant>;
template class AIBase<Magician>;

template<class Object>
//�R���X�g���N�^
AIBase<Object>::AIBase(Object* holder_) {
	this->holder = holder_;
	if (this->holder->getTarget() != nullptr) {
		targetPosition = this->holder->getTarget()->getPosition();
	}
}

template<class Object>
//�R���X�g���N�^
AIBase<Object>::~AIBase() {}