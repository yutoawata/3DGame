#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "..\Player\Soldier.h"

//テンプレートコンストラクタを実体化
template class IdleState<Soldier>;

//コンストラクタ
template<class Object>
IdleState<Object>::IdleState(Object* holder_)
	: StateBase<Object>(holder_) {
	this->animationName = "Idle";
}

//デストラクタ
template<class Object>
IdleState<Object>::~IdleState() {}

//更新処理
template<class Object>
StateBase<Object>* IdleState<Object>::Run() {
	if (IsMove()) {
		//移動キー入力で移動Stateに遷移
		Object* holderAddress = this->holder;
		delete this;
		return new MoveState<Object>(holderAddress);
	}
	else if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		//左クリックで攻撃Stateに遷移
		Object* holderAddress = this->holder;
		delete this;
		return new AttackState<Object>(holderAddress);
	}

	//何も入力が無ければ待機Stateのまま
	return this;
}

template<class Object>
//移動判定処理
bool IdleState<Object>::IsMove() {

	return CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_A)
		|| CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_D)
		|| CheckHitKey(KEY_INPUT_SPACE) || GetMouseInput() & MOUSE_INPUT_RIGHT;
}