#include "SceneBase.h"

//�R���X�g���N�^
SceneBase::SceneBase(int set_size) {
	fontSize = set_size;
	SetFontSize(fontSize);
	titleFontHandle = CreateFontToHandle(NULL, 150, -1);
}

//�f�X�g���N�^
SceneBase::~SceneBase() {
	UIManager::Instance()->ClearList();
}