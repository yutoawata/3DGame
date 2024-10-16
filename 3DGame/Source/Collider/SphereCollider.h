#pragma once
#include "..\BaseClass\ColliderBase.h"

//球形の当たり判定情報クラス
class SphereCollider : public ColliderBase {
	//メンバ関数
public:
	//コンストラクタ
	SphereCollider(Vector3* position_,  Matrix* rotation_, float radius_, Type tag_ = Type::BODY);

	//アクセサ

	//半径を返す
	float getRadius() const { return radius; }

	//メンバ変数
private:
	float radius = 0;//半径
};