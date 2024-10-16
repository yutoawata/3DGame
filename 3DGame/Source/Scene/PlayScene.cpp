#include "PlayScene.h"
#include "ResultScene.h"

//コンストラクタ
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

//デストラクタ
PlayScene::~PlayScene() {
	MoverManager::DeleteInstance();
	ColliderManager::DeleteInstance();
	delete player;
	delete enemy;
	delete field;
}

//シーン処理
SceneBase* PlayScene::Run() {
	//更新前処理
	MoverManager::getInstance()->Prepare();
	ColliderManager::getInstance()->CheckList();

	//更新処理
	MoverManager::getInstance()->Update();

	//描画処理
	field->Draw();
	MoverManager::getInstance()->Draw();

	return ChangeNext();
}

//シーン遷移処理
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