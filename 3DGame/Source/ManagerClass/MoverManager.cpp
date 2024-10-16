#include "MoverManager.h"

MoverManager* MoverManager::instance = new MoverManager();//クラスのインスタンス(シングルトン)

//デストラクタ
MoverManager::~MoverManager() {}

//インスタンスの生成
void MoverManager::CreateInstance() {
	if (instance == nullptr) {
		instance = new MoverManager();
	}
}

//インスタンスの削除
void MoverManager::DeleteInstance() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

//リスト登録処理
void MoverManager::AddList(MoverBase* const object_) {
	objectList.emplace_back(object_);
}

//更新前処理
void MoverManager::Prepare() {
	for (MoverBase* object : objectList) {
		object->Prepare();
	}
}

//更新処理
void MoverManager::Update() {
	for (MoverBase* object : objectList) {
		object->Update();
	}
}

//描画処理
void MoverManager::Draw() {
	for (MoverBase* object : objectList) {
		object->Draw();
	}
}