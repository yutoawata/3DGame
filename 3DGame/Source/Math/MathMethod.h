#pragma once
#include <random>
#include "DxLib.h"
#include "Matrix.h"

//int�^�̐�Βl��Ԃ�
int GetAbsoluteInt(int value_);

//float�^�̐�Βl��Ԃ�
float GetAbsoluteFloat(float value_);

//���W�ϊ��s�񂩂��]�v�f�̍s������o��
Matrix GetRotationMatrix(const Matrix& transform_matrix);

//���������֐�(float�^)
int CreateRandom(int min_, int max_);

//��{�̃x�N�g���̊Ԃ̊p�x���Z�o
float GetAngleFromVector(Vector3 vec_01);