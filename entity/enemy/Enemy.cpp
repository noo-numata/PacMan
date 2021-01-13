#include "Enemy.h"
#include "../etc/Map.h"
#include "../player/Player.h"
#include "../../common/Singleton.h"
#include "../../common/Sound.h"

//===============================
//エネミークラス
//==============================
void Enemy::Update()
{
	m_Chip.x = m_Pos.x / CHIP_SIZE_X;
	m_Chip.y = m_Pos.y / CHIP_SIZE_Y;

	// モードの更新
	UpdateMode();

	if ((m_Pos.x - m_Size.x / 2) % CHIP_SIZE_X == 0 &&
		(m_Pos.y - m_Size.y / 2) % CHIP_SIZE_Y == 0) 
	{
		m_Dir = GetMoveDir();

		UpdateMove();
	}
	UpdatePos();
}

void Enemy::Draw()
{
	if (m_Mode != NONE)
	{
		m_AnimCount++;
		int image = 0;
		if (m_Mode == BACKNEST)
		{
			image = m_EyeImage[m_Dir][0];
		}
		else if (m_Mode == WEAK)
		{
			// いじけ状態のとき
			int tmp = 0;
			if (m_PlayerData->GetPowerUpCount() > POWERUP_FLASH_TIME) {
				tmp = (m_PlayerData->GetPowerUpCount() / 10) % 2;
			}
			image = m_WeakImage[tmp][m_Dir][(m_AnimCount / 20) % ENEMY_PTN_NUM];
		}
		else {
			// 通常状態のとき
			image = m_NormalImage[m_Dir][(m_AnimCount / 20) % ENEMY_PTN_NUM];
		}
		DrawRotaGraph(m_Pos.x, m_Pos.y, 1.0f, 0.0f, image, true, false);
	}
}

void Enemy::UpdateMode()
{
	m_ModeOld = m_Mode;

	if (m_PlayerData->IsEatAll())
	{
		m_Mode = NONE;
	}

	switch (m_Mode)
	{
		case WAIT:
		{
			if (m_PlayerData->IsDeath())
			{
				m_Mode = STOP;
			}
			else if (IsEnemyInNest() == false)
			{
				m_Mode = CHASE;
			}
		}
		break;

		case CHASE:
		{
			if (m_PlayerData->IsDeath())
			{
				m_Mode = STOP;
			}
			else if (m_PlayerData->IsChangedPowerUp())
			{
				m_Mode = WEAK;
				m_ModeCounter = 0;
			}
			else if (IsHitPlayer())
			{
				m_PlayerData->Death();
				m_Mode = STOP;
				m_ModeCounter = 0;
			}
		}
		break;

		case WEAK:
		{
			if (m_PlayerData->IsChangedNormal()) {
				m_Mode = CHASE;
				m_ModeCounter = 0;
			}
			else if (IsHitPlayer()) {
				m_Mode = BACKNEST;
				m_ModeCounter = 0;
				m_Speed = 4;
				m_PlayerData->AddEatScore();
				Singleton<Sound>::GetInstance().PlaySE(Sound::EAT_GHOST);
			}
		}
		break;

		case BACKNEST:
		{
			if (IsEnemyInNest()) {
				Init();
			}
		}
		break;

		case STOP:
		case NONE: 
		{
			m_Move.x = 0;
			m_Move.y = 0;
			m_Speed = 0;
		}
		break;

	}
}

void  Enemy::UpdateMove(void)
{
	m_Move.x = 0;
	m_Move.y = 0;

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

void  Enemy::UpdatePos(void)
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

bool Enemy::IsHitPlayer()
{
	if (m_PlayerData->IsDeath() == false)
	{
		int playerSizeX = static_cast<int>(static_cast<float>(m_PlayerData->GetSize().x) * 0.2f);
		int playerSizeY = static_cast<int>(static_cast<float>(m_PlayerData->GetSize().y) * 0.2f);

		int enemySizeX = static_cast<int>(static_cast<float>(m_Size.x) * 0.4f);
		int enemySizeY = static_cast<int>(static_cast<float>(m_Size.y) * 0.4f);

		if (m_PlayerData->GetPos().x - playerSizeX < m_Pos.x + enemySizeX &&
			m_PlayerData->GetPos().x + playerSizeX > m_Pos.x - enemySizeX &&
			m_PlayerData->GetPos().y - playerSizeY < m_Pos.y + enemySizeY &&
			m_PlayerData->GetPos().y + playerSizeY > m_Pos.y - enemySizeY)
		{
			return true;
		}
	}
	return false;
}

bool Enemy::IsEnemyInNest()
{
	if (m_Chip.y == 5 &&
		(m_Chip.x == 5 || m_Chip.x == 6 || m_Chip.x == 7 || m_Chip.x == 8 || m_Chip.x == 9 || m_Chip.x == 10)) {
		return true;
	}
	return false;
}

bool Enemy::IsBackNestWall(int dir)
{
	if (m_Mode == BACKNEST && dir == DIR_DOWN)
	{
		if (m_Chip.y == 4 && (m_Chip.x == 7 || m_Chip.x == 8))
		{
			return true;
		}
	}
	return false;
}

int Enemy::GetReverseDir(int dir)
{
	int reverseDir[DIR_MAX] = { DIR_DOWN, DIR_LEFT, DIR_UP, DIR_RIGHT };
	return reverseDir[dir];
}

int  Enemy::GetDir(bool isCheckRevereDir)
{
	m_DirCount++;

	int retdir = DIR_UP;

	int topScore;
	if (m_Mode == WEAK)
	{
		topScore = 0;
	}
	else {
		topScore = (m_MapData->GetSize().x * CHIP_SIZE_X) * (m_MapData->GetSize().x * CHIP_SIZE_X) + (m_MapData->GetSize().y * CHIP_SIZE_Y) * (m_MapData->GetSize().y * CHIP_SIZE_Y);
	}

	int reverseDir = GetReverseDir(m_Dir);

	for (int dir = 0; dir < DIR_MAX; dir++) {
		if (isCheckRevereDir && reverseDir == dir) {
			continue;
		}

		bool isBackNest = IsBackNestWall(dir);
		if (m_MapData->HitCheck(m_Chip.x, m_Chip.y, dir) == false || isBackNest) {
			int checkPosX = m_Pos.x;
			int checkPosY = m_Pos.y;

			switch (dir)
			{
			case DIR_UP:
				checkPosY -= CHIP_SIZE_Y;
				break;
			case DIR_RIGHT:
				checkPosX += CHIP_SIZE_X;
				break;
			case DIR_LEFT:
				checkPosX -= CHIP_SIZE_X;
				break;
			case DIR_DOWN:
				checkPosY += CHIP_SIZE_Y;
				break;
			}

			int score = (checkPosY - m_TargetChip.y * CHIP_SIZE_Y) * (checkPosY - m_TargetChip.y * CHIP_SIZE_Y) + (checkPosX - m_TargetChip.x * CHIP_SIZE_X) * (checkPosX - m_TargetChip.x * CHIP_SIZE_X);
			if (isBackNest)
			{
				score = 0;
			}

			if (m_Mode == WEAK) 
			{
				if (score > topScore) {
					topScore = score;
					retdir = (DIR)dir;
				}
			}
			else {
				if (score <= topScore) {
					topScore = score;
					retdir = (DIR)dir;
				}
			}
		}
	}
	return retdir;
}
