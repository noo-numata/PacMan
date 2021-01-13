#include "ChaseEnemy.h"
#include "../player/Player.h"

//===============================
//�ǐՃG�l�~�[�N���X
//==============================
void ChaseEnemy::SetGraphicData(int entityImage)
{
	// �����X�^�[�摜�̃Z�b�g
	for (int i = 0; i < NORMAL_NUM; i++) {
		m_NormalImage[(i / 2)][(i % 2)] = DerivationGraph(32 * i, 32 * CHASE_TYPE, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
	}

	//�@�����X�^�[�������摜�̃Z�b�g
	for (int i = 0; i < NORMAL_NUM; i++) {
		m_WeakImage[0][(i / 2)][(i % 2)] = DerivationGraph(32 * (i % 2), 32 * 6, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
	}
	for (int i = 0; i < NORMAL_NUM; i++) {
		m_WeakImage[1][(i / 2)][(i % 2)] = DerivationGraph(32 * ((i % 2) + 2), 32 * 6, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
	}

	//�@�Ⴞ���̃����X�^�[�摜�̃Z�b�g
	for (int i = 0; i < 4; i++) {
		m_EyeImage[i][0] = DerivationGraph(32 * 10, 32 * i, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
	}
}

void ChaseEnemy::Init()
{
	StartGame();
}

void ChaseEnemy::StartGame()
{
	m_Size.x = CHIP_SIZE_X;
	m_Size.y = CHIP_SIZE_Y;
	m_Pos.x = CHIP_SIZE_X * 6 + m_Size.x / 2;
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

void ChaseEnemy::RestartGame()
{
	StartGame();
}

int ChaseEnemy::GetMoveDir()
{
	bool isCheckRevereDir = true;

	if (m_Mode == STOP) {
		// �~�܂����Ƃ�
		m_TargetChip.x = m_Chip.x;
		m_TargetChip.y = m_Chip.y;
	}
	else if (m_Mode == BACKNEST) {
		// ���ɖ߂�Ƃ�
		m_TargetChip.x = 5;
		m_TargetChip.y = 5;
	}
	else if (m_Mode == WEAK) {
		// ��������Ԃ̂Ƃ�
		m_TargetChip.x = m_PlayerData->GetChip().x;
		m_TargetChip.y = m_PlayerData->GetChip().y;
	}
	else if (m_Mode == WAIT) {
		// �҂���Ԃ̂Ƃ� 
		m_TargetChip.x = 7;
		int subY = (m_DirCount > 1 + CHASE_TYPE * 1) ? 1 : 0;
		m_TargetChip.y = 5 - subY;
		isCheckRevereDir = false;
	}
	else if (m_Mode == TERRIOTRY) {
		// �꒣�菄���Ԃ̂Ƃ�
		m_TargetChip.x = 0;
		m_TargetChip.y = 1;
	}
	else {
		// �v���[���[�ǐՏ�Ԃ̂Ƃ�
		m_TargetChip.x = m_PlayerData->GetChip().x;
		m_TargetChip.y = m_PlayerData->GetChip().y;
	}
	return GetDir(isCheckRevereDir);

}


