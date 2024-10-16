#pragma once
#include "..\Animation\Animator.h"
#include "..\Collider\CubeCollider.h"
#include "..\Collider\ObjectCollider.h"

class Field : public ObjectCollider {
	//メンバ関数
public:
	//コンストラクタ
	Field(Matrix rotation_ = Matrix::GetRotateMatrix(Vector3::ZERO));
	//デストラクタ
	~Field();
	
	//描画処理
	void Draw();

	//メンバ定数
	static const Vector3 length;	//当たり判定の各軸の長さ
	
	//メンバ変数
private:
	Vector3 position = Vector3(0.0f, -20.0f, 0.0f);	//位置座標
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);		//モデルの縮尺
	int modelHandle = 0;							//モデルのハンドル
};