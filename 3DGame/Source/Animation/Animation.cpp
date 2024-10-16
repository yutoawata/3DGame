#include "Animator.h"

const float Animator::ANIMATION_SPEED = 1.0f;//�A�j���[�V�����̍Đ����x

//�R���X�g���N�^
Animator::Animator(int model_handle) {
	modelHandle = model_handle;
}

//�R���X�g���N�^
Animator::Animator(Vector3 position_, int model_handle) {
	position = position_;
	modelHandle = model_handle;
}

//�R���X�g���N�^
Animator::Animator(Vector3 position_, Vector3 angle_, Vector3 scale_, int model_handle) {
	modelHandle = model_handle;
	position = position_;
	angle = angle_;
	scale = scale_;
	ChangeAnimation();
}

//�A�j���[�V�����̍X�V����
void Animator::UpdateAnimation() {
	isFinish = false;
	modelPosition = position;
	//���f���̒��S�ɃI�u�W�F�N�g�̍��W������悤�Ƀ��f���̍��W��������
	modelPosition -= Matrix::GetRotateMatrix(angle) * Vector3(0.0f, modelSize.y, 0.0f);

	//�A�j���[�V�������؂�ւ������
	if (currentAnimID != nextAnimID) {
		timer = 0;
		//�؂�ւ��O�̃A�j���[�V�������f�^�b�`
		MV1DetachAnim(modelHandle, attachIndex);
		ChangeAnimation();
	}

	timer += ANIMATION_SPEED;

	//�A�j���[�V�����̎ڂ��߂����烊�Z�b�g
	if (timer >= totalTime) {
		timer = 0;
		isFinish = true;
	}

	//�Đ����Ԃ�ݒ�
	MV1SetAttachAnimTime(modelHandle, attachIndex, timer);

	//���f���̍��W�E�X�P�[���E��]�p�x��ݒ�
	MV1SetPosition(modelHandle, modelPosition);
	MV1SetRotationXYZ(modelHandle, angle);
	MV1SetScale(modelHandle, scale);
}

//�A�j���[�V�����J�ڏ���
void Animator::ChangeAnimation() {
	currentAnimID = nextAnimID;
	//�A�j���[�V�������A�^�b�`
	attachIndex = MV1AttachAnim(modelHandle, currentAnimID);
	//�A�j���[�V�����̎ڂ��擾
	totalTime = MV1GetAnimTotalTime(modelHandle, currentAnimID);
	//�A�j���[�V�����̍Đ����Ԃ�ݒ�
	MV1SetAttachAnimTime(modelHandle, attachIndex, timer);
}

