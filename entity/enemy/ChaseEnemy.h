#pragma once

#include "Enemy.h"

//=============================
// 追跡エネミークラス
//===============================
class Map;
class Player;

class ChaseEnemy : public Enemy
{
public:
	ChaseEnemy(Map* mapData, Player* playerData) : Enemy(mapData, playerData) {}
	virtual ~ChaseEnemy() {}

	void SetGraphicData(int) override;
	void Init() override;
	void StartGame() override;
	void RestartGame() override;

protected:
	int GetMoveDir() override;
};

