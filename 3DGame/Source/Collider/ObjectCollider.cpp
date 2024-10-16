#include "ObjectCollider.h"
#include "..\ManagerClass\ColliderManager.h"

//�R���X�g���N�^
ObjectCollider::ObjectCollider(ObjectTag tag_) {
	tag = tag_;
	ColliderManager::getInstance()->AddList(this);
}

//�f�X�g���N�^
ObjectCollider::~ObjectCollider() {
	for (CubeCollider* collider: cubeColliders) {
		delete collider;
	}
	for (SphereCollider* collider : sphereColliders) {
		delete collider;
	}

	cubeColliders.clear();
	sphereColliders.clear();
}

//CubeCollider�p��Collider�o�^����
int ObjectCollider::AddCubeColliderList(CubeCollider* add_collider) {
	cubeColliders.emplace_back(add_collider);
	//�ۑ����ꂽ�v�f�ԍ����擾
	int indexNum = static_cast<int>(cubeColliders.size()) - 1;
	return indexNum;
}

//SphereCollider�p��Colidert�o�^����
int ObjectCollider::AddSphereColliderList(SphereCollider* add_collider) {
	sphereColliders.emplace_back(add_collider);
	//�ۑ����ꂽ�v�f�ԍ����擾
	int indexNum = static_cast<int>(sphereColliders.size()) - 1;
	return indexNum;
}