#include "MathMethod.h"

//int�^�̐�Βl���擾
int GetAbsoluteInt(int value_) {
	return (value_ > 0) ? value_ : -value_;
}

//float�^�̐�Η����擾
float GetAbsoluteFloat(float value_) {
	return (value_ > 0.0f) ? value_ : -value_;
}

//�s�񂩂��]�����݂̂̍s����擾
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

//���������֐�(float�^)
int CreateRandom(int min_, int max_) {
    std::random_device rd;

    std::mt19937 engine(rd());

    std::uniform_int_distribution<int> dist(min_, max_);

    int result = dist(engine);
    return result;
}

//��{�̃x�N�g���̊Ԃ̊p�x���Z�o
float GetAngleFromVector(Vector3 vec_01) {
    Vector3 direction = vec_01.Normalized();
    //�i�s�����̊p�x���Z�o
    float frontAngleCos = Vector3::Dot(direction, Vector3(0.0f, 0.0f, -1.0f));
    //�p�x���E��]������]���𔻒�
    Vector3 frontAngleNolm = Vector3::Cross(direction, Vector3(0.0f, 0.0f, -1.0f));

    return (frontAngleNolm.y > 0) ? -acosf(frontAngleCos) : acosf(frontAngleCos);

}