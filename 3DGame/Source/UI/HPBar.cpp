#include "HPBar.h"

//�R���X�g���N�^
HPBar::HPBar(Vector2 position_, const int& hit_point, int width_, int height_, std::string name_)
	: UIBase(position_), nextHitPoint(&hit_point) {
	maxHitPoint = hit_point;
	currentHitPoint = hit_point;
	width = width_;
	height = height_;
	name = name_;
}

//�`�揈��
void HPBar::Draw() {
	
	if (currentHitPoint > *nextHitPoint) {
		currentHitPoint--;
	}

	// �ʏ�̃o�[�̐F
	int color = Color::GREEN;
	// �g�o�`��̒l�������ȉ���������
	if (*nextHitPoint <= maxHitPoint / 2) {
		// ���F
		color = Color::YELLOW;
	}
	// �g�o���c��P�̎�
	if (*nextHitPoint <= maxHitPoint / 4) {
		// ��
		color = Color::RED;
	}

	//HP�o�[�̒�����HP�̊����ɍ��킹�ĒZ������
	float delta = static_cast<float>(currentHitPoint) / static_cast<float>(maxHitPoint);
	int lineSize = static_cast<int>(width * delta);
	// HP �̒l���̑傫�������l�p�Ɏ��܂�悤�ɒl��傫�����܂�
	DrawFillBox(position.x, position.y, position.x + lineSize, position.y + height, Color::RED);
	//HP�o�[�̒�����HP�̊����ɍ��킹�ĒZ������
	delta = static_cast<float>(*nextHitPoint) / static_cast<float>(maxHitPoint);
	lineSize = static_cast<int>(width * delta);
	DrawFillBox(position.x, position.y, position.x  + lineSize, position.y + height, color);
	DrawLineBox(position.x, position.y, position.x + width, position.y + height, Color::WHITE);
	//�I�u�W�F�N�g����\��(20�E5�͕����̈ʒu�𒲐����邽�߂̒l)
	DrawFormatString(position.x + 20, position.y + 5, Color::BLOCK, name.c_str());
}
