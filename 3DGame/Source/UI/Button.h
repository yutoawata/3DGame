#pragma once
#include <string>
#include "..\BaseClass\UIBase.h"
#include "..\Color\Color.h"

class ButtonUI : public UIBase {
	//�����o�֐�
public:
	//�R���X�g���N�^
	ButtonUI(Vector2 position_, Vector2 length_, Vector2 margin_, std::string text_);
	//�f�X�g���N�^
	~ButtonUI();

	//�`�揈��
	void Draw() override;
	//�{�^�����N���b�N���ꂽ���𔻒�
	bool CheckClick();

	//�����o�ϐ�
private:
	int clickSound = LoadSoundMem("Sound/Decision.mp3");//�N���b�N�����ۂ̌��ʉ��̃n���h��
	std::string text;									//�{�^���̒��ɕ\������e�L�X�g
	Vector2 length = Vector2::ZERO;						//�{�^���̕�(x = ���@y = �c)
	Vector2 margin = Vector2::ZERO;						//�e�L�X�g��\������ۂ̘g�Ƃ̋���
	unsigned int color = Color::BLOCK;					//�`�悷��ۂ̐F
};