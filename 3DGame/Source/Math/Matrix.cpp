#include "Matrix.h"

using namespace std;

const Matrix Matrix::INDENT = Matrix(MGetIdent());

//コンストラクタ
Matrix::Matrix() {}

//コンストラクタ
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

//コンストラクタ
Matrix::Matrix(vector<vector<float>> indexes_) {
	indexes = indexes_;
	rowNum = static_cast<int>(indexes.size());
	clumNum = static_cast<int>(indexes[0].size());
}

//コンストラクタ
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

//加算の演算子オーバーロード
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

//減算の演算子オーバーロード
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

//乗算の演算子オーバーロード
Matrix Matrix::operator *(const Matrix& other_) const{
	vector<vector<float>> result;//計算結果の行列
	vector<float> resultIndex;//行列の行単位の要素

	//左辺行列の行ループ
	for (int i = 0; i < rowNum; i++) {

		//右辺行列の列ループ
		for (int j = 0; j < other_.clumNum; j++) {
			float value = 0;

			//左辺行列の列ループ
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

//3次元ベクトルにキャスト
 Matrix::operator Vector3(){
	 //座標の成分に対応する成分でベクトルを生成して返す(4行1列の行列しか対応できていなし)
	 return Vector3(indexes[0][0], indexes[1][0], indexes[2][0]);
}

 //回転行列の算出
 Matrix Matrix::GetRotateMatrix(const Vector3& angle_) {
	 return Role(angle_.z) * Yo(angle_.y) * Pitch(angle_.x);
 }