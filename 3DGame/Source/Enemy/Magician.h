#pragma once
#include <string>
#include "Strategy/LongRangeAI.h"
#include "Weapon/MagicBall.h"
#include "..\BaseClass\MoverBase.h"
#include "..\BaseClass\StateBase.h"
#include "..\UI\HPBar.h"

//魔術師クラス
class Magician : public MoverBase {
	//列挙型
	enum class Animation {
		ATTACK,
		DAMAGE,
		DIE,
		IDLE,
		RUN,
	};
	//メンバ関数
public:
	//コンストラクタ
	Magician(MoverBase* target_, MoverBase* boss_, Vector3 position_, int model_handle = MV1LoadModel("3DModel/Magician.mv1"));
	//デストラクタ
	~Magician();

	//アクセサ

	
	template<class Object>
	//行動AIクラスを返す
	LongRangeAI<Object>* getAI() const { return AI; }

	MagicBall* getMagic() const { return lightBall; }

	bool IsFind() { return isFind; }

	//更新前処理
	void Prepare() override;
	//更新処理
	void Update() override;
	//描画処理
	void Draw() override;

private:
	//衝突判定時の処理
	void OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) override;
	//アニメーションの遷移処理
	void ChengeAnimation(std::string animation_name);

	//メンバ定数
	static const int HIT_POINT = 1000;	//hitPointの最大値

	//メンバ変数
	LongRangeAI<Magician>* AI = nullptr;		//遠距離攻撃用のAI
	MoverBase* boss = nullptr;					//ボスオブジェクト
	StateBase<Magician>* currentState = nullptr;//現在のステート
	MagicBall* lightBall = nullptr;				//攻撃用の光弾
	HPBar* hitPointUI = nullptr;				//HPバーUI
	Animation currentAnim = Animation::IDLE;	//現在のアニメーション
	float damageInterbal = 0.0f;				//ダメージを受ける間隔
	float interbalTimer = 0.0f;					//間隔の時間を測るタイマー
	bool isCollision = false;					//衝突フラグ
	bool isDamage = false;						//ダメージフラグ
	bool canCreate = false;						//攻撃魔法の生成フラグ
};