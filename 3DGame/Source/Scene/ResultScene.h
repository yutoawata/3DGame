#pragma once
#include "..\BaseClass\SceneBase.h"

class ResultScene :public SceneBase {
	//�����o�֐�
public:
	//�R���X�g���N�^
	ResultScene(std::string result_, int set_size = 60);
	//�f�X�g���N�^
	~ResultScene();

	//�V�[������
	SceneBase* Run() override;
	//�V�[���J�ڏ���
	SceneBase* ChangeNext() override;

	//�����o�ϐ�
private:
	std::string result = "";		//���U���g�e�L�X�g
	ButtonUI* titleButton = nullptr;//�V�[���J�ڃ{�^��(�J�ڐ�̓^�C�g���V�[��)
};