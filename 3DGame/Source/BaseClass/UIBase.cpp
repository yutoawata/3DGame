#include "UIBase.h"
#include "..\ManagerClass\UIManager.h"

//�R���X�g���N�^
UIBase::UIBase(Vector2 position_) {
	position = position_;
	UIManager::Instance()->AddList(this);
}