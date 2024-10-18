#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "DxLib.h"

struct Vector2 {
	//メンバ関数
	//コンストラクタ
	Vector2();
	//二次元ベクトル用コンストラクタ
	Vector2(int x_, int y_);
	Vector2(float x_, float y_);
	
	Vector2(VECTOR vector_);


	//内積計算
	static float Dot(Vector2 vec_01, Vector2 vec_02);
	//外積計算
	static float Cross(Vector2 vec_01, Vector2 vec_02);
	//単位ベクトルを返す
	Vector2 Normalized() const;
	//サイズを返す
	int getSize() const;

	//演算子オーバーロード

	//Vectorクラス同士の加算
	Vector2 operator +(const Vector2& other) const;
	//Vectorクラス同士の減算
	Vector2 operator -(const Vector2& other) const;
	//各要素への乗算
	Vector2 operator *(int value) const;
	//各要素への除算
	Vector2 operator /(int value) const;
	//Vectorクラス同士の加算
	Vector2& operator +=(const Vector2& other);
	//Vectorクラス同士の減算
	Vector2& operator -=(const Vector2& other);
	//Vectorクラス同士の等価比較
	bool operator ==(const Vector2& other);
	//Vectorクラス同士の不等価比較
	bool operator !=(const Vector2& other);
	//DXライブラリのベクトルクラスへのキャスト
	operator VECTOR();

	//メンバ定数
	static const Vector2 ZERO;//ゼロベクトル

	//メンバ変数
	int x = 0;//X成分
	int y = 0;//Y成分
};