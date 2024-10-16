#include "EnemyIdleState.h"
#include "EnemyMoveState.h"
#include "EnemyAttackState.h"
#include "..\Mutant.h"
#include "..\Magician.h"

//テンプレートコンストラクタを実体化
template class EnemyIdleState<Mutant>;
template class EnemyIdleState<Magician>;

template<class Object>
//コンストラクタ
EnemyIdleState<Object>::EnemyIdleState(Object* holder_)
	: StateBase<Object>(holder_) {
	this->animationName = "Idle";
}

template<class Object>
//デストラクタ
EnemyIdleState<Object>::~EnemyIdleState() {}

template<class Object>
//待機状態の処理
StateBase<Object>* EnemyIdleState<Object>::Run() {

	//移動方向を算出
	Vector3 direction = this->holder->getAI<Object>()->SelectMovePosition() - this->holder->getPosition();
	//1フレームでの移動量を算出
	float moveSpeed = this->holder->getSpeed() * FPSManager::getInstance()->getDeltaTime();

	//移動先の座標から離れているなら
	if (direction.getSize() >= moveSpeed) {
		Object* holderAddress = this->holder;
		delete this;
		//移動状態に遷移
		return new EnemyMoveState<Object>(holderAddress);
	}

	//攻撃可能なら
	if (this->holder->getAI<Object>()->CanAttack()) {
		Object* holderAddress = this->holder;
		delete this;
		//攻撃状態に遷移
		return new EnemyAttackState<Object>(holderAddress);
	}

	return this;
}