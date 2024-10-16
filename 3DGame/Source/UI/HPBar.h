#pragma once
#include <string>
#include "..\BaseClass\UIBase.h"
#include "..\Color\Color.h"

//HPバーUIクラス
class HPBar : public UIBase {
	//メンバ関数
public:
	//コンストラクタ
	HPBar(Vector2 position_, const int& hit_point, int width_, int height_, std::string name_);

	//描画処理
	void Draw() override;

	const int* const nextHitPoint;//減少後のHP
	/*
		const ポインタ constでアドレスの変更とaddress先の値の変更を禁止
	*/

	//メンバ変数
private:
	std::string name;
	int maxHitPoint = 0;	//HIの最大値
	int currentHitPoint = 0;//減少中のHP
	int width = 0;			//UIの横幅
	int height = 0;			//UIの縦幅
};
