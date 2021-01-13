#pragma once

#include "Enemy.h"

//=============================
// おとぼけエネミークラス
//===============================
class Map;
class Player;

class RandomEnemy : public Enemy
{
protected:
	enum Dist
	{
		GUZUTA_DIST_SQR = (130 * 130)
	};

public:
	RandomEnemy(Map* mapData, Player* playerData) : Enemy(mapData, playerData) {}
	virtual ~RandomEnemy() {}

	void SetGraphicData(int) override;
	void Init() override;
	void StartGame() override;
	void RestartGame() override;

protected:
	int GetMoveDir() override;
};
