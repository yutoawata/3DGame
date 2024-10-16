#pragma once
#include "..\BaseClass\SceneBase.h"

//�^�C�g���V�[���N���X
class TitleScene :public SceneBase {
	//�����o�֐�
public:
	//�R���X�g���N�^
	TitleScene(int set_size = 60);
	//�f�X�g���N�^
	~TitleScene();

	//�V�[������
	SceneBase* Run() override;
	//�J�ڃt���O��Ԃ�
	SceneBase* ChangeNext() override;

	//�����o�萔
	static const float CHANGE_INTERVAL;	//�V�[���J�ڂ̃C���^�[�o��

	//�����o�ϐ�
	std::string title = "3DGame";		//�^�C�g���e�L�X�g
	ButtonUI* startButton = nullptr;	//�V�[���J�ڃ{�^��(�J�ڐ�̓v���C�V�[��)
	float timer = 0.0f;					//�J�ڂ��Ă��Ă���̌o�ߎ���
};