#pragma once
#include "..\..\BaseClass\MoverBase.h"

class MagicBall : public MoverBase {
	//�����o�֐�
public:
	//�R���X�g���N�^
	MagicBall(Vector3 position_, Vector3 direction_, float high_, int model_handle = MV1LoadModel("3DModel/LightBall.mv1"));
	//�f�X�g���N�^
	~MagicBall();

	//�A�N�Z�T

	//�����t���O��Ԃ�
	bool IsActive() { return isActive; }

	//�X�V�O����
	void Prepare() override;
	//�X�V����
	void Update() override;
	//�`�揈��
	void Draw() override;
private:
	//�Փ˔��莞�̏���
	void OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) override;
	//��A�N�e�B�u������
	void Inactivate();
public:
	//�A�N�e�B�u������
	void Activate(Vector3 position_, Vector3 direction_);

	//�����o�萔
private:
	static const float ACTIVE_TIME;//�A�N�e�B�u��Ԃ̐�������
	static const float IDLING_TIME;//�ҋ@��Ԃ̐�������

	//�����o�ϐ�
	Vector3 direction = Vector3::ZERO;	//�ړ�����
	int colliderNum = 0;				//�U���p�̃R���C�_�[�v�f�ԍ�
	float speed = 200.0f;				//�ړ����x
	float radius = 30.0f;				//���a
	float high = 0.0f;					//���ˈʒu�̍���
	float timer = 0.0f;					//�^�C�}�[
	bool isActive = false;				//�����t���O
	bool isBrake = false;				//���Ńt���O
};