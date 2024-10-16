#pragma once
#include "DxLib.h"
#include "..\Math\Vector2.h"
#include "..\Math\Matrix.h"
#include "..\Collider\SphereCollider.h"
#include "..\BaseClass\MoverBase.h"
#include "..\Color\Color.h"

//カメラクラス
class Camera {
	//メンバ関数
public:
	//コンストラクタ
	Camera(Vector3 target_position);
	
	//アクセサ
	Vector3 getPosition() { return position; }

	//更新処理
	void Update(const Vector3& target_position);
	
private:
	//移動処理
	void Move(const Vector3& target_position);

	//メンバ定数
	static const Vector2 STANDERD_CURSOR_POSITION;	//画面の中心座標				
	static const float ROTATE_SPEED;				//回転速度

	//メンバ変数
	Vector3 position = Vector3::ZERO;				//位置座標
	Vector3 upVector = Vector3(0.0f, 1.0f, 0.0f);	//カメラの上方向のベクトル
	Vector3 angleVector = Vector3(0.0f, 0.0f, 0.0f);//各軸の回転角度
	Vector2 cursorPosition = Vector2(0, 0);			//マウスカーソルの位置座標
	float near_ = 0.1f;								//カメラの描画範囲の最短距離
	float far_ = 1000.0f;							//カメラの描画範囲の最長距離
	float distance = 300.0f;						//描画対象とカメラとの距離
	/*
		near_とfar_のみdefine定数でnearとfarが定義済みの為、
		アンダーバー( _ )を加えることで区別している
	*/
};