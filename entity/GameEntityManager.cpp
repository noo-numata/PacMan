#include "GameEntityManager.h"
#include "../common/Singleton.h"
#include "../common/GraphicData.h"
#include "../common/Sound.h"
#include "../entity/etc/Map.h"
#include "../entity/player/Player.h"
#include "../entity/enemy/ChaseEnemy.h"
#include "../entity/enemy/AmbushEnemy.h"
#include "../entity/enemy/FickleEnemy.h"
#include "../entity/enemy/RandomEnemy.h"
#include "../entity/etc/UIEntity.h"

//=============================
// ゲームエンティティ管理クラス
//===============================
GameEntityManager::~GameEntityManager()
{
	for (int i = 0; i < ENTITY_MAX; i++)
	{
		if (m_Entity[i] != nullptr)
		{
			delete m_Entity[i];
		}
	}
}

void GameEntityManager::CreateEntity()
{
	int entityImage = Singleton<GraphicData>::GetInstance().GetData(GraphicData::ENTITY_DATA);

	m_Entity[MAP] = new Map();
	Map* pMap = static_cast<Map*>(m_Entity[MAP]);

	m_Entity[PLAYER] = new Player(pMap);
	Player* pPlayer = static_cast<Player*>(m_Entity[PLAYER]);

	pMap->SetPlayer(pPlayer);

	m_Entity[MONSTER_CHASE] = new ChaseEnemy(pMap, pPlayer);
	m_Entity[MONSTER_AMBUSH] = new AmbushEnemy(pMap, pPlayer);

	ChaseEnemy* pChaseEnemy = static_cast<ChaseEnemy*>(m_Entity[MONSTER_CHASE]);
	m_Entity[MONSTER_FICKLE] = new FickleEnemy(pMap, pPlayer, pChaseEnemy);
	m_Entity[MONSTER_RANDOM] = new RandomEnemy(pMap, pPlayer);

	m_Entity[UI] = new UIEntity(pPlayer);

	for (int i = 0; i < ENTITY_MAX; i++)
	{
		if (m_Entity[i] != nullptr)
		{
			m_Entity[i]->SetGraphicData(entityImage);
			m_Entity[i]->Init();
		}
	}
}

void GameEntityManager::StartGame()
{
	Singleton<Sound>::GetInstance().PlayBGM(Sound::GAME_INTRO);

	for (int i = 0; i < ENTITY_MAX; i++)
	{
		if (m_Entity[i] != nullptr)
		{
			m_Entity[i]->StartGame();
		}
	}
}

void GameEntityManager::RestartGame()
{
	Singleton<Sound>::GetInstance().PlayBGM(Sound::GAME_INTRO);

	for (int i = 0; i < ENTITY_MAX; i++)
	{
		if (m_Entity[i] != nullptr)
		{
			m_Entity[i]->RestartGame();
		}
	}
}

void GameEntityManager::Update()
{
	for (int i = 0; i < ENTITY_MAX; i++)
	{
		if (m_Entity[i] != nullptr)
		{
			m_Entity[i]->Update();
		}
	}
}

void GameEntityManager::Draw()
{
	for (int i = 0; i < ENTITY_MAX; i++)
	{
		if (m_Entity[i] != nullptr)
		{
			m_Entity[i]->Draw();
		}
	}
}

bool GameEntityManager::IsGameRestart()
{
	Player* pPlayer = static_cast<Player*>(m_Entity[PLAYER]);
	return pPlayer->IsGameRestart();
}

bool GameEntityManager::IsGameClear()
{
	Player* pPlayer = static_cast<Player*>(m_Entity[PLAYER]);
	return pPlayer->IsGameClear();
}

bool GameEntityManager::IsGameOver()
{
	Player* pPlayer = static_cast<Player*>(m_Entity[PLAYER]);
	return pPlayer->IsGameOver();
}
