#include "Button.h"

//コンストラクタ
ButtonUI::ButtonUI(Vector2 position_, Vector2 length_, Vector2 margin_, std::string text_)
	: UIBase(position_) {
	length = length_;
	text = text_;
	margin = margin_;
}

//デストラクタ
ButtonUI::~ButtonUI() {
	DeleteSoundMem(clickSound);
}

//ボタンがクリックされたかの判定
bool ButtonUI::CheckClick() {
	//マウスカーソルの座標を取得
	int cursorPositionX = 0;
	int cursorPositionY = 0;
	GetMousePoint(&cursorPositionX, &cursorPositionY);

	//カーするがボタンに重なっているなら
	if (cursorPositionX > position.x && cursorPositionX < position.x + length.x
		&& cursorPositionY > position.y && cursorPositionY < position.y + length.y) {
		//ボタンの色を赤にする
		color = Color::RED;

		//左クリックされたら
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			//決定時の効果音を流す
			PlaySoundMem(clickSound, DX_PLAYTYPE_BACK);
			return true;
		}
	}
	//カーソルがボタンから外れていたら
	else {
		//色を白にする
		color = Color::WHITE;
	}
	return false;
}

//描画処理
void ButtonUI::Draw() {
	//ボタンの名前を描画
	DrawFormatString(position.x + margin.y, position.y + margin.y, color, text.c_str());
	//ボタンの枠を描画
	DrawLineBox(position.x, position.y, position.x + length.x, position.y + length.y, color);
}