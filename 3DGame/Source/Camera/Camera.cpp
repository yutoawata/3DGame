#include "Camera.h"
#include <vector>

const Vector2 Camera::STANDERD_CURSOR_POSITION = Vector2(960, 540);	//�X�N���[���̒��S���W
const float Camera::ROTATE_SPEED = 2.0f;							//��]���x

//�R���X�g���N�^
Camera::Camera(Vector3 target_position) {
	//�J�����̕`��͈͂̐ݒ�
	SetCameraNearFar(near_, far_);
	position = target_position + Vector3(0.0f, 0.0f, -distance);
	upVector = Vector3(0.0f, 1.0f, 0.0f);
	//�J�����̎p����ݒ�
	SetCameraPositionAndTargetAndUpVec(position, target_position, upVector);
}

//�X�V����
void Camera::Update(const Vector3& target_position) {
	Move(target_position);
	//�X�V��������ݒ�
	SetCameraPositionAndTargetAndUpVec(position, target_position, upVector);

	//�}�E�X�J�[�\���̍��W����ʂ̒��S�ɐݒ�
	SetMousePoint(STANDERD_CURSOR_POSITION.x, STANDERD_CURSOR_POSITION.y);
}

//�ړ�����
void Camera::Move(const Vector3& target_position) {
	Vector2 newPosition = Vector2::ZERO;

	//�}�E�X�J�[�\���̍��W���擾
	GetMousePoint(&newPosition.x, &newPosition.y);

	//�}�E�X�J�[�\������Ɉړ����Ă����
	if (STANDERD_CURSOR_POSITION.y < newPosition.y) {
		//�O�����ɉ�]������
		angleVector.x += (DX_PI_F / 180.0f) * ROTATE_SPEED;
	}
	//�}�E�X�J�[�\�������Ɉړ����Ă����
	if (STANDERD_CURSOR_POSITION.y > newPosition.y) {
		//������ɉ�]������
		angleVector.x -= (DX_PI_F / 180.0f) * ROTATE_SPEED;
	}
	//�}�E�X�J�[�\�����E�Ɉړ����Ă����
	if (STANDERD_CURSOR_POSITION.x > newPosition.x) {
		//�E�����ɉ�]������
		angleVector.y -= (DX_PI_F / 180.0f) * ROTATE_SPEED;
	}
	//�}�E�X�J�[�\�������Ɉړ����Ă����
	if (STANDERD_CURSOR_POSITION.x < newPosition.x) {
		//�������ɉ�]������
		angleVector.y += (DX_PI_F / 180.0f) * ROTATE_SPEED;
	}

	//��]�p�x�����]�s����擾
	Matrix rotate = Matrix::GetRotateMatrix(angleVector);

	//�J�����̈ʒu���X�V
	position = target_position + (rotate * Vector3(0.0f, 0.0f, -distance));
}