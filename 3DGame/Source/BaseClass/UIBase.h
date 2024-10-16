#pragma once
#include "..\Math\Vector2.h"

//UI基底クラス
class UIBase {
	//メンバ関数
public:
	//コンストラクタ
	UIBase(Vector2 position_);

	//アクセサ
	
	//描画フラグを返す
	bool IsVisible() { return isVisible; }
	//描画フラグを設定
	void setIsVisible(bool flag_) { isVisible = flag_; }

	//描画処理
	virtual void Draw() = 0 ;

	//メンバ変数
protected:
	Vector2 position = Vector2::ZERO;	//位置座標
	bool isVisible = false;				//表示フラぐ
};