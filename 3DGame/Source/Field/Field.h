#pragma once
#include "..\Animation\Animator.h"
#include "..\Collider\CubeCollider.h"
#include "..\Collider\ObjectCollider.h"

class Field : public ObjectCollider {
	//�����o�֐�
public:
	//�R���X�g���N�^
	Field(Matrix rotation_ = Matrix::GetRotateMatrix(Vector3::ZERO));
	//�f�X�g���N�^
	~Field();
	
	//�`�揈��
	void Draw();

	//�����o�萔
	static const Vector3 length;	//�����蔻��̊e���̒���
	
	//�����o�ϐ�
private:
	Vector3 position = Vector3(0.0f, -20.0f, 0.0f);	//�ʒu���W
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);		//���f���̏k��
	int modelHandle = 0;							//���f���̃n���h��
};