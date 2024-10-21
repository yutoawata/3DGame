#pragma once
#include "..\..\BaseClass\MoverBase.h"

class MagicBall : public MoverBase {
	//メンバ関数
public:
	//コンストラクタ
	MagicBall(Vector3 position_, Vector3 direction_, float high_, int model_handle = MV1LoadModel("3DModel/LightBall.mv1"));
	//デストラクタ
	~MagicBall();

	//アクセサ

	//処理フラグを返す
	bool IsActive() { return isActive; }

	//更新前処理
	void Prepare() override;
	//更新処理
	void Update() override;
	//描画処理
	void Draw() override;
private:
	//衝突判定時の処理
	void OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) override;
	//非アクティブ化処理
	void Inactivate();
public:
	//アクティブ化処理
	void Activate(Vector3 position_, Vector3 direction_);

	//メンバ定数
private:
	static const float ACTIVE_TIME;//アクティブ状態の制限時間
	static const float IDLING_TIME;//待機状態の制限時間

	//メンバ変数
	Vector3 direction = Vector3::ZERO;	//移動方向
	int colliderNum = 0;				//攻撃用のコライダー要素番号
	float speed = 200.0f;				//移動速度
	float radius = 30.0f;				//半径
	float high = 0.0f;					//発射位置の高さ
	float timer = 0.0f;					//タイマー
	bool isActive = false;				//処理フラグ
	bool isBrake = false;				//消滅フラグ
};