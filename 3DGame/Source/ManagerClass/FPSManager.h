#pragma once
#include"DxLib.h"

//フレームレート管理クラス
class FPSManager {
	//メンバ関数
private:
	//コンストラクタ
	FPSManager();
	FPSManager(FPSManager&) = delete;
	//デストラクタ
	~FPSManager();

public:
	//インスタンスを返す
	static FPSManager* getInstance() { return instance; }

	//アクセサ
	//1フレームにかかった時間を返す
	float getDeltaTime() { return 1.0f / fps; }	//1フレームで経過した時間
	//フレームレートを返す
	float getFPS() { return fps; }

	//インスタンスの生成処理
	static void CreateInstance();
	//インスタンスの削除処理
	static void DeleteInstance();
	//更新処理
	void Update();
	//1/60秒経つまで処理を一時停止
	void Wait();
	
	//メンバ定数
private:
	static const int MAX_FPS = 60;			//フレームレートの最大値

	//メンバ変数
	static FPSManager* instance;			//他ファイルでの呼び出し用のインスタンス
	int start_time = 0;						//開始時の時間
	int count = MAX_FPS;					//フレームのカウント
	float fps = static_cast<float>(MAX_FPS);//ゲーム内のフレームレート

};