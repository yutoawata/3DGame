#pragma once
#include <vector>
#include "..\Math\Vector3.h"
#include "..\Math\MathMethod.h"
#include "..\Collider\CubeCollider.h"
#include "..\Collider\SphereCollider.h"

//オブジェクトが持つコライダーの統括クラス
class ObjectCollider {
	//列挙型
public:
	//オブジェクト判別用のタグ
	enum class ObjectTag {
		NONE,
		PLAYER,	//プレイヤー
		FIELD,	//フィールド
		ENEMY,	//エネミー
		ATTACK	//攻撃判定
	};

	//メンバ関数

	//コンストラクタ
	ObjectCollider(ObjectTag tag_ = ObjectTag::NONE);
	//デストラクタ
	virtual ~ObjectCollider();

	//アクセサ
	
	//自身が所持している立方体Colliderの配列で返す
	std::vector<CubeCollider*> getCubeColliders() const { return cubeColliders; }
	//所持している球体Colliderの配列を返す
	std::vector<SphereCollider*> getSphereColliders() const { return sphereColliders; }
	//自身を返す
	template<class Object>
	const Object* getComponent() const { return dynamic_cast<const Object*>(this); }
	//指定された立方体Colliderを返す
	CubeCollider* getCubeCollider(int num_) const { return cubeColliders[num_]; }
	//指定された球体Colliderを返す
	SphereCollider* getSphereCollider(int num_) const { return sphereColliders[num_]; }
	//自身のTagを返す
	ObjectTag getTag() const { return tag; }

	//衝突判定時の処理
	virtual void OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) {}
protected:
	//立方体Colliderの追加(戻り値は配列の要素番号)
	int AddCubeColliderList(CubeCollider* add_collider);
	//球体Colliderの追加(戻り値は配列の要素番号)
	int AddSphereColliderList(SphereCollider* add_collider);

	//メンバ変数
	Vector3 checkPosition = Vector3::ZERO;			//衝突判定用の中心座標
	Matrix rotation = Matrix::INDENT;				//オブジェクトの回転行列
	std::vector<CubeCollider*> cubeColliders;		//オブジェクトが持つ立方体Colliderの配列
	std::vector<SphereCollider*> sphereColliders;	//オブジェクトが持つ球形Colliderの配列
	ObjectTag tag = ObjectTag::NONE;				//オブジェクト判別用ののタグ
};