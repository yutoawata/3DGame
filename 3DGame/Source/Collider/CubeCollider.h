#pragma once
#include <vector>
#include "..\Color\Color.h"
#include "..\Math\Matrix.h"
#include "..\BaseClass\ColliderBase.h"

//�����̂̓����蔻����N���X
class CubeCollider : public ColliderBase {
public://�����o�֐�
	////�ړ����铖���蔻��̏ꍇ�̃R���X�g���N�^
	CubeCollider(Vector3* position_, Matrix* rotation_, Vector3 length_, Type tag_ = Type::BODY);
	//�ړ����Ȃ������蔻��̏ꍇ�̃R���X�g���N�^
	CubeCollider(Vector3 position_, Matrix rotation_, Vector3 length_, Type tag_ = Type::BODY);

	//�A�N�Z�T
	//�w�肵���ԍ�(x = 0, y = 1, z = 2)�̎��̕����x�N�g��(�P�ʃx�N�g��)��Ԃ�
	Vector3 getDirectoin(int num_) const { return *rotationMatrix * DIRECTION[num_]; }
	//�e�������̒�����Ԃ�
	Vector3 getLength() const { return length; }

	//�����o�萔
private:
	static const int MAX_DIRECTION_NUM = 3;				//�����x�N�g���̖{��
	static const Vector3 DIRECTION[MAX_DIRECTION_NUM];	//�e���̐��̌���

	//�����o�ϐ�
	std::vector<Vector3> posDelta;	//�e�p������Ă��鋗���̃x�N�g���̔z��
	Vector3 length = Vector3::ZERO;	//�e�����̒���
};