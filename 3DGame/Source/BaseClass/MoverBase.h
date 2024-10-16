#pragma once
#include "DxLib.h"
#include "AIBase.h"
#include "..\Collider\ObjectCollider.h"
#include "..\Animation\Animator.h"

//移動オブジェクトの基底クラス
class MoverBase : public ObjectCollider, public Animator {
	//メンバ関数
public:
	//コンストラクタ
	MoverBase(int model_handle, ObjectTag tag_);
	MoverBase(Vector3 position_, int model_handle, ObjectTag tag_);
	MoverBase(Vector3 position_, Vector3 angle_, Vector3 scale_, int model_handle,  int hit_point, int attack_point,
				ObjectTag tag_);
	//デストラクタ
	virtual ~MoverBase();

	//アクセサ
	
	//オブジェクトがアクションを起こす相手を返す
	MoverBase* getTarget() const { return target; }
	//前方の方向ベクトルを返す
	Vector3 getFrontDirection() const { return frontDirection; }
	//HPを返す
	int getHitPoint() const { return hitPoint; }
	//攻撃力を返す
	int getAttackPoint() const { return attackPoint; }
	//移動速度を返す
	float getSpeed() const { return speed; }
	//接地フラグを返す
	bool IsGround() const { return isGround; }
	//目標発見フラグを返す
	bool IsFind() const { return isFind; }
public:
	//更新前処理
	virtual void Prepare() = 0;
	//更新処理
	virtual void Update() = 0;
	//描画処理
	virtual void Draw() = 0;

	//メンバ変数
protected:
	MoverBase* target = nullptr;			//目標となるオブジェクト
	Vector3 moveVector = Vector3::ZERO;		//オブジェクトの移動方向
	Vector3 frontDirection = Vector3::ZERO;	//前方の方向ベクトル
	int hitPoint = 0;						//オブジェクトのHP
	int attackPoint = 0;					//攻撃力
	float speed = 0.0f;						//移動速度
	bool isGround = false;					//接地フラグ
	bool isGravity = false;					//重力の影響を受けるフラグ
	bool isFind = false;					//発見フラグ
};