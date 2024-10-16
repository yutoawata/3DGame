#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include"DxLib.h"

struct Vector3 {
	//メンバ関数

	//コンストラクタ
	Vector3();
	//三次元ベクトル用コンストラクタ
	Vector3(float x_, float y_, float z_);
	Vector3(VECTOR vector_);


	//内積計算
	static float Dot(Vector3 vec_01, Vector3 vec_02);
	//外積計算
	static Vector3 Cross(Vector3 vec_01, Vector3 vec_02);
	//単位ベクトルを返す
	Vector3 Normalized() const;
	//サイズを返す
	float getSize() const { return sqrtf(x * x + y * y + z * z); }

	//演算子オーバーロード

	//Vectorクラス同士の加算
	Vector3 operator +(const Vector3& other) const;
	//Vectorクラス同士の減算
	Vector3 operator -(const Vector3& other) const;
	//各要素への乗算
	Vector3 operator *(float value) const;
	//各要素への除算
	Vector3 operator /(float value) const;
	//Vectorクラス同士の加算
	Vector3& operator +=(const Vector3& other);
	//Vectorクラス同士の減算
	Vector3& operator -=(const Vector3& other);
	//Vectorクラス同士の加算
	Vector3& operator *=(float value);
	//Vectorクラス同士の減算
	Vector3& operator /=(float value);
	//Vectorクラス同士の等価比較
	bool operator ==(const Vector3& other);
	//Vectorクラス同士の不等価比較
	bool operator !=(const Vector3& other);
	//DXライブラリのベクトルクラスへのキャスト
	operator VECTOR() const;
	
	//メンバ定数
	static const Vector3 ZERO;//ゼロベクトル

	//メンバ変数
	float x = 0.0f;//X成分
	float y = 0.0f;//Y成分
	float z = 0.0f;//Z成分
};