#include "MoverBase.h"
#include "..\ManagerClass\MoverManager.h"

//コンストラクタ
MoverBase::MoverBase(int model_handle, ObjectTag tag_)
	: ObjectCollider(tag_), Animator(model_handle) {
	MoverManager::getInstance()->AddList(this);
}

//コンストラクタ
MoverBase::MoverBase(Vector3 position_, int model_handle, ObjectTag tag_)
	: ObjectCollider(tag_), Animator(position_, model_handle) {
	MoverManager::getInstance()->AddList(this);
}

//コンストラクタ
MoverBase::MoverBase(Vector3 position_, Vector3 angle_, Vector3 scale_,
						int model_handle, int hit_point, int attack_point, ObjectTag tag_)
	: ObjectCollider(tag_), Animator(position_, angle_, scale_, model_handle) {
	hitPoint = hit_point;
	attackPoint = attack_point;
	MoverManager::getInstance()->AddList(this);
}

//デストラクタ
MoverBase::~MoverBase() {}