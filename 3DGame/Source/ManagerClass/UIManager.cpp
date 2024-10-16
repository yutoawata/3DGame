#include "UIManager.h"

UIManager* UIManager::instance = new UIManager();

//デストラクタ
UIManager::~UIManager() {
	for (UIBase* ui : UIList) {
		if (ui != nullptr) {
			delete ui;
		}
	}
}

//
void UIManager::CreateInstance() {
	if (instance == nullptr) {
		instance = new UIManager();
	}
}

void UIManager::DeleteInstance() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

void UIManager::ClearList() {
	UIList.clear();
	int i = 0;
}

void UIManager::AddList(UIBase* ui_) {
	UIList.emplace_back(ui_);
}

void UIManager::Draw() const {
	for (UIBase* UI : UIList) {
		if (UI->IsVisible()) {
			UI->Draw();
		}
	}
}