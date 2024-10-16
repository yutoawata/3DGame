#include "ObjectCollider.h"
#include "..\ManagerClass\ColliderManager.h"

//コンストラクタ
ObjectCollider::ObjectCollider(ObjectTag tag_) {
	tag = tag_;
	ColliderManager::getInstance()->AddList(this);
}

//デストラクタ
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

//CubeCollider用のCollider登録処理
int ObjectCollider::AddCubeColliderList(CubeCollider* add_collider) {
	cubeColliders.emplace_back(add_collider);
	//保存された要素番号を取得
	int indexNum = static_cast<int>(cubeColliders.size()) - 1;
	return indexNum;
}

//SphereCollider用のColidert登録処理
int ObjectCollider::AddSphereColliderList(SphereCollider* add_collider) {
	sphereColliders.emplace_back(add_collider);
	//保存された要素番号を取得
	int indexNum = static_cast<int>(sphereColliders.size()) - 1;
	return indexNum;
}