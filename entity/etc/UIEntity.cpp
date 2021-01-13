#include "UIEntity.h"
#include "../player/Player.h"
#include "Map.h"

//===============================
//UIƒNƒ‰ƒX
//==============================
void UIEntity::SetGraphicData(int entityImage)
{
	m_ReadyImage = DerivationGraph(32*4, 32*7 + 16, CHIP_SIZE_X*4, CHIP_SIZE_Y/2, entityImage);
	m_GameOverImage = DerivationGraph(32*6, 32*6 + 16, CHIP_SIZE_X*5, CHIP_SIZE_Y / 2, entityImage);
}

void UIEntity::Init()
{
	m_Mode = GAME_START_WAIT;
	m_ModeOld = GAME_START_WAIT;
	m_ModeCounter = 0;
}

void UIEntity::StartGame()
{
	Init();
}

void UIEntity::RestartGame()
{
	Init();
}

void UIEntity::Update()
{
	m_ModeOld = m_Mode;
	if (m_PlayerData != nullptr)
	{
		switch (m_Mode)
		{
		case GAME_START_WAIT:
			if (m_PlayerData->IsGameStartWait() == false)
			{
				m_Mode = NORMAL;
			}
			break;

		case NORMAL:
			if (m_PlayerData->IsDeath() && m_PlayerData->GetLineNum() == 0)
			{
				m_Mode = GAME_OVER;
			}
			break;

		case GAME_OVER:
			break;
		}
	}
}

void UIEntity::Draw()
{
	if (m_Mode == GAME_START_WAIT)
	{
		StratWaitDraw();
	}
	else if (m_Mode == GAME_OVER)
	{
		GameOverDraw();
	}

	StatusDraw();
};

void UIEntity::StratWaitDraw()
{
	DrawRotaGraph(CHIP_SIZE_X * 8 + 16, CHIP_SIZE_Y * 7 + 16, 1.0f, 0.0f, m_ReadyImage, true, false);
}

void UIEntity::GameOverDraw()
{
	DrawRotaGraph(CHIP_SIZE_X * 8 + 16, CHIP_SIZE_Y * 7 + 16, 1.0f, 0.0f, m_GameOverImage, true, false);
}

void UIEntity::StatusDraw()
{
	int mapSizeX = CHIP_SIZE_X * Map::MAP_SIZE_X;
	int topY = 20;

	DrawFormatString((mapSizeX + 20), topY, 0xff0000, "PAC-MAN");

	if (m_PlayerData != nullptr)
	{
		DrawFormatString((mapSizeX + 20), topY + 36, 0xff0000, "STAGE %d", (m_PlayerData->GetStageNum() + 1));
		DrawFormatString((mapSizeX + 30), topY + 68, 0xff0000, "SCORE");
		DrawFormatString((mapSizeX + 30), topY + 84, 0xffffff, "%d", m_PlayerData->GetScore());
		DrawFormatString((mapSizeX + 30), topY + 108, 0xff0000, "LIFE");
		DrawFormatString((mapSizeX + 30), topY + 124, 0xffffff, "%d", m_PlayerData->GetLineNum());
	}
};
