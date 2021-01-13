#pragma once

#include "Entity.h"

//=============================
// 移動エンティティクラス
//===============================

class MoveEntity : public Entity
{
public:
	enum DIR {
		DIR_NONE = -1,
		DIR_UP,
		DIR_RIGHT,
		DIR_DOWN,
		DIR_LEFT,
		DIR_MAX,
	};

	enum Time
	{
		POWERUP_FLASH_TIME = (3 * 60),
		POWERUP_TIME = (8 * 60)
	};

public:
	MoveEntity() : m_Pos(), m_Move(), m_Chip(), m_Speed(0), m_AnimCount(0), m_Dir(-1) {}
	virtual ~MoveEntity() {}

	XY& GetPos() { return m_Pos; }
	XY& GetChip() { return m_Chip; }
	int GetDir() { return m_Dir; }

protected:
	virtual int GetMoveDir() = 0;
	virtual void UpdateMode() = 0;
	virtual void UpdateMove() = 0;
	virtual void UpdatePos() = 0;

protected:
	XY m_Pos;
	XY m_Move;
	XY m_Chip;
	int m_Speed;
	int m_AnimCount;
	int m_Dir;
};

