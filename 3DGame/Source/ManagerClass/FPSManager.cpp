#include "FPSManager.h"
#include "..\Color\Color.h"

//他ファイルでの呼び出し用のインスタンスを生成
FPSManager* FPSManager::instance = new FPSManager();

//コンストラクタ
FPSManager::FPSManager() {}

//デストラクタ
FPSManager::~FPSManager() {}

//更新処理
void FPSManager::Update() {
	if (count == 0) {
		//ミリ秒単位の精度を持つカウンタの現在値を得る
		start_time = GetNowCount();
	}
	if (count == MAX_FPS) {
		//ミリ秒単位の制度を持つカウンタの現在値を得る
		int t = GetNowCount();
		fps = 1000.f / ((t - start_time) / static_cast<float>(MAX_FPS));
		count = 0;
		start_time = t;
	}
	count++;
}

//1/60秒経つまで処理を一時停止
void FPSManager::Wait() {
	//ミリ秒単位の制度を持つカウンタの現在値を得る
	int nTookTime = GetNowCount() - start_time;
	int nWaitTime = count * 1000 / MAX_FPS - nTookTime;
	if (nWaitTime > 0) {
		Sleep(nWaitTime);
	}
}

//インスタンスの生成処理
void FPSManager::CreateInstance() {
	if (instance == nullptr) {
		instance = new FPSManager();
	}
}

//インスタンスの削除処理
void FPSManager::DeleteInstance() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}