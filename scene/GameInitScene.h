#pragma once

#include "BaseScene.h"

//=============================
// �Q�[���������V�[���N���X
//===============================
class GameInitScene : public BaseScene
{
public:
	GameInitScene() {};
	~GameInitScene() {};

	void Init() override;
	BaseScene* Update() override;
	void Draw() override;
};

