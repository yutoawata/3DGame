#include "MathMethod.h"

//int型の絶対値を取得
int GetAbsoluteInt(int value_) {
	return (value_ > 0) ? value_ : -value_;
}

//float型の絶対利を取得
float GetAbsoluteFloat(float value_) {
	return (value_ > 0.0f) ? value_ : -value_;
}

//行列から回転成分のみの行列を取得
Matrix GetRotationMatrix(const Matrix& transform_matrix)
{
    Matrix MATRIX_IDENTITY = Matrix(MGetIdent());

    Matrix rotationMatrix = MATRIX_IDENTITY;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rotationMatrix.setIndex(i, j, transform_matrix.getIndex(i, j));
        }
    }
    return rotationMatrix;
}

//乱数生成関数(float型)
int CreateRandom(int min_, int max_) {
    std::random_device rd;

    std::mt19937 engine(rd());

    std::uniform_int_distribution<int> dist(min_, max_);

    int result = dist(engine);
    return result;
}

//二本のベクトルの間の角度を算出
float GetAngleFromVector(Vector3 vec_01) {
    Vector3 direction = vec_01.Normalized();
    //進行方向の角度を算出
    float frontAngleCos = Vector3::Dot(direction, Vector3(0.0f, 0.0f, -1.0f));
    //角度が右回転か左回転かを判定
    Vector3 frontAngleNolm = Vector3::Cross(direction, Vector3(0.0f, 0.0f, -1.0f));

    return (frontAngleNolm.y > 0) ? -acosf(frontAngleCos) : acosf(frontAngleCos);

}