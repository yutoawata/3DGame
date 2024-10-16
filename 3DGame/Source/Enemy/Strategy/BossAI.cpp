#include "..\Strategy\BossAI.h"
#include "..\Mutant.h"
#include "..\Magician.h"

//テンプレートコンストラクタを実体化
template class BossAI<Mutant>;
template class BossAI<Magician>;

template<class Object >
const float BossAI<Object>::ATTACK_RANGE = 180.0f;//攻撃距離

template<class Object>
//コンストラクタ
BossAI<Object>::BossAI(Object* holder_)
	: AIBase<Object>(holder_) {
	this->routeList = { Vector3(100.0f,0.0f,100.0f), Vector3(-100.0f,0.0f,-100.0f) };
}

template<class Object>
//移動目標の座標を選択
Vector3 BossAI<Object>::SelectMovePosition() {
	Vector3 targetPosition = Vector3::ZERO;

	if (this->holder->getTarget() != nullptr) {
		targetPosition = this->holder->getTarget()->getPosition();	
	}

	Vector3 direction = targetPosition - this->holder->getPosition();

	//1フレームでの移動量
	float moveSpeed = this->holder->getSpeed() * FPSManager::getInstance()->getDeltaTime();

	//目的地が1フレームでの移動量より近ければ
	if (direction.getSize() <= moveSpeed) {
		//目的地を自身の座標にして、移動しないようにする
		targetPosition = this->holder->getPosition();
	}

	return targetPosition;
}


template<class Object>
//攻撃可能判定処理
bool BossAI<Object>::CanAttack() {
	this->targetPosition = this->holder->getTarget()->getPosition();

	//発見状態 かつ 攻撃範囲内なら
	if (this->holder->IsFind() && (this->targetPosition - this->holder->getPosition()).getSize() <= ATTACK_RANGE) {
		return true;//攻撃可能
	}
	return false;
}