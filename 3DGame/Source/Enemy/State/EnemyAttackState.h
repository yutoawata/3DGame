#pragma once
#include "..\..\BaseClass\StateBase.h"

template<class Object>
//エネミーの攻撃状態クラス
class EnemyAttackState : public StateBase<Object> {
	//メンバ関数
public:
	//コンストラクタ
	EnemyAttackState(Object* holder_);
	//デストラクタ
	~EnemyAttackState();

	//攻撃状態の処理
	StateBase<Object>* Run() override;
};