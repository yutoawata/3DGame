#pragma once
#include "..\BaseClass\MoverBase.h"

//移動オブジェクトの管理クラス
class MoverManager {
	//メンバ関数
public:
	//コンストラクタ
	~MoverManager();

	//アクセサ

	//インスタンスを返す
	static MoverManager* getInstance() { return instance; }

	//インスタンスの生成
	static void CreateInstance();
	//インスタンスの削除
	static void DeleteInstance();
	//リスト登録処理
	void AddList(MoverBase* const object_);
	//更新前処理
	void Prepare();
	//更新処理
	void Update();
	//描画処理
	void Draw();

private:
	//コンストラクタ
	MoverManager() {}
	//コピーコンストラクタを削除
	MoverManager(const MoverManager&) = delete;

	//メンバ変数
	static MoverManager* instance;		//クラスのインスタンス(シングルトン)
	std::vector<MoverBase*> objectList;	//管理するオブジェクトのリスト
	/*
		リスト内のポインタの変更を禁止
	*/
};