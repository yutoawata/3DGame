#pragma once
#include <string>
#include "Strategy/LongRangeAI.h"
#include "Weapon/MagicBall.h"
#include "..\BaseClass\MoverBase.h"
#include "..\BaseClass\StateBase.h"
#include "..\UI\HPBar.h"

//���p�t�N���X
class Magician : public MoverBase {
	//�񋓌^
	enum class Animation {
		ATTACK,
		DAMAGE,
		DIE,
		IDLE,
		RUN,
	};
	//�����o�֐�
public:
	//�R���X�g���N�^
	Magician(MoverBase* target_, MoverBase* boss_, Vector3 position_, int model_handle = MV1LoadModel("3DModel/Magician.mv1"));
	//�f�X�g���N�^
	~Magician();

	//�A�N�Z�T

	
	template<class Object>
	//�s��AI�N���X��Ԃ�
	LongRangeAI<Object>* getAI() const { return AI; }

	MagicBall* getMagic() const { return lightBall; }

	bool IsFind() { return isFind; }

	//�X�V�O����
	void Prepare() override;
	//�X�V����
	void Update() override;
	//�`�揈��
	void Draw() override;

private:
	//�Փ˔��莞�̏���
	void OnCollision(const ObjectCollider& other_, const ColliderBase::Type& collider_type) override;
	//�A�j���[�V�����̑J�ڏ���
	void ChengeAnimation(std::string animation_name);

	//�����o�萔
	static const int HIT_POINT = 1000;	//hitPoint�̍ő�l

	//�����o�ϐ�
	LongRangeAI<Magician>* AI = nullptr;		//�������U���p��AI
	MoverBase* boss = nullptr;					//�{�X�I�u�W�F�N�g
	StateBase<Magician>* currentState = nullptr;//���݂̃X�e�[�g
	MagicBall* lightBall = nullptr;				//�U���p�̌��e
	HPBar* hitPointUI = nullptr;				//HP�o�[UI
	Animation currentAnim = Animation::IDLE;	//���݂̃A�j���[�V����
	float damageInterbal = 0.0f;				//�_���[�W���󂯂�Ԋu
	float interbalTimer = 0.0f;					//�Ԋu�̎��Ԃ𑪂�^�C�}�[
	bool isCollision = false;					//�Փ˃t���O
	bool isDamage = false;						//�_���[�W�t���O
	bool canCreate = false;						//�U�����@�̐����t���O
};