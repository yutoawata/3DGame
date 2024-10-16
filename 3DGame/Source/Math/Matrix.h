#pragma once
#include <vector>
#include "Vector3.h"

//行列クラス
class Matrix {
public://メンバ関数
	//コンストラクタ
	Matrix();
	//ベクトルクラスから行列へ変換するコンストラクタ
	Matrix(Vector3 vec_);
	//要素を配列で指定するコンストラクタ
	Matrix(std::vector<std::vector<float>> indexes);
	//DXライブラリの行列クラスからの変換コンストラクタ
	Matrix(MATRIX matrix_);

	//アクセサ
	//行列の行数を返す
	int getRowNum() const { return rowNum; }
	//行列の列数
	int getCulmNum() const { return clumNum; }
	//行列の要素を指定して返す
	float getIndex(int clum_num, int row_num) const { return indexes[row_num][clum_num]; }
	//行列の指定した要素を設定する
	void setIndex(int row_num, int clum_num, float value_) { indexes[row_num][clum_num] = value_; }

	//演算子オーバーライド
	Matrix operator +(const Matrix& other_) const;//Vectorクラス同士の加算を追加4
	Matrix operator -(const Matrix& other_) const;//Vectorクラス同士の減算を追加
	Matrix operator *(const Matrix& other_) const;//各要素への乗算を追加
	operator Vector3();//座標への変換

	//回転行列の算出
	static Matrix GetRotateMatrix(const Vector3& angle_);

	//メンバ定数
	static const Matrix INDENT;	//単位行列

	//メンバ変数
	std::vector<std::vector<float>> indexes;//行列の要素
	int rowNum = 0;							//行数
	int clumNum = 0;						//列数
};

//Z軸回転行列クラス
class Role : public Matrix {
public:
	Role(float angle_)
		:Matrix({ { cosf(angle_), -sinf(angle_), 0.0f, 0.0f},
				  { sinf(angle_),  cosf(angle_), 0.0f, 0.0f},
				  {			0.0f,		   0.0f, 1.0f, 0.0f},
				  {			0.0f,		   0.0f, 0.0f, 1.0f} 
				}) {
		angle = angle_;
	}

	float angle = 0.0f;
};

//X軸回転行列クラス
class Pitch : public Matrix {
public:
	Pitch(float angle_)
		:Matrix({ { 1.0f,		  0.0f,			 0.0f, 0.0f},
				  {	0.0f, cosf(angle_), -sinf(angle_), 0.0f},
				  {	0.0f, sinf(angle_),  cosf(angle_), 0.0f},
				  {	0.0f,		  0.0f,			 0.0f, 1.0f}
			}) {
		angle = angle_;
	}

	float angle = 0.0f;
};

//Y軸回転行列クラス
class Yo : public Matrix {
public:
	Yo(float angle_)
		:Matrix({ { cosf(angle_), 0.0f, sinf(angle_), 0.0f},
				  {			0.0f, 1.0f,			0.0f, 0.0f},
				  {-sinf(angle_), 0.0f, cosf(angle_), 0.0f},
				  {			0.0f, 0.0f,			0.0f, 1.0f}
			}) {
		angle = angle_;
	}

	float angle = 0.0f;
};