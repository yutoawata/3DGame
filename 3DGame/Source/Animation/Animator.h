#pragma once
#include "DxLib.h"
#include "..\Color\Color.h"
#include "..\Math\Vector3.h"
#include "..\Math\Matrix.h"
#include <unordered_map>

//�A�j���[�V��������N���X
class Animator {
	//�����o�֐�
public:
	//�R���X�g���N�^
	Animator(int model_handle);
	Animator(Vector3 position_, int model_handle);
	Animator(Vector3 position_, Vector3 angle_, Vector3 scale_, int model_handle);

	//�A�N�Z�T
	
	//���f���̍��W��Ԃ�
	Vector3 getPosition() const { return position; }
	//���f���̉�]�p�x��Ԃ�
	Vector3 getAngle() const { return angle; }
	//���f���̃n���h����Ԃ�
	int getModelHandle() const { return modelHandle; }
	//�A�j���[�V�����̑��Đ����Ԃ�Ԃ�
	float getTotalAnimationTime() const { return totalTime; }
	//�A�j���[�V�����I���t���O��Ԃ�
	bool IsFinish() const { return isFinish; }

	//�A�j���[�V�����̍X�V����
	void UpdateAnimation();
	//�A�j���[�V�����J�ڏ���
	void ChangeAnimation();

	//�����o�萔
protected:
	static const float ANIMATION_SPEED;			//�A�j���[�V�����̍Đ����x

	//�����o�ϐ�
	Vector3 position = Vector3::ZERO;			//�I�u�W�F�N�g�Ƃ��Ă̍��W(���S�����_)
	Vector3 angle = Vector3::ZERO;				//��]�p�x
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);	//���f���̃X�P�[��
	Vector3 modelSize = Vector3::ZERO;			//�I�u�W�F�N�g�̕�
	int modelHandle = 0;						//�A�j���[�V������ݒ肷�郂�f���̃n���h��
	int nextAnimID = -1;						//���ɍĐ�����A�j���[�V�����ԍ�
	//�N���X���ł����g��Ȃ��̂�private�ɂ���
private:
	Vector3 modelPosition = Vector3::ZERO;		//�`�悷��ۂ̃��f���̍��W(���������_)
	int currentAnimID = -1;						//�A�^�b�`�����A�j���[�V�����̃A�^�b�`�ԍ���
	int attachIndex = -1;						//�A�^�b�`�����A�j���[�V�����̓o�^�ԍ���
	float totalTime = 0;						//�A�j���[�V�����̑��Đ�����
	float timer = 0;							//�A�j���[�V�����̍Đ�����
	bool isFinish = false;						//�A�j���[�V�����̏I���t���O
	/*
		��animationNum��attachIndex�̏����l��-1�Ȃ̂́A
		  0���o�^���ꂽ�A�j���[�V�����̈�ڂ��w�����߁A
		  �A�j���[�V���������݂��Ȃ��l�ł���-1�ŏ��������Ă���
	*/
};