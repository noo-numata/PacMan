#pragma once

#include "BaseScene.h"

//=============================
// ゲームシーンクラス
//===============================
class GameScene : public BaseScene
{
public:
	GameScene(){};
	virtual ~GameScene(){};

	void Init() override;
	BaseScene* Update() override;
	void Draw() override;

protected:
	enum Time
	{
		GAME_START_WAIT_TIME = (4 * 60)
	};
};

