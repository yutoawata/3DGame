#pragma once
#include"DxLib.h"

//�t���[�����[�g�Ǘ��N���X
class FPSManager {
	//�����o�֐�
private:
	//�R���X�g���N�^
	FPSManager();
	FPSManager(FPSManager&) = delete;
	//�f�X�g���N�^
	~FPSManager();

public:
	//�C���X�^���X��Ԃ�
	static FPSManager* getInstance() { return instance; }

	//�A�N�Z�T
	//1�t���[���ɂ����������Ԃ�Ԃ�
	float getDeltaTime() { return 1.0f / fps; }	//1�t���[���Ōo�߂�������
	//�t���[�����[�g��Ԃ�
	float getFPS() { return fps; }

	//�C���X�^���X�̐�������
	static void CreateInstance();
	//�C���X�^���X�̍폜����
	static void DeleteInstance();
	//�X�V����
	void Update();
	//1/60�b�o�܂ŏ������ꎞ��~
	void Wait();
	
	//�����o�萔
private:
	static const int MAX_FPS = 60;			//�t���[�����[�g�̍ő�l

	//�����o�ϐ�
	static FPSManager* instance;			//���t�@�C���ł̌Ăяo���p�̃C���X�^���X
	int start_time = 0;						//�J�n���̎���
	int count = MAX_FPS;					//�t���[���̃J�E���g
	float fps = static_cast<float>(MAX_FPS);//�Q�[�����̃t���[�����[�g

};