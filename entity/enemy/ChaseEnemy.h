#pragma once

#include "Enemy.h"

//=============================
// �ǐՃG�l�~�[�N���X
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

