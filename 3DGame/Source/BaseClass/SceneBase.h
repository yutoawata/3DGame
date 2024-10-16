#pragma once
#include <string>
#include "DxLib.h"
#include "..\UI\Button.h"
#include "..\ManagerClass\UIManager.h"

//シーンクラスの親クラス
class SceneBase {
	//列挙型
public:
	//シーンの種類
	enum class Kind {
		NONE,
		TITLE,
		PLAY,
		RESULT,
	};

	//メンバ関数

	//コンストラクタ
	SceneBase(int set_size);
	//デストラクタ
	virtual ~SceneBase();

	//アクセサ

	//遷移後のシーンの種類を返す
	Kind getNextKind() const { return next; }
	
	//シーン処理
	virtual SceneBase* Run() = 0;
	//シーン遷移処理
	virtual SceneBase* ChangeNext() = 0;

	//メンバ変数
protected:
	Kind next = Kind::NONE;	//シーンの処理
	int titleFontHandle = 0;//見出しフォントのハンドル
	int fontSize = 0;		//シーン内のフォントのサイズ
};