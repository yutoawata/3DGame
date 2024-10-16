#pragma once
#include <random>
#include "DxLib.h"
#include "Matrix.h"

//int型の絶対値を返す
int GetAbsoluteInt(int value_);

//float型の絶対値を返す
float GetAbsoluteFloat(float value_);

//座標変換行列から回転要素の行列を取り出す
Matrix GetRotationMatrix(const Matrix& transform_matrix);

//乱数生成関数(float型)
int CreateRandom(int min_, int max_);

//二本のベクトルの間の角度を算出
float GetAngleFromVector(Vector3 vec_01);