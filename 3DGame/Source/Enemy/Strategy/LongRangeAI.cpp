#include "LongRangeAI.h"
#include "DxLib.h"
#include "..\..\Enemy\Mutant.h"
#include "..\..\Enemy\Magician.h"

//テンプレートコンストラクタを実体化
template class LongRangeAI<Magician>;

template<class Object>
const float LongRangeAI<Object>::angleList[listSize] = {
		DX_PI_F / 2,//90
		DX_PI_F / 3,//60
		DX_PI_F / 4,//45
		DX_PI_F / 5,//30
		DX_PI_F / 6 //15
};
template<class Object>
const float LongRangeAI<Object>::POSITION_INTERVAL = 10.0f;
template<class Object>
const float LongRangeAI<Object>::ATTACK_INTERVAL = 3.0f;
template<class Object>
const float LongRangeAI<Object>::ATTACK_DISTANCE = 200.0f;

template<class Object>
//コンストラクタ
LongRangeAI<Object>::LongRangeAI(Object* holder_)
	: AIBase<Object>(holder_){}

template<class Object>
//デストラクタ
LongRangeAI<Object>::~LongRangeAI() {}

template<class Object>
//移動先を選択
Vector3 LongRangeAI<Object>::SelectMovePosition() {

	CrelateMovePosition();
	Vector3 result = movePosition;

	//目的地までの距離を算出
	float distance = (movePosition - this->holder->getPosition()).getSize();
	
	//距離が近ければ
	if (distance <= 0.1f) {
		//自身の座標を代入
		result = this->holder->getPosition();
	}

	return result;
}

template<class Object>
//移送先の座標をを生成
void LongRangeAI<Object>::CrelateMovePosition() {

	positionTimer += FPSManager::getInstance()->getDeltaTime();
	//座標の更新時間になったら
	if (positionTimer >= POSITION_INTERVAL) {
		int max = (listSize - 1) * 2;	//乱数の最大値(角度のリストの要素数の二倍(+ or -))
		int randIndex = CreateRandom(0, max);
		float resultAngle = 0.0f;		//移動先の座標を決める角度

		if (max / 2 > randIndex) {
			resultAngle = this->angleList[randIndex % 2];
		}
		else {
			resultAngle = -this->angleList[randIndex % 2];
		}
		angle.y = resultAngle + this->holder->getTarget()->getAngle().y;

		Vector3 vec = this->holder->getPosition() - this->holder->getTarget()->getPosition();

		vec = vec.Normalized() * ATTACK_DISTANCE;

		Vector3 vector = Matrix::GetRotateMatrix(angle) * vec;
		movePosition = this->targetPosition + vector;
		positionTimer = 0;
	}
}


template<class Object>
//攻撃が可能かの判定処理
bool LongRangeAI<Object>::CanAttack() {
	attackTimer += FPSManager::getInstance()->getDeltaTime();
	if (!this->holder->getMagic()->IsActive()&& attackTimer >= ATTACK_INTERVAL) {
		attackTimer = 0.0f;
		return true;
	}

	return false;
}