#pragma once
#include <string>
#include "MoverBase.h"
#include "..\ManagerClass\FPSManager.h"

//�X�e�[�g�̊��N���X
template<class Object>
class StateBase {
	//�����o�֐�
public:
	//�R���X�g���N�^
	StateBase(Object* holder_);
	//�f�X�g���N�^
	virtual ~StateBase();

	//�A�N�Z�T

	//�X�e�[�g��ێ����Ă���I�u�W�F�N�g��
	Vector3 getHolderPosition() const { return holderPosition; }
	Vector3 getHolderAngle() const { return holderAngle; }
	//���g�̃X�e�[�g�ł̃A�j���[�V�����̖��O��Ԃ�
	std::string getAnimationName() const { return animationName; }

	//���g�̃X�e�[�g�ł������ۂ̏���
	virtual StateBase<Object>* Run() = 0;

	//�����o�ϐ�
protected:
	Object* holder = nullptr;				//�X�e�[�g��ێ����Ă���N���X�̃A�h���X
	Vector3 holderPosition = Vector3::ZERO;	//���g��ێ����Ă���I�u�W�F�N�g�̍��W
	Vector3 holderAngle = Vector3::ZERO;	//���g��ێ����Ă���I�u�W�F�N�g�̊p�x
	std::string animationName = "";			//���g�̃X�e�[�g�ł̃A�j���[�V�����̖��O
};