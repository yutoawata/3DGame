#include "Magician.h"
#include "State\EnemyIdleState.h"
#include "..\Player\Soldier.h"

//コンストラクタ
Magician::Magician(MoverBase* target_, MoverBase* boss_, Vector3 position_, int model_handle)
	: MoverBase(model_handle, ObjectTag::ENEMY) {
	position = Vector3(300.0f, 50.0f, 300.0f);
	scale = Vector3(0.5f, 0.5f, 0.5f);
	rotation = Matrix::GetRotateMatrix(angle);
	target = target_;
	boss = boss_;
	hitPoint = 100;
	speed = 80.0f;
	modelSize = Vector3(20.0f, 50.0f, 20.0f);
	lightBall = new MagicBall(position, target->getPosition() - position, modelSize.y);
	currentState = new EnemyIdleState<Magician>(this);
	AI = new LongRangeAI<Magician>(this);
	hitPointUI = new HPBar(Vector2(400, 50), hitPoint, 1000, 50, "魔術師");
	AddCubeColliderList(new CubeCollider(&checkPosition, &rotation, modelSize));
	isFind = true;
}

//デストラクタ
Magician::~Magician() {
	delete AI;
	delete currentState;
	delete hitPointUI;
	delete lightBall;
	AI = nullptr;
	currentState = nullptr;
	hitPointUI = nullptr;
	lightBall = nullptr;
}

//更新前処理
void Magician::Prepare() {
	if (!isDamage) {
		currentState = currentState->Run();
	}
	
	if (lightBall->IsActive()) {
		lightBall->Prepare();
	}
	//ステートでの変更を保存
	checkPosition = currentState->getHolderPosition();
	angle = currentState->getHolderAngle();
	rotation = Matrix::GetRotateMatrix(angle);
	
	//前方向ベクトルを取得
	frontDirection = Vector3(target->getPosition() - position).Normalized();
	frontDirection.y = 0.0f;
}

//更新処理
void Magician::Update() {
	position = checkPosition;
	
	if (interbalTimer < damageInterbal) {
		interbalTimer += FPSManager::getInstance()->getDeltaTime();
	}

	if (!isDamage) {
		//現在のステートからアニメーションの種類を取得
		ChengeAnimation(currentState->getAnimationName());
	}
	else {
		if (IsFinish()) {
			isDamage = false;
		}
	}
	nextAnimID = static_cast<int>(currentAnim);

	//アニメーション更新処理
	UpdateAnimation();
	
	//攻撃魔法の更新処理
	lightBall->Update();

	if (hitPoint == 0) {
		ChengeAnimation("DIE");
	}

	//発見状態なら
	if (isFind) {
		//ボスのHPバー場表示されていなければ
		if (!boss->IsFind()) {
			//HPバーを表示
			hitPointUI->setIsVisible(true);
		}
		else {
			//HPバーを非表示
			hitPointUI->setIsVisible(false);
		}
	}
	else {
		//HPバーを非表示
		hitPointUI->setIsVisible(false);
	}
}

//描画処理
void Magician::Draw() {
	MV1DrawModel(modelHandle);
	lightBall->Draw();
}

//衝突判定時の処理
void Magician::OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) {
	if (interbalTimer >= damageInterbal) {
		//衝突相手が攻撃用の当たり判定　かつ　同じタグでないなら
		if (collider_type == ColliderBase::Type::WEAPON && other_.getTag() != tag) {
			int damage = 0;
			//衝突相手がプレイヤーなら
			if (other_.getTag() == ObjectTag::PLAYER) {
				//衝突相手の攻撃力を取得する
				const Soldier* player = other_.getComponent<Soldier>();
				damage = player->getAttackPoint();
			}
			hitPoint -= damage;
			interbalTimer = 0.0f;
			damageInterbal = 1.0f;
			currentAnim = Animation::DAMAGE;
			isDamage = true;
		}
	}
}

void Magician::ChengeAnimation(std::string animation_name) {

	if (animation_name == "Idle") {
		canCreate = true;
		currentAnim = Animation::IDLE;
	}
	else if (animation_name == "Move") {
		currentAnim = Animation::RUN;
	}
	else if (animation_name == "DIE") {
		currentAnim = Animation::DIE;
	}
	else if (animation_name == "Attack") {
		//光弾を発射していない　かつ　生成フラグ他trueなら
		if (!lightBall->IsActive() && canCreate) {
			currentAnim = Animation::ATTACK;
			Vector3 direction = target->getPosition() - position;
			lightBall->Activate(position, direction.Normalized());
			canCreate = false;
		}
	}
	else {
		//対象外の文字列が渡された際のデバック処理記入用
	}
}