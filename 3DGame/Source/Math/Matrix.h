#pragma once
#include <vector>
#include "Vector3.h"

//�s��N���X
class Matrix {
public://�����o�֐�
	//�R���X�g���N�^
	Matrix();
	//�x�N�g���N���X����s��֕ϊ�����R���X�g���N�^
	Matrix(Vector3 vec_);
	//�v�f��z��Ŏw�肷��R���X�g���N�^
	Matrix(std::vector<std::vector<float>> indexes);
	//DX���C�u�����̍s��N���X����̕ϊ��R���X�g���N�^
	Matrix(MATRIX matrix_);

	//�A�N�Z�T
	//�s��̍s����Ԃ�
	int getRowNum() const { return rowNum; }
	//�s��̗�
	int getCulmNum() const { return clumNum; }
	//�s��̗v�f���w�肵�ĕԂ�
	float getIndex(int clum_num, int row_num) const { return indexes[row_num][clum_num]; }
	//�s��̎w�肵���v�f��ݒ肷��
	void setIndex(int row_num, int clum_num, float value_) { indexes[row_num][clum_num] = value_; }

	//���Z�q�I�[�o�[���C�h
	Matrix operator +(const Matrix& other_) const;//Vector�N���X���m�̉��Z��ǉ�4
	Matrix operator -(const Matrix& other_) const;//Vector�N���X���m�̌��Z��ǉ�
	Matrix operator *(const Matrix& other_) const;//�e�v�f�ւ̏�Z��ǉ�
	operator Vector3();//���W�ւ̕ϊ�

	//��]�s��̎Z�o
	static Matrix GetRotateMatrix(const Vector3& angle_);

	//�����o�萔
	static const Matrix INDENT;	//�P�ʍs��

	//�����o�ϐ�
	std::vector<std::vector<float>> indexes;//�s��̗v�f
	int rowNum = 0;							//�s��
	int clumNum = 0;						//��
};

//Z����]�s��N���X
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

//X����]�s��N���X
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

//Y����]�s��N���X
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