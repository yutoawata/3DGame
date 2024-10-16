#include "AIBase.h"
#include "..\Enemy\Mutant.h"
#include "..\Enemy\Magician.h"

//テンプレートコンストラクタを実体化
template class AIBase<Mutant>;
template class AIBase<Magician>;

template<class Object>
//コンストラクタ
AIBase<Object>::AIBase(Object* holder_) {
	this->holder = holder_;
	if (this->holder->getTarget() != nullptr) {
		targetPosition = this->holder->getTarget()->getPosition();
	}
}

template<class Object>
//コンストラクタ
AIBase<Object>::~AIBase() {}