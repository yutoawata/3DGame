#pragma once
#include "..\BaseClass\MoverBase.h"
#include "..\Collider\ObjectCollider.h"
#include "Strategy\BossAI.h"
#include "State/EnemyIdleState.h"
#include "..\UI\HPBar.h"

class Mutant : public MoverBase {
	enum class Animation {
		ATTACK,
		DAMAGE,
		DIE,
		IDLE,
		JUMP,
		RUN,
		WALK
	};
public://�����o�֐�
	//�R���X�g���N�^
	Mutant(MoverBase* target_, Vector3 position_ = Vector3(200.0f, 80.0f, 200.0f), int model_handle = MV1LoadModel("3DModel/Enemy.mv1"));
	//�f�X�g���N�^
	~Mutant();

	//�A�N�Z�T
	template<class Object>
	BossAI<Object>* getAI() const { return AI; }

	//�X�V�O����
	void Prepare() override;
	//�X�V����
	void Update() override;
	//�`�揈��
	void Draw() override;
	
private:
	//�Փˎ��̏���
	void OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) override;
	//�ڕW�̔�������
	void CheckFind();
	//�A�j���[�V�����̑J�ڏ���
	void ChengeAnimation(std::string animation_name);

	//�����o�萔
	static const int WEAPON_FRAME_NUM = 13;	//����̃t���[���ԍ�
	static const int HIT_POINT = 600;		//hitPoint�̍ő�l
	static const int ATTACK_POINT = 10;		//�U����
	static const float MOVE_SPEED;			//�ړ����x
	static const float SEARCH_DISTANCE;		//���G�͈�

	//�����o�ϐ�
	StateBase<Mutant>* currentState = nullptr;//���݂̃X�e�[�g
	BossAI<Mutant>* AI = nullptr;			//�{�X���߂��݁[�p��AI
	HPBar* hitPointUI = nullptr;			//HP�o�[
	Animation currentAnim = Animation::IDLE;//���݂̃A�j���[�V����
	Vector3 weaponPosition = Vector3::ZERO;	//�U���p�̃I�u�W�F�N�g�̍��W
	Matrix weaponRotation = Matrix::INDENT;	//�U���p�̃I�u�W�F�N�g�̉�]�s��
	int attackColliderNum = 0;				//�U���p�̃I�u�W�F�N�g�̃R���C�_�[�̗v�f�ԍ�
	float attackInterval = 0.0f;			//�_���[�W��^����Ԋu
	float intervalTimer = 0.0f;				//�U���Ԋu�̎��Ԃ��v������^�C�}�[
	bool isCollision = false;				//�Փ˃t���O
	bool isDamage = false;					//�_���[�W�t���O
};
