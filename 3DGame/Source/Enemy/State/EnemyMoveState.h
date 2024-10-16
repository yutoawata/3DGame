#pragma once
#include "..\..\BaseClass\StateBase.h"

template<class Object>
class EnemyMoveState : public StateBase<Object> {
	//メンバ関数
public:
	//コンストラクタ
	EnemyMoveState(Object* holder_);
	
	//デストラクタ
	~EnemyMoveState();

	//移動状態の処理
	StateBase<Object>* Run() override;
private:
	//追跡処理
	void Move();
	//回転処理
	void Rotate();

	//メンバ変数
	Vector3 moveVector = Vector3::ZERO;	//移動方向
	int nextRuteIndex = 0;				//徘徊時の移動先の座標の要素番号
	bool isStop = false;				//目的地到着フラグ
};
