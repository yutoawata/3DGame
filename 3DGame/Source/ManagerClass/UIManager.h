#pragma once
#include <vector>
#include "..\BaseClass\UIBase.h"

class UIManager {
	//メンバ関数
public:
	//デストラクタ
	~UIManager();

	//アクセサ
	
	//インスタンスを返す
	static UIManager* Instance() { return instance; }

	//インスタンスの生成処理
	static void CreateInstance();
	//インスタンスの削除処理
	static void DeleteInstance();
	//UIList登録処理
	void AddList(UIBase* ui_);
	//描画処理
	void Draw() const;
	//リストを削除
	void ClearList();
private:
	//コンストラクタ
	UIManager() {}
	UIManager(const UIManager&) = delete;

	//メンバ変数
	static UIManager* instance;//他ファイルでの呼び出し用のインスタンス
	std::vector<UIBase*> UIList;//UIオブジェクトのリスト
};