#pragma once
#include "..\BaseClass\SceneBase.h"
#include "..\Field\Field.h"
#include "..\Player\Soldier.h"
#include "..\Enemy\Mutant.h"
#include "..\Enemy\\Magician.h"
#include "..\ManagerClass\ColliderManager.h"
#include "..\ManagerClass\MoverManager.h"

class PlayScene :public SceneBase {
	//�����o�֐�
public:
	//�R���X�g���N�^
	PlayScene(int set_size = 32);
	//�f�X�g���N�^
	~PlayScene();

	//�V�[������
	SceneBase* Run() override;
	//�V�[���J�ڏ���
	SceneBase* ChangeNext() override;

	//�����o�ϐ�
private:
	Soldier* player = nullptr;		//���@�I�u�W�F�N�g
	Mutant* enemy = nullptr;		//�G�l�~�[�I�u�W�F�N�g
	Magician* magician = nullptr;	//���p�t�I�u�W�F�N�g
	Field* field = nullptr;			//�n�`�I�u�W�F�N�g
};