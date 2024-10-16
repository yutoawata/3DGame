#pragma once
#include <vector>
#include "..\Math\Vector3.h"
#include "..\Math\Matrix.h"

//�R���C�_�[�̊��N���X
class ColliderBase {
	//�񋓌^
public:
	enum class Type {
		BODY,
		SEARCH,
		WEAPON
	};

	//�����o�֐�
	
	//�R���X�g���N�^
	ColliderBase(Vector3* position_, Type type_);
	ColliderBase(Vector3* position_, Matrix* rotation_, Type type_);
	//�f�X�g���N�^
	virtual ~ColliderBase();

	//�A�N�Z�T

	//Object�̒��S���W��Ԃ�
	Vector3 getPosition() const { return *position; }
	//�ړ�������Ԃ�
	Vector3 getMoveVector() const { return moveVector; }
	//Collider�̎�ނ�Ԃ�
	Type getType() const { return type; }
	//�����t���O��Ԃ�
	bool IsActive() const { return isActive; }
	//�����t���O��ݒ肷��
	void setIsActive(bool flag_) { isActive = flag_; }

	//�X�V����
	void Update();

	//�����o�ϐ�
protected:
	Vector3* position = nullptr;			//�ʒu���W
	Matrix* rotationMatrix = nullptr;		//��]�s��
	/*
		position��rotation���|�C���^�[�ɂ��Ă���̂�
		���f���ɃR���C�_�[��Ǐ]�₷�����邽�߂�
		���f���̍��W���A�h���X�Ƃ��Ď󂯎��ω��𓯊������邽��
	*/
	Vector3 latePosition = Vector3::ZERO;	//�O�t���[���ł̍��W
	Vector3 moveVector = Vector3::ZERO;		//�ړ��x�N�g��
	Type type = Type::BODY;					//�R���C�_�[�̔��ʗp�̃^�O
	bool isActive = true;					//�R���C�_�[�̃A�N�e�B�u�t���O
};