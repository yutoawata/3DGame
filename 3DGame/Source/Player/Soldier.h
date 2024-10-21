#pragma once
#include <string>
#include "..\BaseClass\MoverBase.h"
#include "..\State\IdleState.h"
#include "..\Camera\Camera.h"
#include "..\Collider\ObjectCollider.h"
#include "..\UI\HPBar.h"

class MoverBase;

class Soldier : public MoverBase {
public://メンバ関数
	enum class Animation {
		ATTACK,
		AVOID,
		DAMAGE,
		DIE,
		IDLE,
		JUMP,
		RUN,
		WALK
	};

	//コンストラクタ
	Soldier(Vector3 position_ = Vector3(0.0f, 40.0f, 0.0f), int model_handle = MV1LoadModel("./3DModel/Player.mv1"));
	//デストラクタ
	~Soldier();
	
	//更新前処理
	void Prepare() override;
	//更新処理
	void Update() override;
	//描画処理
	void Draw() override;
	//衝突判定時の処理
	void OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) override;

private:
	//アニメーションの遷移処理
	void ChengeAnimation(std::string animation_name);
	 
	//メンバ定数
	static const int WEAPON_FRAME_NUM = 75;	//武器のフレーム番号
	static const int HIT_POINT = 100;		//hitPointの最大値
	static const int ATTACK_POINT = 10;		//攻撃力
	static const int ATTACK_SOUND;			//攻撃時の効果音
	static const float MOVE_SPEED;			//移動速度
	static const float GAVITY_POWER;		//重力の強さ

	//メンバ変数
	Camera* camera = nullptr;					//カメラオブジェクト
	StateBase<Soldier>* currentState = nullptr;	//現在のステート
	HPBar* hitPointUI = nullptr;				//HPバー
	Animation currentAnim = Animation::IDLE;	//現在のアニメーション
	Vector3 attackPosition = Vector3::ZERO;		//攻撃の当たり判定の位置
	Matrix weaponRotation;						//攻撃の当たり判定の回転行列
	int weaponColliderNum = 0;					//攻撃の当たり判定の要素番号
	float damageInterbal = 0;					//ダメージを受ける間隔
	float interbalTimer = 0;					//間隔のタイマー
	bool isCollision = false;					//衝突グラグ
	bool isDamage = false;						//ダメージフラグ
};