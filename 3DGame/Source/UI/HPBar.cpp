#include "HPBar.h"

//コンストラクタ
HPBar::HPBar(Vector2 position_, const int& hit_point, int width_, int height_, std::string name_)
	: UIBase(position_), nextHitPoint(&hit_point) {
	maxHitPoint = hit_point;
	currentHitPoint = hit_point;
	width = width_;
	height = height_;
	name = name_;
}

//描画処理
void HPBar::Draw() {
	
	if (currentHitPoint > *nextHitPoint) {
		currentHitPoint--;
	}

	// 通常のバーの色
	int color = Color::GREEN;
	// ＨＰ描画の値が半分以下だったら
	if (*nextHitPoint <= maxHitPoint / 2) {
		// 黄色
		color = Color::YELLOW;
	}
	// ＨＰが残り１の時
	if (*nextHitPoint <= maxHitPoint / 4) {
		// 赤
		color = Color::RED;
	}

	//HPバーの長さをHPの割合に合わせて短くする
	float delta = static_cast<float>(currentHitPoint) / static_cast<float>(maxHitPoint);
	int lineSize = static_cast<int>(width * delta);
	// HP の値分の大きさだが四角に収まるように値を大きくします
	DrawFillBox(position.x, position.y, position.x + lineSize, position.y + height, Color::RED);
	//HPバーの長さをHPの割合に合わせて短くする
	delta = static_cast<float>(*nextHitPoint) / static_cast<float>(maxHitPoint);
	lineSize = static_cast<int>(width * delta);
	DrawFillBox(position.x, position.y, position.x  + lineSize, position.y + height, color);
	DrawLineBox(position.x, position.y, position.x + width, position.y + height, Color::WHITE);
	//オブジェクト名を表示(20・5は文字の位置を調整するための値)
	DrawFormatString(position.x + 20, position.y + 5, Color::BLOCK, name.c_str());
}
