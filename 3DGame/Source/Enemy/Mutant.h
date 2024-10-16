#pragma once
#include "..\BaseClass\MoverBase.h"
#include "..\Collider\ObjectCollider.h"
#include "Strategy\BossAI.h"
#include "State/EnemyIdleState.h"
#include "..\UI\HPBar.h"

class Mutant : public MoverBase {
	enum class Animation {
		ATTACK,
		DAMAGE,
		DIE,
		IDLE,
		JUMP,
		RUN,
		WALK
	};
public://メンバ関数
	//コンストラクタ
	Mutant(MoverBase* target_, Vector3 position_ = Vector3(200.0f, 80.0f, 200.0f), int model_handle = MV1LoadModel("3DModel/Enemy.mv1"));
	//デストラクタ
	~Mutant();

	//アクセサ
	template<class Object>
	BossAI<Object>* getAI() const { return AI; }

	//更新前処理
	void Prepare() override;
	//更新処理
	void Update() override;
	//描画処理
	void Draw() override;
	
private:
	//衝突時の処理
	void OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) override;
	//目標の発見判定
	void CheckFind();
	//アニメーションの遷移処理
	void ChengeAnimation(std::string animation_name);

	//メンバ定数
	static const int WEAPON_FRAME_NUM = 13;	//武器のフレーム番号
	static const int HIT_POINT = 600;		//hitPointの最大値
	static const int ATTACK_POINT = 10;		//攻撃力
	static const float MOVE_SPEED;			//移動速度
	static const float SEARCH_DISTANCE;		//索敵範囲

	//メンバ変数
	StateBase<Mutant>* currentState = nullptr;//現在のステート
	BossAI<Mutant>* AI = nullptr;			//ボスえめっみー用のAI
	HPBar* hitPointUI = nullptr;			//HPバー
	Animation currentAnim = Animation::IDLE;//現在のアニメーション
	Vector3 weaponPosition = Vector3::ZERO;	//攻撃用のオブジェクトの座標
	Matrix weaponRotation = Matrix::INDENT;	//攻撃用のオブジェクトの回転行列
	int attackColliderNum = 0;				//攻撃用のオブジェクトのコライダーの要素番号
	float attackInterval = 0.0f;			//ダメージを与える間隔
	float intervalTimer = 0.0f;				//攻撃間隔の時間を計測するタイマー
	bool isCollision = false;				//衝突フラグ
	bool isDamage = false;					//ダメージフラグ
};
