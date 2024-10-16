#include "UIBase.h"
#include "..\ManagerClass\UIManager.h"

//コンストラクタ
UIBase::UIBase(Vector2 position_) {
	position = position_;
	UIManager::Instance()->AddList(this);
}