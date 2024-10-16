#pragma once
#include "..\BaseClass\SceneBase.h"
#include "..\Field\Field.h"
#include "..\Player\Soldier.h"
#include "..\Enemy\Mutant.h"
#include "..\Enemy\\Magician.h"
#include "..\ManagerClass\ColliderManager.h"
#include "..\ManagerClass\MoverManager.h"

class PlayScene :public SceneBase {
	//メンバ関数
public:
	//コンストラクタ
	PlayScene(int set_size = 32);
	//デストラクタ
	~PlayScene();

	//シーン処理
	SceneBase* Run() override;
	//シーン遷移処理
	SceneBase* ChangeNext() override;

	//メンバ変数
private:
	Soldier* player = nullptr;		//自機オブジェクト
	Mutant* enemy = nullptr;		//エネミーオブジェクト
	Magician* magician = nullptr;	//魔術師オブジェクト
	Field* field = nullptr;			//地形オブジェクト
};