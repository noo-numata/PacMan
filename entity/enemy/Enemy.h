#pragma once

#include "../MoveEntity.h"

//=============================
// エネミークラス
//===============================
class Map;
class Player;

class Enemy : public MoveEntity
{
protected:
	enum AnimPtn
	{
		NORMAL_NUM = 8,
		ENEMY_PTN_NUM = 2
	};

	enum EnemyType
	{
		CHASE_TYPE,	// 追いかけ
		AMBUSH_TYPE,	// 待ち伏せ
		FICKLE_TYPE,	// 気まぐれ
		RANDOM_TYPE,  // おとぼけ

		ENEMY_TYPE_MAX,
	};


public:
	Enemy(Map* mapData, Player* playerData) : m_TargetChip(),  m_DirCount(0), m_NormalImage(), m_WeakImage(), m_EyeImage(), m_MapData(mapData), m_PlayerData(playerData) {}
	virtual ~Enemy() {}

	void Update() override;
	void Draw() override;

protected:
	void  UpdateMode(void) override;
	void  UpdateMove(void) override;
	void  UpdatePos(void) override;

	bool IsHitPlayer();
	bool IsEnemyInNest();
	bool IsBackNestWall(int);
	int GetReverseDir(int);
	int  GetDir(bool);

protected:
	XY m_TargetChip;
	int m_DirCount;

	int m_NormalImage[4][2];
	int m_WeakImage[2][4][2];
	int m_EyeImage[4][2];

	Map* m_MapData;
	Player* m_PlayerData;
};


