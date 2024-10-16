#pragma once
#include "DxLib.h"
#include "..\Color\Color.h"
#include "..\Math\Vector3.h"
#include "..\Math\Matrix.h"
#include <unordered_map>

//アニメーション操作クラス
class Animator {
	//メンバ関数
public:
	//コンストラクタ
	Animator(int model_handle);
	Animator(Vector3 position_, int model_handle);
	Animator(Vector3 position_, Vector3 angle_, Vector3 scale_, int model_handle);

	//アクセサ
	
	//モデルの座標を返す
	Vector3 getPosition() const { return position; }
	//モデルの回転角度を返す
	Vector3 getAngle() const { return angle; }
	//モデルのハンドルを返す
	int getModelHandle() const { return modelHandle; }
	//アニメーションの総再生時間を返す
	float getTotalAnimationTime() const { return totalTime; }
	//アニメーション終了フラグを返す
	bool IsFinish() const { return isFinish; }

	//アニメーションの更新処理
	void UpdateAnimation();
	//アニメーション遷移処理
	void ChangeAnimation();

	//メンバ定数
protected:
	static const float ANIMATION_SPEED;			//アニメーションの再生速度

	//メンバ変数
	Vector3 position = Vector3::ZERO;			//オブジェクトとしての座標(中心を原点)
	Vector3 angle = Vector3::ZERO;				//回転角度
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);	//モデルのスケール
	Vector3 modelSize = Vector3::ZERO;			//オブジェクトの幅
	int modelHandle = 0;						//アニメーションを設定するモデルのハンドル
	int nextAnimID = -1;						//次に再生するアニメーション番号
	//クラス内でしか使わないのでprivateにする
private:
	Vector3 modelPosition = Vector3::ZERO;		//描画する際のモデルの座標(足元を原点)
	int currentAnimID = -1;						//アタッチしたアニメーションのアタッチ番号※
	int attachIndex = -1;						//アタッチしたアニメーションの登録番号※
	float totalTime = 0;						//アニメーションの総再生時間
	float timer = 0;							//アニメーションの再生時間
	bool isFinish = false;						//アニメーションの終了フラグ
	/*
		※animationNumとattachIndexの初期値が-1なのは、
		  0が登録されたアニメーションの一つ目を指すため、
		  アニメーションが存在しない値である-1で初期化している
	*/
};