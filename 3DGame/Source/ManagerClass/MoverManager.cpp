#include "MoverManager.h"

MoverManager* MoverManager::instance = new MoverManager();//�N���X�̃C���X�^���X(�V���O���g��)

//�f�X�g���N�^
MoverManager::~MoverManager() {}

//�C���X�^���X�̐���
void MoverManager::CreateInstance() {
	if (instance == nullptr) {
		instance = new MoverManager();
	}
}

//�C���X�^���X�̍폜
void MoverManager::DeleteInstance() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

//���X�g�o�^����
void MoverManager::AddList(MoverBase* const object_) {
	objectList.emplace_back(object_);
}

//�X�V�O����
void MoverManager::Prepare() {
	for (MoverBase* object : objectList) {
		object->Prepare();
	}
}

//�X�V����
void MoverManager::Update() {
	for (MoverBase* object : objectList) {
		object->Update();
	}
}

//�`�揈��
void MoverManager::Draw() {
	for (MoverBase* object : objectList) {
		object->Draw();
	}
}