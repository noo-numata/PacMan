#pragma once

#include "Enemy.h"

//=============================
// �҂������G�l�~�[�N���X
//===============================
class Map;
class Player;

class AmbushEnemy : public Enemy
{
public:
	AmbushEnemy(Map* mapData, Player* playerData) : Enemy(mapData, playerData) {}
	virtual ~AmbushEnemy() {}

	void SetGraphicData(int) override;
	void Init() override;
	void StartGame() override;
	void RestartGame() override;

protected:
	int GetMoveDir() override;
};

