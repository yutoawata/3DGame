#pragma once
#include "..\BaseClass\SceneBase.h"

//タイトルシーンクラス
class TitleScene :public SceneBase {
	//メンバ関数
public:
	//コンストラクタ
	TitleScene(int set_size = 60);
	//デストラクタ
	~TitleScene();

	//シーン処理
	SceneBase* Run() override;
	//遷移フラグを返す
	SceneBase* ChangeNext() override;

	//メンバ定数
	static const float CHANGE_INTERVAL;	//シーン遷移のインターバル

	//メンバ変数
	std::string title = "3DGame";		//タイトルテキスト
	ButtonUI* startButton = nullptr;	//シーン遷移ボタン(遷移先はプレイシーン)
	float timer = 0.0f;					//遷移してきてからの経過時間
};