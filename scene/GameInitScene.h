#pragma once

#include "BaseScene.h"

//=============================
// ゲーム初期化シーンクラス
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

