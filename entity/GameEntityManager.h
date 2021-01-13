#pragma once

#include "../common/Main.h"

//=============================
// �Q�[���G���e�B�e�B�Ǘ��N���X
//===============================
class Entity;

class GameEntityManager
{
private:
	enum EntityType
	{
		MAP,
		MONSTER_CHASE,
		MONSTER_AMBUSH,
		MONSTER_FICKLE,
		MONSTER_RANDOM,
		PLAYER,
		UI,

		ENTITY_MAX
	};

public:
	GameEntityManager() : m_Entity() {}
	~GameEntityManager();

	void CreateEntity();
	void StartGame();
	void RestartGame();
	void Update();
	void Draw();

	bool IsGameRestart();
	bool IsGameClear();
	bool IsGameOver();
private:
	Entity* m_Entity[ENTITY_MAX];
};
