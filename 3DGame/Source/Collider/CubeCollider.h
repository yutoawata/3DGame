#pragma once
#include <vector>
#include "..\Color\Color.h"
#include "..\Math\Matrix.h"
#include "..\BaseClass\ColliderBase.h"

//立方体の当たり判定情報クラス
class CubeCollider : public ColliderBase {
public://メンバ関数
	////移動する当たり判定の場合のコンストラクタ
	CubeCollider(Vector3* position_, Matrix* rotation_, Vector3 length_, Type tag_ = Type::BODY);
	//移動しない当たり判定の場合のコンストラクタ
	CubeCollider(Vector3 position_, Matrix rotation_, Vector3 length_, Type tag_ = Type::BODY);

	//アクセサ
	//指定した番号(x = 0, y = 1, z = 2)の軸の方向ベクトル(単位ベクトル)を返す
	Vector3 getDirectoin(int num_) const { return *rotationMatrix * DIRECTION[num_]; }
	//各軸方向の長さを返す
	Vector3 getLength() const { return length; }

	//メンバ定数
private:
	static const int MAX_DIRECTION_NUM = 3;				//方向ベクトルの本数
	static const Vector3 DIRECTION[MAX_DIRECTION_NUM];	//各軸の正の向き

	//メンバ変数
	std::vector<Vector3> posDelta;	//各角が離れている距離のベクトルの配列
	Vector3 length = Vector3::ZERO;	//各成分の長さ
};