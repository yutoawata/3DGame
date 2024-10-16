#pragma once
#include <string>
#include "..\BaseClass\UIBase.h"
#include "..\Color\Color.h"

//HP�o�[UI�N���X
class HPBar : public UIBase {
	//�����o�֐�
public:
	//�R���X�g���N�^
	HPBar(Vector2 position_, const int& hit_point, int width_, int height_, std::string name_);

	//�`�揈��
	void Draw() override;

	const int* const nextHitPoint;//�������HP
	/*
		const �|�C���^ const�ŃA�h���X�̕ύX��address��̒l�̕ύX���֎~
	*/

	//�����o�ϐ�
private:
	std::string name;
	int maxHitPoint = 0;	//HI�̍ő�l
	int currentHitPoint = 0;//��������HP
	int width = 0;			//UI�̉���
	int height = 0;			//UI�̏c��
};
