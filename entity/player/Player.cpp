#include "Player.h"
#include "../../common/Singleton.h"
#include "../../common/Sound.h"
#include "../etc/Map.h"

//===============================
//プレーヤークラス
//==============================
void Player::SetGraphicData(int entityImage)
{
	// パックマン画像のセット
	for (int i = 0; i < NORMAL_NUM; ++i) {
		m_NormalImage[(i / 2)][(i % 2)] = DerivationGraph(32 * i, 32 * 4, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
	}

	// パックマン停止画像のセット
	m_StopImage = DerivationGraph(32 * 8, 32 * 4, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);

	// パックマン死亡画像のセット
	for (int i = 0; i < DEATH_NUM; ++i) {
		m_DeathImage[i] = DerivationGraph(32 * i, 32 * 5, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
	}
}

void Player::Init()
{
	StartGame();
	m_LifeNum = LIFE_NUM;
	m_Score = 0;
	m_StageNum = 0;
}

void Player::StartGame()
{
	m_Size.x = CHIP_SIZE_X;
	m_Size.y = CHIP_SIZE_Y;
	m_Pos.x = CHIP_SIZE_X * 8;
	m_Pos.y = CHIP_SIZE_Y * 8 + m_Size.y / 2;
	m_Move.x = 0;
	m_Move.y = 0;
	m_Chip.x = 0;
	m_Chip.y = 0;
	m_Speed = 2;
	m_AnimCount = 0;
	m_Dir = DIR_NONE;
	m_Mode = GAME_START_WAIT;
	m_ModeOld = GAME_START_WAIT;
	m_ModeCounter = 0;

	m_IsFirstHit = false;
}

void Player::RestartGame()
{
	StartGame();
}

void Player::Update()
{
	m_Chip.x = m_Pos.x / CHIP_SIZE_X;
	m_Chip.y = m_Pos.y / CHIP_SIZE_Y;

	// モードの更新
	UpdateMode();
		
	if ((m_IsFirstHit == false) ||
		((m_Pos.x - m_Size.x / 2) % CHIP_SIZE_X == 0 &&
		(m_Pos.y - m_Size.y / 2) % CHIP_SIZE_Y == 0)) 
	{
		m_Dir = GetMoveDir();

		// ドットまたはパワーエサがある場合は食べたとき
		if (m_MapData->IsEatSomething(m_Chip.x, m_Chip.y) == true)
		{
			int addScore = 10;
			// パワーエサを食べたとき
			if (m_MapData->IsEatPowerUpDot(m_Chip.x, m_Chip.y) == true)
			{
				m_Mode = POWER_UP;
				addScore = 50;
			}
			Singleton<Sound>::GetInstance().PlaySE(Sound::EAT_DOT);
			m_MapData->EatDat(m_Chip.x, m_Chip.y);

			m_Score += addScore;

			// 全部ドットを食べたとき
			if (m_MapData->IsClear())
			{
				m_Mode = EAT_ALL;
				m_ModeCounter = 0;
			}
		}

		UpdateMove();
	}
	UpdatePos();
}

void Player::Draw()
{
	int dispImage = 0;
	if (m_Mode == DEATH)
	{
		int tmpIndex = (m_AnimCount++ / 8) % DEATH_NUM;
		if (m_AnimCount < DEATH_NUM * 8) 
		{
			dispImage = m_DeathImage[tmpIndex];
		}
	}
	else if (m_Mode == EAT_ALL)
	{
		dispImage = m_StopImage;
	}
	else
	{
		if (m_Move.x != 0 || m_Move.y != 0)
		{
			m_AnimCount++;
		}
		if (m_Dir == DIR_NONE)
		{
			dispImage = m_StopImage;
		}
		else
		{
			dispImage = m_NormalImage[m_Dir][(m_AnimCount / 4) % PLAYER_PTN_NUM];
		}
	}
	DrawRotaGraph(m_Pos.x, m_Pos.y, 1.0f, 0.0f, dispImage, true, false);
}

void Player::Death()
{
	m_Mode = DEATH;
	m_AnimCount = 0;
	m_LifeNum--;
	Singleton<Sound>::GetInstance().PlaySE(Sound::DEATH);
}

void Player::AddEatScore()
{
	m_Score += 100;
}

int Player::GetPowerUpCount() 
{ 
	if (m_Mode == POWER_UP)
	{
		return m_ModeCounter;
	}
	return 0;
}

int Player::GetLineNum()
{
	return m_LifeNum;
}

int Player::GetScore()
{
	return m_Score;
}

int Player::GetStageNum()
{
	return m_StageNum;
}

bool Player::IsGameStartWait()
{
	if (m_Mode == GAME_START_WAIT)
	{
		return true;
	}
	return false;
}
bool Player::IsDeath()
{
	if (m_Mode == DEATH)
	{
		return true;
	}
	return false;
}

bool Player::IsGameOver()
{
	if (m_Mode == GAME_OVER)
	{
		return true;
	}
	return false;
}

bool Player::IsGameRestart()
{
	if (m_Mode == RESTART)
	{
		return true;
	}
	return false;
}

bool Player::IsGameClear()
{
	if (m_Mode == CLEAR)
	{
		return true;
	}
	return false;
}

bool Player::IsChangedPowerUp()
{ 
	if (m_Mode == POWER_UP && m_ModeOld != POWER_UP)
	{
		return true;
	}
	return false;
}

bool Player::IsChangedNormal()
{
	if (m_Mode == NORMAL && m_ModeOld != NORMAL)
	{
		return true;
	}
	return false;
}

bool Player::IsEatAll()
{
	if (m_Mode == EAT_ALL)
	{
		return true;
	}
	return false;
}

int Player::GetMoveDir()
{
	int moveDir = DIR_NONE;
	if (CheckHitKey(KEY_INPUT_UP))
	{
		moveDir = DIR_UP;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		moveDir = DIR_RIGHT;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		moveDir = DIR_LEFT;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		moveDir = DIR_DOWN;
	}

	// 一回目のキーだけ横方向のキーを入れる
	if (m_IsFirstHit == false)
	{
		if (moveDir == DIR_RIGHT || moveDir == DIR_LEFT)
		{
			m_IsFirstHit = true;
		}
		else
		{
			moveDir = DIR_NONE;
		}
	}
	return moveDir;
}

void Player::UpdateMode()
{
	m_ModeOld = m_Mode;

	switch (m_Mode)
	{
		case GAME_START_WAIT:
		{
			m_ModeCounter = 0;
			m_Mode = NORMAL;
		}
		break;

		case NORMAL:
		{
			m_ModeCounter = 0;
		}
		break;

		case POWER_UP:
		{
			++m_ModeCounter;
			if (m_ModeCounter > POWERUP_TIME)
			{
				m_Mode = NORMAL;
				m_ModeCounter = 0;
			}
		}
		break;

		case EAT_ALL:
		{
			m_Move.x = 0;
			m_Move.y = 0;
			m_Speed = 0;

			++m_ModeCounter;
			if (m_ModeCounter > CLEAR_TIME)
			{
				m_Mode = CLEAR;
				m_StageNum++;
			}
		}
		break;

		case DEATH:
		{
			m_Move.x = 0;
			m_Move.y = 0;
			m_Speed = 0;

			++m_ModeCounter;
			if (m_ModeCounter > (DEATH_NUM*8)+30)
			{
				if (m_LifeNum > 0)
				{
					m_Mode = RESTART;
				}
				else
				{
					m_Mode = GAME_OVER;
				}
			}
		}
		break;
	}
}

void  Player::UpdateMove()
{
	m_Move.x = 0;
	m_Move.y = 0;

	if (m_MapData->HitCheck(m_Chip.x, m_Chip.y, m_Dir) == false)
	{
		switch (m_Dir)
		{
		case DIR_UP:
			m_Move.y -= m_Speed;
			break;
		case DIR_RIGHT:
			m_Move.x += m_Speed;
			break;
		case DIR_LEFT:
			m_Move.x -= m_Speed;
			break;
		case DIR_DOWN:
			m_Move.y += m_Speed;
			break;
		}
	}
}

void  Player::UpdatePos()
{
	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;

	// ワープ処理
	int warpY = 5;
	if (m_Chip.y == warpY) {
		if (m_Pos.x > (CHIP_SIZE_X - 1) * m_MapData->GetSize().x) {
			m_Pos.x = 0;
		}
		else if (m_Pos.x < -CHIP_SIZE_X) {
			m_Pos.x = (CHIP_SIZE_X - 1) * m_MapData->GetSize().x;
		}
	}
}
