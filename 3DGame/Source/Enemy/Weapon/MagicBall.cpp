#include "MagicBall.h"
#include "..\..\ManagerClass\FPSManager.h"

const float MagicBall::ACTIVE_TIME = 5.0f;
const float MagicBall::IDLING_TIME = 2.0f;

//コンストラクタ
MagicBall::MagicBall(Vector3 position_, Vector3 direction_, float high_, int model_handle)
	: MoverBase(position_, model_handle, ObjectTag::ENEMY){
	direction = direction_.Normalized();
	scale = Vector3(0.3f, 0.3f, 0.3f);
	position = position_ + (direction * radius);
	rotation = Matrix::GetRotateMatrix(angle);
	modelSize = Vector3(radius, radius, radius);
	high = high_;
	attackPoint = 15;
	AddSphereColliderList(new SphereCollider(&position, &rotation, radius, ColliderBase::Type::WEAPON));
	Inactivate();
}

//デストラクタ
MagicBall::~MagicBall() {}

//更新前処理
void MagicBall::Prepare() {
	//オブジェクトと出現状態を同期
	sphereColliders[colliderNum]->setIsActive(isActive);
}

//更新処理
void MagicBall::Update() {

	if (isActive) {
		timer += FPSManager::getInstance()->getDeltaTime();
		UpdateAnimation();
		
		//待機時間を過ぎたら
		if (timer >= IDLING_TIME) {
			//移動方向へ進む
			position += direction.Normalized() * speed * FPSManager::getInstance()->getDeltaTime();
		}
		else if (timer >= ACTIVE_TIME) {//出現時間を過ぎたら
			Inactivate();//非アクティブ化する
		}
	}
}

//描画処理
void MagicBall::Draw() {
	if (isActive) {
		MV1DrawModel(modelHandle);
	}
}

//衝突判定時の処理
void MagicBall::OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) {

	if (other_.getTag() == ObjectTag::PLAYER) {
		Inactivate();
	}
}

//アクティブ化処理
void MagicBall::Activate(Vector3 position_, Vector3 direction_) {
	direction = direction_.Normalized();
	position = position_ + (direction * radius);
	position.y += high;
	isActive = true;
}

//非アクティブ化処理
void MagicBall::Inactivate() {
	isActive = false;
	isBrake = true;
	sphereColliders[colliderNum]->setIsActive(isActive);
	timer = 0.0f;
}