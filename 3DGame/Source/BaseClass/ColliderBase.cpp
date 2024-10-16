#include "ColliderBase.h"

//コンストラクタ
ColliderBase::ColliderBase(Vector3* position_, Type type_) {
	position = position_;
	latePosition = *position;
	type = type_;
}

//コンストラクタ
ColliderBase::ColliderBase(Vector3* position_, Matrix* rotation_, Type type_) {
	position = position_;
	rotationMatrix = rotation_;
	latePosition = *position;
	type = type_;
}

//デストラクタ
ColliderBase::~ColliderBase() {}

//更新処理
void ColliderBase::Update() {
	Vector3 newPosition = *position;
	moveVector = newPosition - latePosition;
	latePosition = newPosition;
}