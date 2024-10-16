#pragma once
#include <vector>
#include "..\Math\Vector3.h"

template<class Object>
//行動AIの基底クラス
class AIBase {
	//メンバ関数
public:
	//コンストラクタ
	AIBase(Object* holder_);
	//デストラクタ
	virtual ~AIBase();

	//アクセサ
	std::vector<Vector3> getRouteList() { return routeList; }

	//更新処理
	virtual Vector3 SelectMovePosition() = 0;

	//メンバ変数
protected:
	std::vector<Vector3> routeList;			//徘徊ルートの基点座標の配列
	Object* holder = nullptr;				//AIを保持しているObject
	Vector3 targetPosition = Vector3::ZERO;	//移動対象の座標
	Vector3 moveDirection = Vector3::ZERO;	//移動方向
};