#include "Button.h"

//�R���X�g���N�^
ButtonUI::ButtonUI(Vector2 position_, Vector2 length_, Vector2 margin_, std::string text_)
	: UIBase(position_) {
	length = length_;
	text = text_;
	margin = margin_;
}

//�f�X�g���N�^
ButtonUI::~ButtonUI() {
	DeleteSoundMem(clickSound);
}

//�{�^�����N���b�N���ꂽ���̔���
bool ButtonUI::CheckClick() {
	//�}�E�X�J�[�\���̍��W���擾
	int cursorPositionX = 0;
	int cursorPositionY = 0;
	GetMousePoint(&cursorPositionX, &cursorPositionY);

	//�J�[���邪�{�^���ɏd�Ȃ��Ă���Ȃ�
	if (cursorPositionX > position.x && cursorPositionX < position.x + length.x
		&& cursorPositionY > position.y && cursorPositionY < position.y + length.y) {
		//�{�^���̐F��Ԃɂ���
		color = Color::RED;

		//���N���b�N���ꂽ��
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			//���莞�̌��ʉ��𗬂�
			PlaySoundMem(clickSound, DX_PLAYTYPE_BACK);
			return true;
		}
	}
	//�J�[�\�����{�^������O��Ă�����
	else {
		//�F�𔒂ɂ���
		color = Color::WHITE;
	}
	return false;
}

//�`�揈��
void ButtonUI::Draw() {
	//�{�^���̖��O��`��
	DrawFormatString(position.x + margin.y, position.y + margin.y, color, text.c_str());
	//�{�^���̘g��`��
	DrawLineBox(position.x, position.y, position.x + length.x, position.y + length.y, color);
}