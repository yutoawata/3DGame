#pragma once
#include <string>
#include "..\BaseClass\MoverBase.h"
#include "..\State\IdleState.h"
#include "..\Camera\Camera.h"
#include "..\Collider\ObjectCollider.h"
#include "..\UI\HPBar.h"

class MoverBase;

class Soldier : public MoverBase {
public://�����o�֐�
	enum class Animation {
		ATTACK,
		AVOID,
		DAMAGE,
		DIE,
		IDLE,
		JUMP,
		RUN,
		WALK
	};

	//�R���X�g���N�^
	Soldier(Vector3 position_ = Vector3(0.0f, 40.0f, 0.0f), int model_handle = MV1LoadModel("./3DModel/Player.mv1"));
	//�f�X�g���N�^
	~Soldier();
	
	//�X�V�O����
	void Prepare() override;
	//�X�V����
	void Update() override;
	//�`�揈��
	void Draw() override;
	//�Փ˔��莞�̏���
	void OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) override;

private:
	//�A�j���[�V�����̑J�ڏ���
	void ChengeAnimation(std::string animation_name);
	 
	//�����o�萔
	static const int WEAPON_FRAME_NUM = 75;	//����̃t���[���ԍ�
	static const int HIT_POINT = 100;		//hitPoint�̍ő�l
	static const int ATTACK_POINT = 10;		//�U����
	static const int ATTACK_SOUND;			//�U�����̌��ʉ�
	static const float MOVE_SPEED;			//�ړ����x
	static const float GAVITY_POWER;		//�d�͂̋���

	//�����o�ϐ�
	Camera* camera = nullptr;					//�J�����I�u�W�F�N�g
	StateBase<Soldier>* currentState = nullptr;	//���݂̃X�e�[�g
	HPBar* hitPointUI = nullptr;				//HP�o�[
	Animation currentAnim = Animation::IDLE;	//���݂̃A�j���[�V����
	Vector3 attackPosition = Vector3::ZERO;		//�U���̓����蔻��̈ʒu
	Matrix weaponRotation;						//�U���̓����蔻��̉�]�s��
	int weaponColliderNum = 0;					//�U���̓����蔻��̗v�f�ԍ�
	float damageInterbal = 0;					//�_���[�W���󂯂�Ԋu
	float interbalTimer = 0;					//�Ԋu�̃^�C�}�[
	bool isCollision = false;					//�Փ˃O���O
	bool isDamage = false;						//�_���[�W�t���O
};