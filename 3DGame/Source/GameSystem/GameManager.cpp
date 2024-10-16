#include "GameManager.h"

//�R���X�g���N�^
GameManager::GameManager() {
	//�𑜓x��ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);

	//�t���X�N���[���ɂ���
	ChangeWindowMode(FALSE);
	isInit = DxLib_Init();

	//Z�o�b�t�@�̎g�p������
	SetUseZBuffer3D(TRUE);
	//Z�o�b�t�@�̏������݂�����
	SetWriteZBuffer3D(TRUE);
	//�}�E�X�J�[�\���̕\����OFF
	SetMouseDispFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	//���݂̃V�[�����^�C�g���ɂ���
	currentScene = new TitleScene();
	//UI�Ǘ��N���X�𐶐�
	UIManager::CreateInstance();
	FPSManager::CreateInstance();
}

//�f�X�g���N�^
GameManager::~GameManager() {
	delete currentScene;
	currentScene = nullptr;
	UIManager::DeleteInstance();
	FPSManager::DeleteInstance();
	InitSoundMem();
	DxLib_End();
}

//�Q�[�����[�v
void GameManager::Run() {
	while (!ProcessMessage() && isInit != TRUE) {

		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}
		
		ClearDrawScreen();

		//�V�[�����̏���
		currentScene = currentScene->Run();
		//UI��`��
		UIManager::Instance()->Draw();
		//�t���[�����[�g�Ǘ��N���X�̍X�V����
		FPSManager::getInstance()->Update();

		ScreenFlip();

		FPSManager::getInstance()->Wait();
	}
}