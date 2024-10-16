#pragma once
#include "DxLib.h"
#include "..\Math\Vector2.h"
#include "..\Math\Matrix.h"
#include "..\Collider\SphereCollider.h"
#include "..\BaseClass\MoverBase.h"
#include "..\Color\Color.h"

//�J�����N���X
class Camera {
	//�����o�֐�
public:
	//�R���X�g���N�^
	Camera(Vector3 target_position);
	
	//�A�N�Z�T
	Vector3 getPosition() { return position; }

	//�X�V����
	void Update(const Vector3& target_position);
	
private:
	//�ړ�����
	void Move(const Vector3& target_position);

	//�����o�萔
	static const Vector2 STANDERD_CURSOR_POSITION;	//��ʂ̒��S���W				
	static const float ROTATE_SPEED;				//��]���x

	//�����o�ϐ�
	Vector3 position = Vector3::ZERO;				//�ʒu���W
	Vector3 upVector = Vector3(0.0f, 1.0f, 0.0f);	//�J�����̏�����̃x�N�g��
	Vector3 angleVector = Vector3(0.0f, 0.0f, 0.0f);//�e���̉�]�p�x
	Vector2 cursorPosition = Vector2(0, 0);			//�}�E�X�J�[�\���̈ʒu���W
	float near_ = 0.1f;								//�J�����̕`��͈͂̍ŒZ����
	float far_ = 1000.0f;							//�J�����̕`��͈͂̍Œ�����
	float distance = 300.0f;						//�`��ΏۂƃJ�����Ƃ̋���
	/*
		near_��far_�̂�define�萔��near��far����`�ςׁ݂̈A
		�A���_�[�o�[( _ )�������邱�Ƃŋ�ʂ��Ă���
	*/
};