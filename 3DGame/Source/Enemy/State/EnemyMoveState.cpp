#include "EnemyMoveState.h"
#include "EnemyIdleState.h"
#include "EnemyAttackState.h"
#include "..\Mutant.h"
#include "..\Magician.h"

//テンプレートコンストラクタを実体化
template class EnemyMoveState<Mutant>;
template class EnemyMoveState<Magician>;

template<class Object>
//コンストラクタ
EnemyMoveState<Object>::EnemyMoveState(Object* holder_)
	: StateBase<Object>(holder_) {
	this->animationName = "Move";
}

template<class Object>
//デストラクタ
EnemyMoveState<Object>::~EnemyMoveState(){}


template<class Object>
//移動状態の処理
StateBase<Object>* EnemyMoveState<Object>::Run() {
	//移動処理
	Move();
	//回転処理
	Rotate();
	
	//移動していないなら
	if (isStop) {
		Object* holderAddress = this->holder;
		delete this;
		return new EnemyIdleState<Object>(holderAddress);
	}

	//攻撃距離まで目標のオブジェクトに近づいたなら
	if (this->holder->getAI<Object>()->CanAttack()) {
		Object* holderAddress = this->holder;
		delete this;
		return new EnemyAttackState<Object>(holderAddress);
	}

	return this;
}


template<class Object>
//移動処理
void EnemyMoveState<Object>::Move() {
	//目標のオブジェクトがいる方向に移動する
	moveVector = this->holder->getAI<Object>()->SelectMovePosition() - this->holder->getPosition();
	moveVector.y = 0.0f;

	//1フレームでの移動量を算出
	float moveSpeed = this->holder->getSpeed() * FPSManager::getInstance()->getDeltaTime();
	

	//目的地との距離が1フレームの移動量より遠いなら
	if (moveVector.getSize() >= moveSpeed) {
		//移動する
		moveVector = moveVector.Normalized() * moveSpeed;
		this->holderPosition = this->holder->getPosition() + moveVector;
		isStop = false;
	}
	else {
		moveVector = Vector3::ZERO;
		isStop = true;
	}
	
}

//回転処理
template<class Object>
void EnemyMoveState<Object>::Rotate() {
	Vector3 direction = moveVector.Normalized();
	this->holderAngle.y = GetAngleFromVector(direction);
}