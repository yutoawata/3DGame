#include "EnemyAttackState.h"
#include "EnemyIdleState.h"
#include "..\Mutant.h"
#include "..\Magician.h"

//テンプレートコンストラクタを実体化
template class EnemyAttackState<Mutant>;
template class EnemyAttackState<Magician>;

template<class Object>
//コンストラクタ
EnemyAttackState<Object>::EnemyAttackState(Object* holder_)
	: StateBase<Object>(holder_) {
	this->animationName = "Attack";
	Vector3 direction = this->holder->getTarget()->getPosition() - this->holderPosition;
	this->holderAngle.y = GetAngleFromVector(direction);
}

template<class Object>
//デストラクタ
EnemyAttackState<Object>::~EnemyAttackState() {}


template<class Object>
//攻撃状態時の処理
StateBase<Object>* EnemyAttackState<Object>::Run() {

	//攻撃アニメーションが終了したら
	if (this->holder->IsFinish()) {
		//IdleStateに遷移する
		Object* holderAddress = this->holder;
		delete this;
		return new EnemyIdleState<Object>(holderAddress);
	}

	return this;
}