#include "SceneBase.h"

//コンストラクタ
SceneBase::SceneBase(int set_size) {
	fontSize = set_size;
	SetFontSize(fontSize);
	titleFontHandle = CreateFontToHandle(NULL, 150, -1);
}

//デストラクタ
SceneBase::~SceneBase() {
	UIManager::Instance()->ClearList();
}