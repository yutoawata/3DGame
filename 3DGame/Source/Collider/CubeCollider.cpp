#include "CubeCollider.h"
#include "..\ManagerClass\ColliderManager.h"


const Vector3 CubeCollider::DIRECTION[MAX_DIRECTION_NUM] = {//�e���̐��̌���
	Vector3(1.0f, 0.0f, 0.0f),
	Vector3(0.0f, 1.0f, 0.0f),
	Vector3(0.0f, 0.0f, 1.0f)
};

//�ړ����铖���蔻��̏ꍇ�̃R���X�g���N�^
CubeCollider::CubeCollider(Vector3* position_, Matrix* rotation_, Vector3 length_, Type tag_)
	: ColliderBase(position_, rotation_, tag_){
	length = length_;
	posDelta = {
		Vector3(-length.x,  length.y,  length.z),
		Vector3(length.x, -length.y,  length.z),
		Vector3(length.x,  length.y, -length.z)
	};
	isActive = true;
}

//�ړ����Ȃ������蔻��̏ꍇ�̃R���X�g���N�^
CubeCollider::CubeCollider(Vector3 position_, Matrix rotation_, Vector3 length_, Type tag_)
	: ColliderBase(new Vector3(position_), new Matrix(rotation_), tag_) {
	length = length_;
	posDelta = {
		Vector3(-length.x,  length.y,  length.z),
		Vector3(length.x, -length.y,  length.z),
		Vector3(length.x,  length.y, -length.z)
	};
	isActive = true;
}