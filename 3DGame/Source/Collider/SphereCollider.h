#pragma once
#include "..\BaseClass\ColliderBase.h"

//���`�̓����蔻����N���X
class SphereCollider : public ColliderBase {
	//�����o�֐�
public:
	//�R���X�g���N�^
	SphereCollider(Vector3* position_,  Matrix* rotation_, float radius_, Type tag_ = Type::BODY);

	//�A�N�Z�T

	//���a��Ԃ�
	float getRadius() const { return radius; }

	//�����o�ϐ�
private:
	float radius = 0;//���a
};