#pragma once
#include "..\..\BaseClass\AIBase.h"

template<class Object>
class BossAI : public AIBase<Object> {
	//メンバ関数
public:
	//コンストラクタ
	BossAI(Object* holider_);

	//移動先を選択
	Vector3 SelectMovePosition() override;
	//攻撃可能判定処理
	bool CanAttack();

private:
	static const float ATTACK_RANGE;//攻撃距離
	
	//メンバ変数
	int ruteNum = 0;//移動先の順路の要素番号
};