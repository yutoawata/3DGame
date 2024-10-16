#pragma once
#include "..\BaseClass\SceneBase.h"

class ResultScene :public SceneBase {
	//メンバ関数
public:
	//コンストラクタ
	ResultScene(std::string result_, int set_size = 60);
	//デストラクタ
	~ResultScene();

	//シーン処理
	SceneBase* Run() override;
	//シーン遷移処理
	SceneBase* ChangeNext() override;

	//メンバ変数
private:
	std::string result = "";		//リザルトテキスト
	ButtonUI* titleButton = nullptr;//シーン遷移ボタン(遷移先はタイトルシーン)
};