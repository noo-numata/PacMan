#pragma once

#include "BaseScene.h"

//=============================
// �^�C�g���V�[���N���X
//===============================
class TitleScene : public BaseScene
{
public:
	TitleScene():m_TitleImageID(0) {};
	~TitleScene() {};

	void Init() override;
	BaseScene* Update() override;
	void Draw() override;

private:
	int m_TitleImageID;
};
