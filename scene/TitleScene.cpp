#include "TitleScene.h"
#include "GameInitScene.h"
#include "../entity/etc/Map.h"

//===============================
//タイトルシーンクラス
//==============================
void TitleScene::Init()
{
	m_FrameCounter = 0;
	m_TitleImageID = LoadGraph("image/title.png");
}

BaseScene* TitleScene::Update()
{
	m_FrameCounter++;
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return new GameInitScene();
	}
	return this;
}

void TitleScene::Draw()
{
	int screenSizeX = CHIP_SIZE_X * Map::MAP_SIZE_X;
	
	DrawGraph(50, 0, m_TitleImageID, true);

	if (((m_FrameCounter / 30) % 2) == 0)
	{
		DrawFormatString(((screenSizeX / 2) - 10), 320, 0xffffff, "HIT SPACE KEY");
	}
}
