#pragma once
#include <vector>
#include "..\BaseClass\UIBase.h"

class UIManager {
	//�����o�֐�
public:
	//�f�X�g���N�^
	~UIManager();

	//�A�N�Z�T
	
	//�C���X�^���X��Ԃ�
	static UIManager* Instance() { return instance; }

	//�C���X�^���X�̐�������
	static void CreateInstance();
	//�C���X�^���X�̍폜����
	static void DeleteInstance();
	//UIList�o�^����
	void AddList(UIBase* ui_);
	//�`�揈��
	void Draw() const;
	//���X�g���폜
	void ClearList();
private:
	//�R���X�g���N�^
	UIManager() {}
	UIManager(const UIManager&) = delete;

	//�����o�ϐ�
	static UIManager* instance;//���t�@�C���ł̌Ăяo���p�̃C���X�^���X
	std::vector<UIBase*> UIList;//UI�I�u�W�F�N�g�̃��X�g
};