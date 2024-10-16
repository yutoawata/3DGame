#include "TitleScene.h"
#include "PlayScene.h"

const float TitleScene::CHANGE_INTERVAL = 0.5f;	//�V�[���J�ڂ̃C���^�[�o��

//�R���X�g���N�^
TitleScene::TitleScene(int set_size)
	:SceneBase(set_size) {
	next = Kind::PLAY;
	startButton = new ButtonUI(Vector2(700, 600), Vector2(450, 95), Vector2(2, 5), "Click to Start");
	startButton->setIsVisible(true);
}

//�f�X�g���N�^
TitleScene::~TitleScene() {
	delete startButton;
	startButton = nullptr;
}

//�V�[������
SceneBase* TitleScene::Run() {

	DrawStringToHandle(700, 300, title.c_str(), Color::WHITE, titleFontHandle);

	return ChangeNext();
}

//�V�[���J�ڏ���
SceneBase* TitleScene::ChangeNext() {
	if (timer < 0.5f) {
		//�V�[���J�ڂ̃C���^�[�o�����v��
		timer += FPSManager::getInstance()->getDeltaTime();
	}

	//�^�C�g���V�[���ɑJ�ڎ��Ƀv���C�V�[���ɑJ�ڂ���̂݊Ԋu��������
	if (timer >= 0.5f) {
		if (startButton->CheckClick()) {
			delete this;
			return new PlayScene();
		}
	}
	
	return this;
}