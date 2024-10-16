#include "GameManager.h"

//コンストラクタ
GameManager::GameManager() {
	//解像度を設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);

	//フルスクリーンにする
	ChangeWindowMode(FALSE);
	isInit = DxLib_Init();

	//Zバッファの使用を許可
	SetUseZBuffer3D(TRUE);
	//Zバッファの書き込みを許可
	SetWriteZBuffer3D(TRUE);
	//マウスカーソルの表示をOFF
	SetMouseDispFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	//現在のシーンをタイトルにする
	currentScene = new TitleScene();
	//UI管理クラスを生成
	UIManager::CreateInstance();
	FPSManager::CreateInstance();
}

//デストラクタ
GameManager::~GameManager() {
	delete currentScene;
	currentScene = nullptr;
	UIManager::DeleteInstance();
	FPSManager::DeleteInstance();
	InitSoundMem();
	DxLib_End();
}

//ゲームループ
void GameManager::Run() {
	while (!ProcessMessage() && isInit != TRUE) {

		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}
		
		ClearDrawScreen();

		//シーン内の処理
		currentScene = currentScene->Run();
		//UIを描画
		UIManager::Instance()->Draw();
		//フレームレート管理クラスの更新処理
		FPSManager::getInstance()->Update();

		ScreenFlip();

		FPSManager::getInstance()->Wait();
	}
}