#pragma once
#include <vector>
#include "..\Math\Vector3.h"

template<class Object>
//�s��AI�̊��N���X
class AIBase {
	//�����o�֐�
public:
	//�R���X�g���N�^
	AIBase(Object* holder_);
	//�f�X�g���N�^
	virtual ~AIBase();

	//�A�N�Z�T
	std::vector<Vector3> getRouteList() { return routeList; }

	//�X�V����
	virtual Vector3 SelectMovePosition() = 0;

	//�����o�ϐ�
protected:
	std::vector<Vector3> routeList;			//�p�j���[�g�̊�_���W�̔z��
	Object* holder = nullptr;				//AI��ێ����Ă���Object
	Vector3 targetPosition = Vector3::ZERO;	//�ړ��Ώۂ̍��W
	Vector3 moveDirection = Vector3::ZERO;	//�ړ�����
};