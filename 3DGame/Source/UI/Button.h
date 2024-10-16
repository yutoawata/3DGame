#pragma once
#include <string>
#include "..\BaseClass\UIBase.h"
#include "..\Color\Color.h"

class ButtonUI : public UIBase {
	//メンバ関数
public:
	//コンストラクタ
	ButtonUI(Vector2 position_, Vector2 length_, Vector2 margin_, std::string text_);
	//デストラクタ
	~ButtonUI();

	//描画処理
	void Draw() override;
	//ボタンがクリックされたかを判定
	bool CheckClick();

	//メンバ変数
private:
	int clickSound = LoadSoundMem("Sound/Decision.mp3");//クリックした際の効果音のハンドル
	std::string text;									//ボタンの中に表示するテキスト
	Vector2 length = Vector2::ZERO;						//ボタンの幅(x = 横　y = 縦)
	Vector2 margin = Vector2::ZERO;						//テキストを表示する際の枠との距離
	unsigned int color = Color::BLOCK;					//描画する際の色
};