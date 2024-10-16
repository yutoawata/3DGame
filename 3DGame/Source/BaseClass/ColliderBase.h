#pragma once
#include <vector>
#include "..\Math\Vector3.h"
#include "..\Math\Matrix.h"

//コライダーの基底クラス
class ColliderBase {
	//列挙型
public:
	enum class Type {
		BODY,
		SEARCH,
		WEAPON
	};

	//メンバ関数
	
	//コンストラクタ
	ColliderBase(Vector3* position_, Type type_);
	ColliderBase(Vector3* position_, Matrix* rotation_, Type type_);
	//デストラクタ
	virtual ~ColliderBase();

	//アクセサ

	//Objectの中心座標を返す
	Vector3 getPosition() const { return *position; }
	//移動方向を返す
	Vector3 getMoveVector() const { return moveVector; }
	//Colliderの種類を返す
	Type getType() const { return type; }
	//処理フラグを返す
	bool IsActive() const { return isActive; }
	//処理フラグを設定する
	void setIsActive(bool flag_) { isActive = flag_; }

	//更新処理
	void Update();

	//メンバ変数
protected:
	Vector3* position = nullptr;			//位置座標
	Matrix* rotationMatrix = nullptr;		//回転行列
	/*
		positionとrotationをポインターにしているのは
		モデルにコライダーを追従やすくするために
		モデルの座標をアドレスとして受け取り変化を同期させるため
	*/
	Vector3 latePosition = Vector3::ZERO;	//前フレームでの座標
	Vector3 moveVector = Vector3::ZERO;		//移動ベクトル
	Type type = Type::BODY;					//コライダーの判別用のタグ
	bool isActive = true;					//コライダーのアクティブフラグ
};