#include "TitleScene.h"
#include "PlayScene.h"

const float TitleScene::CHANGE_INTERVAL = 0.5f;	//シーン遷移のインターバル

//コンストラクタ
TitleScene::TitleScene(int set_size)
	:SceneBase(set_size) {
	next = Kind::PLAY;
	startButton = new ButtonUI(Vector2(700, 600), Vector2(450, 95), Vector2(2, 5), "Click to Start");
	startButton->setIsVisible(true);
}

//デストラクタ
TitleScene::~TitleScene() {
	delete startButton;
	startButton = nullptr;
}

//シーン処理
SceneBase* TitleScene::Run() {

	DrawStringToHandle(700, 300, title.c_str(), Color::WHITE, titleFontHandle);

	return ChangeNext();
}

//シーン遷移処理
SceneBase* TitleScene::ChangeNext() {
	if (timer < 0.5f) {
		//シーン遷移のインターバルを計測
		timer += FPSManager::getInstance()->getDeltaTime();
	}

	//タイトルシーンに遷移時にプレイシーンに遷移するのみ間隔をあける
	if (timer >= 0.5f) {
		if (startButton->CheckClick()) {
			delete this;
			return new PlayScene();
		}
	}
	
	return this;
}