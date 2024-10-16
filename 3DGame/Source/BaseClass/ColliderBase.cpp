#include "ColliderBase.h"

//�R���X�g���N�^
ColliderBase::ColliderBase(Vector3* position_, Type type_) {
	position = position_;
	latePosition = *position;
	type = type_;
}

//�R���X�g���N�^
ColliderBase::ColliderBase(Vector3* position_, Matrix* rotation_, Type type_) {
	position = position_;
	rotationMatrix = rotation_;
	latePosition = *position;
	type = type_;
}

//�f�X�g���N�^
ColliderBase::~ColliderBase() {}

//�X�V����
void ColliderBase::Update() {
	Vector3 newPosition = *position;
	moveVector = newPosition - latePosition;
	latePosition = newPosition;
}