#pragma once
#include "..\..\BaseClass\StateBase.h"

template<class Object>
//エネミーの待機状態クラス
class EnemyIdleState : public StateBase<Object> {
	//メンバ関数
public:
	//コンストラクタ
	EnemyIdleState(Object* holder_);

	//デストラクタ
	~EnemyIdleState();

	//待機状態の処理
	StateBase<Object>* Run() override;

};