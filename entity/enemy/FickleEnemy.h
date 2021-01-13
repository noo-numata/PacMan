#pragma once

#include "Enemy.h"

//=============================
// 気まぐれエネミークラス
//===============================
class Map;
class Player;
class ChaseEnemy;

class FickleEnemy : public Enemy
{
public:
	FickleEnemy(Map* mapData, Player* playerData, ChaseEnemy* chaseEnemy) : Enemy(mapData, playerData), m_ChaseEnemyData(chaseEnemy) {}
	virtual ~FickleEnemy() {}

	void SetGraphicData(int) override;
	void Init() override;
	void StartGame() override;
	void RestartGame() override;

protected:
	int GetMoveDir() override;
	
	ChaseEnemy* m_ChaseEnemyData;
};
