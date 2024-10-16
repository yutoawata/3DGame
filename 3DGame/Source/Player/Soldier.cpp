#include "Soldier.h"
#include "..\Enemy\Mutant.h"

const int Soldier::ATTACK_SOUND = LoadSoundMem("Sound/Slash.mp3");

//コンストラクタ
Soldier::Soldier(Vector3 position_, int model_halde)
	: MoverBase(position_, Vector3(0.0f, DX_PI_F / 2.0f, 0.0f), Vector3(0.5f, 0.5f, 0.5f),
				model_halde, HIT_POINT, ATTACK_POINT, ObjectTag::PLAYER) {
	currentState = new IdleState<Soldier>(this);
	camera = new Camera(position);
	hitPointUI = new HPBar(Vector2(20, 1000), hitPoint, 800, 40, "プレイヤー");
	speed = 1.0f;
	rotation = Matrix::GetRotateMatrix(angle);
	modelSize = Vector3(10.0f, 40.0f, 10.0f);
	//モデルの当たり判定を追加
	AddCubeColliderList(new CubeCollider(&checkPosition, &rotation, modelSize));
	
	//攻撃用の当たり判定を置くモデルのフレームの座標を取得
	attackPosition = Vector3(MV1GetFramePosition(modelHandle, WEAPON_FRAME_NUM));
	//武器のボーンの座標変換行列を取得
	MATRIX transformMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, WEAPON_FRAME_NUM);
	//座標変換行列から回転要素を抽出
	Matrix rotationMatrix = GetRotationMatrix(Matrix(transformMatrix));
	weaponRotation = rotationMatrix;
	//攻撃用当たり判定を追加
	Vector3 weaponLength = Vector3(2.0f, 35.0f, 2.0f);
	weaponColliderNum = AddCubeColliderList(new CubeCollider(&attackPosition, &weaponRotation, weaponLength, ColliderBase::Type::WEAPON));
	cubeColliders[weaponColliderNum]->setIsActive(false);
	hitPointUI->setIsVisible(true);
}

//デストラクタ
Soldier::~Soldier() {
	delete camera;
	delete currentState;
	delete hitPointUI;
	camera = nullptr;
	currentState = nullptr;
	hitPointUI = nullptr;
	MV1DeleteModel(modelHandle);
	DeleteSoundMem(ATTACK_SOUND);
}

//更新前処理
void Soldier::Prepare() {
	//前方向ベクトルを算出
	frontDirection = Vector3(position - camera->getPosition());
	frontDirection.y = 0.0f;
	frontDirection = frontDirection.Normalized();

	//更新処理の前に移動後の座標を当たり判定用の座標に代入
	currentState = currentState->Run();
	checkPosition = currentState->getHolderPosition();

	//攻撃用の当たり判定を置くモデルのフレームの座標を取得
	attackPosition = Vector3(MV1GetFramePosition(modelHandle, WEAPON_FRAME_NUM));

	//武器のボーンの座標変換行列を取得
	MATRIX transformMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, WEAPON_FRAME_NUM);
	//座標変換行列から回転要素を抽出
	Matrix rotationMatrix = GetRotationMatrix(Matrix(transformMatrix));
	weaponRotation = rotationMatrix;

	angle = currentState->getHolderAngle();
	rotation = Matrix::GetRotateMatrix(angle);
	isGround = false;
	isCollision = false;
}

//更新処理
void Soldier::Update() {
	position = checkPosition;

	if (interbalTimer < damageInterbal) {
		interbalTimer += FPSManager::getInstance()->getDeltaTime();
	}

	if (!isDamage) {
		//現在のステートからアニメーションの種類を取得
		ChengeAnimation(currentState->getAnimationName());
	}

	if (isDamage && IsFinish()) {
		isDamage = false;
	}

	if (!CheckHitKey(KEY_INPUT_LALT)) {
		camera->Update(position);
	}
	
	nextAnimID = static_cast<int>(currentAnim);
	UpdateAnimation();
}

//描画処理
void Soldier::Draw() {
	MV1DrawModel(modelHandle);
}

//衝突判定時の処理
void Soldier::OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) {
	//ダメージを受ける以上たっていたら
	if (interbalTimer >= damageInterbal && currentAnim != Animation::AVOID) {
		if (collider_type == ColliderBase::Type::WEAPON) {
			int damage = 0;
			if (other_.getTag() == ObjectTag::ENEMY) {
				//ダメージ量を取得
				const MoverBase* enemy = other_.getComponent<MoverBase>();
				hitPoint -= enemy->getAttackPoint();
				//ダメージ間隔の計測をリセット
				damageInterbal = 1.0f;
				interbalTimer = 0;
				currentAnim = Animation::DAMAGE;
				isDamage = true;	
			}
		}
	}
	if (collider_type == ColliderBase::Type::BODY && CheckSoundMem(ATTACK_SOUND) == FALSE) {
		//攻撃効果音を最初からバックグラウンド再生
		PlaySoundMem(ATTACK_SOUND, DX_PLAYTYPE_BACK, TRUE);
	}
	if (other_.getTag() == ObjectTag::FIELD) {
		isGround = true;
	}
}

//アニメーションの遷移処理
void Soldier::ChengeAnimation(std::string animation_name) {

	if (animation_name == "Idle") {
		cubeColliders[weaponColliderNum]->setIsActive(false);
		currentAnim = Animation::IDLE;
	}
	else if (animation_name == "Move") {
		cubeColliders[weaponColliderNum]->setIsActive(false);
		currentAnim = Animation::WALK;
	}
	else if (animation_name == "Run") {
		cubeColliders[weaponColliderNum]->setIsActive(false);
		currentAnim = Animation::RUN;
	}
	else if (animation_name == "Jump") {
		cubeColliders[weaponColliderNum]->setIsActive(false);
		currentAnim = Animation::JUMP;
	}
	else if (animation_name == "Avoid") {
		cubeColliders[weaponColliderNum]->setIsActive(false);
		currentAnim = Animation::AVOID;
	}
	else if (animation_name == "Attack") {
		cubeColliders[weaponColliderNum]->setIsActive(true);
		currentAnim = Animation::ATTACK;
	}
	else {
		//対象外の文字列が渡された際のデバック処理記入用
	}
}
