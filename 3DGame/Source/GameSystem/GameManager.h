#pragma once
#include "DxLib.h"
#include "..\BaseClass\SceneBase.h"
#include "..\Scene\TitleScene.h"
#include "..\ManagerClass\UIManager.h"
#include "..\ManagerClass\FPSManager.h"

class GameManager {
	//メンバ関数
public:
	//コンストラクタ
	GameManager();
	//デストラクタ
	~GameManager();

	//ゲームループ処理
	void Run();

	//メンバ定数
private:
	//ゲームウィンドウ設定定数--------------
	static const int SCREEN_WIDTH = 1920;	//ゲームウィンドウの横幅
	static const int SCREEN_HEIGHT = 1080;	//ゲームウィンドウの縦幅
	static const int SCREEN_COLOR = 32;	//ゲームウィンドウのカラービット

	//メンバ変数

	SceneBase* currentScene = nullptr;	//ゲームシーンオブジェクト
	int isInit = FALSE;					//ゲームの初期設定完了フラグ
	/*
		ライブラリ初期設定関数「Init()」の結果がint型で返ってくるため
		bool型ではなく、int型にしています。
	*/
};