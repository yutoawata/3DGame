#pragma once
#include "..\..\BaseClass\AIBase.h"

template<class Object>
class LongRangeAI : public AIBase<Object> {
	//メンバ関数
public:
	//コンストラクタ
	LongRangeAI(Object* holder_);
	//デストラクタ
	~LongRangeAI();

	//移動先を選択
	Vector3 SelectMovePosition() override;
	//攻撃可能判定処理
	bool CanAttack();
private:
	//移動先を生成
	void CrelateMovePosition();

	//メンバ定数
	static const int listSize = 5;			//angleListの要素数
	static const float angleList[listSize];	//ランダム生成する角度のリスト
	static const float POSITION_INTERVAL;	//移動先の座標更新の間隔
	static const float ATTACK_INTERVAL;		//攻撃の感覚
	static const float ATTACK_DISTANCE;		//攻撃する距離

	//メンバ変数
	Vector3 movePosition = Vector3::ZERO;	//移動先の座標
	Vector3 angle = Vector3::ZERO;			//回転角度
	float positionTimer = POSITION_INTERVAL;//座標更新のタイマー
	float attackTimer = 0;					//攻撃間隔のタイマー
	bool isAttack = false;					//攻撃中フラグ
};