#include "DxLib.h"
#include "GameManager.h"

//メイン関数
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	//ゲーム管理クラスを生成
	GameManager* game_manager = new GameManager();
	
	//ゲームループ処理
	game_manager->Run();

	//ゲーム管理クラスを削除
	delete game_manager;
}