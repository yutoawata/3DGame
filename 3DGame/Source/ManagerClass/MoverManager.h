#pragma once
#include "..\BaseClass\MoverBase.h"

//�ړ��I�u�W�F�N�g�̊Ǘ��N���X
class MoverManager {
	//�����o�֐�
public:
	//�R���X�g���N�^
	~MoverManager();

	//�A�N�Z�T

	//�C���X�^���X��Ԃ�
	static MoverManager* getInstance() { return instance; }

	//�C���X�^���X�̐���
	static void CreateInstance();
	//�C���X�^���X�̍폜
	static void DeleteInstance();
	//���X�g�o�^����
	void AddList(MoverBase* const object_);
	//�X�V�O����
	void Prepare();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

private:
	//�R���X�g���N�^
	MoverManager() {}
	//�R�s�[�R���X�g���N�^���폜
	MoverManager(const MoverManager&) = delete;

	//�����o�ϐ�
	static MoverManager* instance;		//�N���X�̃C���X�^���X(�V���O���g��)
	std::vector<MoverBase*> objectList;	//�Ǘ�����I�u�W�F�N�g�̃��X�g
	/*
		���X�g���̃|�C���^�̕ύX���֎~
	*/
};