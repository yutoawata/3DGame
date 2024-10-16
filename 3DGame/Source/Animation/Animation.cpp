#include "Animator.h"

const float Animator::ANIMATION_SPEED = 1.0f;//アニメーションの再生速度

//コンストラクタ
Animator::Animator(int model_handle) {
	modelHandle = model_handle;
}

//コンストラクタ
Animator::Animator(Vector3 position_, int model_handle) {
	position = position_;
	modelHandle = model_handle;
}

//コンストラクタ
Animator::Animator(Vector3 position_, Vector3 angle_, Vector3 scale_, int model_handle) {
	modelHandle = model_handle;
	position = position_;
	angle = angle_;
	scale = scale_;
	ChangeAnimation();
}

//アニメーションの更新処理
void Animator::UpdateAnimation() {
	isFinish = false;
	modelPosition = position;
	//モデルの中心にオブジェクトの座標が来るようにモデルの座標を下げる
	modelPosition -= Matrix::GetRotateMatrix(angle) * Vector3(0.0f, modelSize.y, 0.0f);

	//アニメーションが切り替わったら
	if (currentAnimID != nextAnimID) {
		timer = 0;
		//切り替え前のアニメーションをデタッチ
		MV1DetachAnim(modelHandle, attachIndex);
		ChangeAnimation();
	}

	timer += ANIMATION_SPEED;

	//アニメーションの尺を過ぎたらリセット
	if (timer >= totalTime) {
		timer = 0;
		isFinish = true;
	}

	//再生時間を設定
	MV1SetAttachAnimTime(modelHandle, attachIndex, timer);

	//モデルの座標・スケール・回転角度を設定
	MV1SetPosition(modelHandle, modelPosition);
	MV1SetRotationXYZ(modelHandle, angle);
	MV1SetScale(modelHandle, scale);
}

//アニメーション遷移処理
void Animator::ChangeAnimation() {
	currentAnimID = nextAnimID;
	//アニメーションをアタッチ
	attachIndex = MV1AttachAnim(modelHandle, currentAnimID);
	//アニメーションの尺を取得
	totalTime = MV1GetAnimTotalTime(modelHandle, currentAnimID);
	//アニメーションの再生時間を設定
	MV1SetAttachAnimTime(modelHandle, attachIndex, timer);
}

