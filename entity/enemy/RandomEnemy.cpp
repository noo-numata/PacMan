#include "RandomEnemy.h"
#include "../player/Player.h"
#include "../etc/Map.h"

//===============================
//おとぼけエネミークラス
//==============================
void RandomEnemy::SetGraphicData(int entityImage)
{
	// モンスター画像のセット
	for (int i = 0; i < NORMAL_NUM; i++) {
		m_NormalImage[(i / 2)][(i % 2)] = DerivationGraph(32 * i, 32 * RANDOM_TYPE, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
	}

	//　モンスターいじけ画像のセット
	for (int i = 0; i < NORMAL_NUM; i++) {
		m_WeakImage[0][(i / 2)][(i % 2)] = DerivationGraph(32 * (i % 2), 32 * 6, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
	}
	for (int i = 0; i < NORMAL_NUM; i++) {
		m_WeakImage[1][(i / 2)][(i % 2)] = DerivationGraph(32 * ((i % 2) + 2), 32 * 6, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
	}

	//　眼だけのモンスター画像のセット
	for (int i = 0; i < 4; i++) {
		m_EyeImage[i][0] = DerivationGraph(32 * 10, 32 * i, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
	}
}

void RandomEnemy::Init()
{
	StartGame();
}

void RandomEnemy::StartGame()
{
	m_Size.x = CHIP_SIZE_X;
	m_Size.y = CHIP_SIZE_Y;
	m_Pos.x = CHIP_SIZE_X * 9 + m_Size.x / 2;
	m_Pos.y = CHIP_SIZE_Y * 5 + m_Size.y / 2;
	m_Move.x = 0;
	m_Move.y = 0;
	m_Chip.x = m_Pos.x / CHIP_SIZE_X;
	m_Chip.y = m_Pos.y / CHIP_SIZE_Y;
	m_Speed = 1;
	m_AnimCount = 0;
	m_Dir = DIR_LEFT;
	m_TargetChip.x = m_Chip.x;
	m_TargetChip.y = m_Chip.y;
	m_Mode = WAIT;
	m_ModeOld = WAIT;
	m_ModeCounter = 0;
	m_DirCount = 0;
}

void RandomEnemy::RestartGame()
{
	StartGame();
}

int RandomEnemy::GetMoveDir()
{
	bool isCheckRevereDir = true;

	if (m_Mode == STOP) {
		// 止まったとき
		m_TargetChip.x = m_Chip.x;
		m_TargetChip.y = m_Chip.y;
	}
	else if (m_Mode == BACKNEST) {
		// 巣に戻るとき
		m_TargetChip.x = 10;
		m_TargetChip.y = 5;
	}
	else if (m_Mode == WEAK) {
		// いじけ状態のとき
		m_TargetChip.x = m_PlayerData->GetChip().x;
		m_TargetChip.y = m_PlayerData->GetChip().y;
	}
	else if (m_Mode == WAIT) {
		// 待ち状態のとき 
		m_TargetChip.x = 8;
		int subY = (m_DirCount > 1 + RANDOM_TYPE * 1) ? 1 : 0;
		m_TargetChip.y = 5 - subY;
		isCheckRevereDir = false;
	}
	else if (m_Mode == TERRIOTRY) {
		// 縄張り巡回状態のとき
		m_TargetChip.x = 15;
		m_TargetChip.y = 10;
	}
	else {
		// プレーヤー追跡状態のとき
		// GUZUTA_DIST_SQRよりプレーヤーとの距離が遠いときは
		// プレーヤーがターゲットそれ以外のときはランダム
		int chipLength = (m_Pos.x - m_PlayerData->GetPos().x) * (m_Pos.x - m_PlayerData->GetPos().x) + (m_Pos.y - m_PlayerData->GetPos().y) * (m_Pos.y - m_PlayerData->GetPos().y);
		if (chipLength > GUZUTA_DIST_SQR)
		{
			m_TargetChip.x = m_PlayerData->GetChip().x;
			m_TargetChip.y = m_PlayerData->GetChip().y;
		}
		else
		{
			m_TargetChip.x = GetRand(m_MapData->GetSize().x - 1);;
			m_TargetChip.y = GetRand(m_MapData->GetSize().y - 1);;
		}
	}
	return GetDir(isCheckRevereDir);

}


