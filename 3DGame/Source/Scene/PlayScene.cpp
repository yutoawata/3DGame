#include "PlayScene.h"
#include "ResultScene.h"

//�R���X�g���N�^
PlayScene::PlayScene(int set_size)
	:SceneBase(set_size) {
	next = Kind::RESULT;
	MoverManager::CreateInstance();
	ColliderManager::CreateInstance();
	player = new Soldier();
	enemy = new Mutant(player);
	magician = new Magician(player, enemy, Vector3(0.0f, 0.0f, 0.0f));
	field = new Field();
}

//�f�X�g���N�^
PlayScene::~PlayScene() {
	MoverManager::DeleteInstance();
	ColliderManager::DeleteInstance();
	delete player;
	delete enemy;
	delete field;
}

//�V�[������
SceneBase* PlayScene::Run() {
	//�X�V�O����
	MoverManager::getInstance()->Prepare();
	ColliderManager::getInstance()->CheckList();

	//�X�V����
	MoverManager::getInstance()->Update();

	//�`�揈��
	field->Draw();
	MoverManager::getInstance()->Draw();

	return ChangeNext();
}

//�V�[���J�ڏ���
SceneBase* PlayScene::ChangeNext() {
	if (player->getHitPoint() <= 0) {
		delete this;
		return new ResultScene("Game Over");
	}
	else if(enemy->getHitPoint() <= 0) {
		delete this;
		return new ResultScene("Game Clear");
	}

	return this;
}