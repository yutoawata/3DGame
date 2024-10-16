#include "ResultScene.h"
#include "TitleScene.h"

//コンストラクタ
ResultScene::ResultScene(std::string result_, int set_size)
	:SceneBase(set_size) {
	result = result_;
	next = Kind::TITLE;
	titleButton = new ButtonUI(Vector2(700, 600), Vector2(450, 95), Vector2(2, 5), "Click to Title");
	titleButton->setIsVisible(true);
}

//デストラクタ
ResultScene::~ResultScene() {
	delete titleButton;
	titleButton = nullptr;
}

SceneBase* ResultScene::Run() {
	DrawStringToHandle(600, 300, result.c_str(), Color::WHITE, titleFontHandle);
	return ChangeNext();
}

//シーン遷移処理
SceneBase* ResultScene::ChangeNext() {
	if (titleButton->CheckClick()) {
		delete this;
		return new TitleScene();
	}

	return this;
}