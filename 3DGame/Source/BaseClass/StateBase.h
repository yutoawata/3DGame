#pragma once
#include <string>
#include "MoverBase.h"
#include "..\ManagerClass\FPSManager.h"

//ステートの基底クラス
template<class Object>
class StateBase {
	//メンバ関数
public:
	//コンストラクタ
	StateBase(Object* holder_);
	//デストラクタ
	virtual ~StateBase();

	//アクセサ

	//ステートを保持しているオブジェクトの
	Vector3 getHolderPosition() const { return holderPosition; }
	Vector3 getHolderAngle() const { return holderAngle; }
	//自身のステートでのアニメーションの名前を返す
	std::string getAnimationName() const { return animationName; }

	//自身のステートであった際の処理
	virtual StateBase<Object>* Run() = 0;

	//メンバ変数
protected:
	Object* holder = nullptr;				//ステートを保持しているクラスのアドレス
	Vector3 holderPosition = Vector3::ZERO;	//自身を保持しているオブジェクトの座標
	Vector3 holderAngle = Vector3::ZERO;	//自身を保持しているオブジェクトの角度
	std::string animationName = "";			//自身のステートでのアニメーションの名前
};