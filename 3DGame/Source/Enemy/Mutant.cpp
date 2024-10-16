#include "Mutant.h"
#include "..\Player\Soldier.h"

const float Mutant::MOVE_SPEED = 80.0f;
const float Mutant::SEARCH_DISTANCE = 180.0f;

//コンストラクタ
Mutant::Mutant(MoverBase* target_, Vector3 position_, int model_handle)
	: MoverBase(position_, Vector3::ZERO, Vector3(1.0f, 1.0f, 1.0f), model_handle, HIT_POINT, ATTACK_POINT,ObjectTag::ENEMY) {
	currentState = new EnemyIdleState<Mutant>(this);
	rotation = Matrix::GetRotateMatrix(angle);
	target = target_;
	speed = MOVE_SPEED;
	modelSize = Vector3(30.0f, 80.0f, 30.0f);
	isFind = true;
	AI = new BossAI<Mutant>(this);
	hitPointUI = new HPBar(Vector2(400, 50), hitPoint, 1000, 50, "ミュータント");
	//モデルの当たり判定を追加
	AddCubeColliderList(new CubeCollider(&checkPosition, &rotation, modelSize));

	////攻撃用の当たり判定を置くモデルのフレームの座標を取得
	weaponPosition = Vector3(MV1GetFramePosition(modelHandle, WEAPON_FRAME_NUM));
	//MATRIX matrix = MV1GetFrameLocalMatrix(modelHandle, WEAPON_FRAME_NUM);
	weaponRotation = Matrix(MV1GetFrameLocalMatrix(modelHandle, WEAPON_FRAME_NUM));
	////攻撃用当たり判定を追加
	Vector3 length = Vector3(20.0f, 50.0f, 20.0f);
	attackColliderNum = AddCubeColliderList(new CubeCollider(&weaponPosition, &weaponRotation, length, ColliderBase::Type::WEAPON));
}

//デストラクタ
Mutant::~Mutant() {
	delete AI;
	delete currentState;
	delete hitPointUI;
}

//更新前処理
void Mutant::Prepare() {
	
	if (!isDamage) {
		currentState = currentState->Run();
	}
	
	//ステートでの変更を取得
	checkPosition = currentState->getHolderPosition();
	angle = currentState->getHolderAngle();
	rotation = Matrix::GetRotateMatrix(angle);

	//前方向ベクトルを算出
	frontDirection = Vector3(target->getPosition() - position).Normalized();
	frontDirection.y = 0.0f;

	//攻撃用の当たり判定を置くモデルのフレームの座標を取得
	weaponPosition = Vector3(MV1GetFramePosition(modelHandle, WEAPON_FRAME_NUM));
	
	//武器のボーンの座標変換行列を取得
	MATRIX transformMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, WEAPON_FRAME_NUM);
	//座標変換行列から回転要素を抽出
	Matrix rotationMatrix = GetRotationMatrix(Matrix(transformMatrix));
	weaponRotation = rotationMatrix;

	isGround = false;
	isCollision = false;
}

//更新処理
void Mutant::Update() {

	position = checkPosition;

	if (intervalTimer < attackInterval) {
		//ダメージを与える間隔のタイマーを加算する
		intervalTimer += FPSManager::getInstance()->getDeltaTime();
	}
	
	if (!isDamage) {
		//現在のステートからアニメーションの種類を取得
		ChengeAnimation(currentState->getAnimationName());
	}
	//現在のアニメーションを保存
	nextAnimID = static_cast<int>(currentAnim);

	//ダメージ状態が終了したなら
	if (isDamage && IsFinish()) {
		isDamage = false;
	}

	//プレイヤーを発見したなら
	if (isFind) {
		//HPバーを表示
		hitPointUI->setIsVisible(true);
	}
	else {
		//HPバーを非表示
		hitPointUI->setIsVisible(false);
	}

	//HPが0になったなら
	if (hitPoint == 0) {
		currentAnim = Animation::DIE;
	}

	//アニメーション更新処理
	UpdateAnimation();

	CheckFind();
}

//描画処理
void Mutant::Draw() {
	MV1DrawModel(modelHandle);
}

//衝突判定時の処理
void Mutant::OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) {
	if (intervalTimer >= attackInterval) {
		//衝突相手が攻撃用の当たり判定　かつ　同じタグでないなら
		if (collider_type == ColliderBase::Type::WEAPON && other_.getTag() != tag) {
			int damage = 0;
			//衝突相手がプレイヤーなら
			if (other_.getTag() == ObjectTag::PLAYER) {
				//衝突相手の攻撃力を取得する
				const Soldier* player = other_.getComponent<Soldier>();
				damage = player->getAttackPoint();
				currentAnim = Animation::DAMAGE;
				isDamage = true;
			}
			hitPoint -= damage;
			intervalTimer = 0.0f;
			attackInterval = 1.0f;
		}
	}
}

//アニメーションの遷移処理
void Mutant::ChengeAnimation(std::string animation_name) {

	if (animation_name == "Idle") {
		cubeColliders[attackColliderNum]->setIsActive(false);
		currentAnim = Animation::IDLE;
	}
	else if (animation_name == "Move") {
		cubeColliders[attackColliderNum]->setIsActive(false);
		currentAnim = Animation::WALK;
	}
	else if (animation_name == "Run") {
		cubeColliders[attackColliderNum]->setIsActive(false);
		currentAnim = Animation::RUN;
	}
	else if (animation_name == "Jump") {
		cubeColliders[attackColliderNum]->setIsActive(false);
		currentAnim = Animation::JUMP;
	}
	else if (animation_name == "DIE") {
		cubeColliders[attackColliderNum]->setIsActive(false);
		currentAnim = Animation::DIE;
	}
	else if (animation_name == "Attack") {
		cubeColliders[attackColliderNum]->setIsActive(true);
		currentAnim = Animation::ATTACK;
	}
	else {
		//対象外の文字列が渡された際のデバック処理記入用
	}
}

void Mutant::CheckFind() {
	Vector3 distance = target->getPosition() - position;
	isFind =  (distance.getSize() <= SEARCH_DISTANCE);
}