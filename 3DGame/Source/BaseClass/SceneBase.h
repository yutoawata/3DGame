#pragma once
#include <string>
#include "DxLib.h"
#include "..\UI\Button.h"
#include "..\ManagerClass\UIManager.h"

//�V�[���N���X�̐e�N���X
class SceneBase {
	//�񋓌^
public:
	//�V�[���̎��
	enum class Kind {
		NONE,
		TITLE,
		PLAY,
		RESULT,
	};

	//�����o�֐�

	//�R���X�g���N�^
	SceneBase(int set_size);
	//�f�X�g���N�^
	virtual ~SceneBase();

	//�A�N�Z�T

	//�J�ڌ�̃V�[���̎�ނ�Ԃ�
	Kind getNextKind() const { return next; }
	
	//�V�[������
	virtual SceneBase* Run() = 0;
	//�V�[���J�ڏ���
	virtual SceneBase* ChangeNext() = 0;

	//�����o�ϐ�
protected:
	Kind next = Kind::NONE;	//�V�[���̏���
	int titleFontHandle = 0;//���o���t�H���g�̃n���h��
	int fontSize = 0;		//�V�[�����̃t�H���g�̃T�C�Y
};