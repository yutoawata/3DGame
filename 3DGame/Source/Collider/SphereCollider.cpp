#include "SphereCollider.h"

//�R���X�g���N�^
SphereCollider::SphereCollider(Vector3* position_, Matrix* rotation_, float radius_, Type tag_)
	: ColliderBase(position_, rotation_, tag_) {
	radius = radius_;
}