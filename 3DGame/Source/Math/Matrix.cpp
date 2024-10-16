#include "Matrix.h"

using namespace std;

const Matrix Matrix::INDENT = Matrix(MGetIdent());

//�R���X�g���N�^
Matrix::Matrix() {}

//�R���X�g���N�^
Matrix::Matrix(Vector3 vec_) {
	vector<float> row = { vec_.x };
	indexes.emplace_back(row);
	row.clear();
	row.emplace_back(vec_.y);
	indexes.emplace_back(row);
	row.clear();
	row.emplace_back(vec_.z);
	indexes.emplace_back(row);
	row.clear();
	row.emplace_back(1);
	indexes.emplace_back(row);

	clumNum = 1;
	rowNum = 4;
}

//�R���X�g���N�^
Matrix::Matrix(vector<vector<float>> indexes_) {
	indexes = indexes_;
	rowNum = static_cast<int>(indexes.size());
	clumNum = static_cast<int>(indexes[0].size());
}

//�R���X�g���N�^
Matrix::Matrix(MATRIX matrix_) {
	clumNum = rowNum = 4;
	for (int i = 0; i < 4; i++) {
		vector<float> row;
		for (int j = 0; j < 4; j++) {
			row.emplace_back(matrix_.m[i][j]);
		}
		indexes.emplace_back(row);
	}
}

//���Z�̉��Z�q�I�[�o�[���[�h
Matrix Matrix::operator +(const Matrix& other_) const{
	vector<vector<float>> result;
	for (int i = 0; i < other_.rowNum; i++) {
		float value = 0;
		for (int j = 0; j < other_.rowNum; j++) {
			value += indexes[i][j] + other_.indexes[j][i];
		}
		result[i].emplace_back(value);
	}
	return Matrix(result);
}

//���Z�̉��Z�q�I�[�o�[���[�h
Matrix Matrix::operator -(const Matrix& other_) const{
	vector<vector<float>> result;
	for (int i = 0; i < other_.rowNum; i++) {
		float value = 0;
		for (int j = 0; j < other_.rowNum; j++) {
			value += indexes[i][j] - other_.indexes[j][i];
		}
		result[i].emplace_back(value);
	}
	return Matrix(result);
}

//��Z�̉��Z�q�I�[�o�[���[�h
Matrix Matrix::operator *(const Matrix& other_) const{
	vector<vector<float>> result;//�v�Z���ʂ̍s��
	vector<float> resultIndex;//�s��̍s�P�ʂ̗v�f

	//���Ӎs��̍s���[�v
	for (int i = 0; i < rowNum; i++) {

		//�E�Ӎs��̗񃋁[�v
		for (int j = 0; j < other_.clumNum; j++) {
			float value = 0;

			//���Ӎs��̗񃋁[�v
			for (int k = 0; k < clumNum; k++) {
				value += indexes[i][k] * other_.indexes[k][j];
			}
			resultIndex.emplace_back(value);
		}
		result.emplace_back(resultIndex);
		resultIndex.clear();
	}
	return Matrix(result);
}

//3�����x�N�g���ɃL���X�g
 Matrix::operator Vector3(){
	 //���W�̐����ɑΉ����鐬���Ńx�N�g���𐶐����ĕԂ�(4�s1��̍s�񂵂��Ή��ł��Ă��Ȃ�)
	 return Vector3(indexes[0][0], indexes[1][0], indexes[2][0]);
}

 //��]�s��̎Z�o
 Matrix Matrix::GetRotateMatrix(const Vector3& angle_) {
	 return Role(angle_.z) * Yo(angle_.y) * Pitch(angle_.x);
 }