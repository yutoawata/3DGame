#pragma once
#include "..\BaseClass\MoverBase.h"
#include "..\BaseClass\StateBase.h"
#include "..\Color\Color.h"

template<class Object>
//待機状態クラス
class IdleState : public StateBase<Object> {
public:
	//コンストラクタ
	IdleState(Object* holder_);

	//デストラクタ
	~IdleState();

	//更新処理
	StateBase<Object>* Run() override;
	//移動判定処理
	bool IsMove();
};