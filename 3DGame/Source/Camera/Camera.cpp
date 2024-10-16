#include "Camera.h"
#include <vector>

const Vector2 Camera::STANDERD_CURSOR_POSITION = Vector2(960, 540);	//スクリーンの中心座標
const float Camera::ROTATE_SPEED = 2.0f;							//回転速度

//コンストラクタ
Camera::Camera(Vector3 target_position) {
	//カメラの描画範囲の設定
	SetCameraNearFar(near_, far_);
	position = target_position + Vector3(0.0f, 0.0f, -distance);
	upVector = Vector3(0.0f, 1.0f, 0.0f);
	//カメラの姿勢を設定
	SetCameraPositionAndTargetAndUpVec(position, target_position, upVector);
}

//更新処理
void Camera::Update(const Vector3& target_position) {
	Move(target_position);
	//更新した情報を設定
	SetCameraPositionAndTargetAndUpVec(position, target_position, upVector);

	//マウスカーソルの座標を画面の中心に設定
	SetMousePoint(STANDERD_CURSOR_POSITION.x, STANDERD_CURSOR_POSITION.y);
}

//移動処理
void Camera::Move(const Vector3& target_position) {
	Vector2 newPosition = Vector2::ZERO;

	//マウスカーソルの座標を取得
	GetMousePoint(&newPosition.x, &newPosition.y);

	//マウスカーソルが上に移動していれば
	if (STANDERD_CURSOR_POSITION.y < newPosition.y) {
		//前方向に回転させる
		angleVector.x += (DX_PI_F / 180.0f) * ROTATE_SPEED;
	}
	//マウスカーソルが下に移動していれば
	if (STANDERD_CURSOR_POSITION.y > newPosition.y) {
		//後方向に回転させる
		angleVector.x -= (DX_PI_F / 180.0f) * ROTATE_SPEED;
	}
	//マウスカーソルが右に移動していれば
	if (STANDERD_CURSOR_POSITION.x > newPosition.x) {
		//右方向に回転させる
		angleVector.y -= (DX_PI_F / 180.0f) * ROTATE_SPEED;
	}
	//マウスカーソルが左に移動していれば
	if (STANDERD_CURSOR_POSITION.x < newPosition.x) {
		//左方向に回転させる
		angleVector.y += (DX_PI_F / 180.0f) * ROTATE_SPEED;
	}

	//回転角度から回転行列を取得
	Matrix rotate = Matrix::GetRotateMatrix(angleVector);

	//カメラの位置を更新
	position = target_position + (rotate * Vector3(0.0f, 0.0f, -distance));
}