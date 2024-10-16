#include "Field.h"

const Vector3 Field::length = Vector3(1000.0f, 1.0f, 1000.0f);

//�R���X�g���N�^
Field::Field(Matrix rotation_)
	: ObjectCollider(ObjectTag::FIELD){
	AddCubeColliderList(new CubeCollider(&position, &rotation, length));
	rotation = Matrix::GetRotateMatrix(Vector3::ZERO);
	modelHandle = MV1LoadModel("3DModel/Field.mv1");
	MV1SetPosition(modelHandle, position);
	MV1SetScale(modelHandle, scale);
}

//�f�X�g���N�^
Field::~Field() {}

//�`�揈��
void Field::Draw() {
	MV1DrawModel(modelHandle);
}