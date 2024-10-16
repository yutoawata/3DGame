#include "AttackState.h"
#include "IdleState.h"
#include "MoveState.h"
#include "..\Player\Soldier.h"

//テンプレートコンストラクタを実体化
template class AttackState<Soldier>;

template<class Object>
//コンストラクタ
AttackState<Object>::AttackState(Object* holder_)
	: StateBase<Object>(holder_){
	this->animationName = "Attack";
}

template<class Object>
//デストラクタ
AttackState<Object>::~AttackState() {}

template<class Object>
//更新処理
StateBase<Object>* AttackState<Object>::Run() {
	
	if (GetMouseInput()&MOUSE_INPUT_RIGHT) {
		Object* holderAddress = this->holder;
		delete this;
		return new MoveState<Object>(holderAddress);
	}
	//オブジェクトの攻撃アニメーションが終了したら
	else if (this->holder->IsFinish()) {
		Object* holderAddress = this->holder;
		delete this;
		return new IdleState<Object>(holderAddress);
	}
	return this;
}