#include "FPSManager.h"
#include "..\Color\Color.h"

//���t�@�C���ł̌Ăяo���p�̃C���X�^���X�𐶐�
FPSManager* FPSManager::instance = new FPSManager();

//�R���X�g���N�^
FPSManager::FPSManager() {}

//�f�X�g���N�^
FPSManager::~FPSManager() {}

//�X�V����
void FPSManager::Update() {
	if (count == 0) {
		//�~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
		start_time = GetNowCount();
	}
	if (count == MAX_FPS) {
		//�~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
		int t = GetNowCount();
		fps = 1000.f / ((t - start_time) / static_cast<float>(MAX_FPS));
		count = 0;
		start_time = t;
	}
	count++;
}

//1/60�b�o�܂ŏ������ꎞ��~
void FPSManager::Wait() {
	//�~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
	int nTookTime = GetNowCount() - start_time;
	int nWaitTime = count * 1000 / MAX_FPS - nTookTime;
	if (nWaitTime > 0) {
		Sleep(nWaitTime);
	}
}

//�C���X�^���X�̐�������
void FPSManager::CreateInstance() {
	if (instance == nullptr) {
		instance = new FPSManager();
	}
}

//�C���X�^���X�̍폜����
void FPSManager::DeleteInstance() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}