#pragma once
#include "..\BaseClass\StateBase.h"
#include "..\Collider\ObjectCollider.h"
#include "..\Collider\CubeCollider.h"
#include "..\Color\Color.h"

template<class Object>
//攻撃状態クラス
class AttackState : public StateBase<Object> {
public:
	//コンストラクタ
	AttackState(Object* holder_);

	//デストラクタ
	~AttackState();

	//更新処理
	StateBase<Object>* Run() override;
};