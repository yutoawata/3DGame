#pragma once
#include "..\Color\Color.h"
#include "..\BaseClass\StateBase.h"


template<class Object>
class MoveState : public StateBase<Object> {
public://メンバ関数
	//コンストラクタ
	MoveState(Object* holder_);

	//デストラクタ
	~MoveState();
	
	StateBase<Object>* Run() override;
	
private:
	//移動処理
	Vector3 Move();	//移動処理
	Vector3 Jump();	//ジャンプ処理
	Vector3 Avoid();//回避処理
	void Rotate();	//回転処理

	//メンバ定数
	static const float MOVE_SPEED;	//移動速度
	static const float JUMP_POWER;	//ジャンプ時の力
	static const float AVOID_SPEED;	//回避時の速度

	//メンバ変数
	Vector3 moveVector = Vector3::ZERO;	//移動時の座標変位
	Vector3 jumpVector = Vector3::ZERO;	//ジャンプ時の座標変位
	Vector3 avoidVector = Vector3::ZERO;//回避時の座標変位
	Vector3 angle = Vector3::ZERO;		//各軸の回転量
	bool isMove = false;				//移動フラグ
	bool isJump = false;				//ジャンプ中フラグ
	bool isAvoid = false;				//回避中フラグ
	bool isRun = false;					//走行中フラグ
};