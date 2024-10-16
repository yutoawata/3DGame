#pragma once
#include "..\Math\Vector2.h"

//UI���N���X
class UIBase {
	//�����o�֐�
public:
	//�R���X�g���N�^
	UIBase(Vector2 position_);

	//�A�N�Z�T
	
	//�`��t���O��Ԃ�
	bool IsVisible() { return isVisible; }
	//�`��t���O��ݒ�
	void setIsVisible(bool flag_) { isVisible = flag_; }

	//�`�揈��
	virtual void Draw() = 0 ;

	//�����o�ϐ�
protected:
	Vector2 position = Vector2::ZERO;	//�ʒu���W
	bool isVisible = false;				//�\���t����
};