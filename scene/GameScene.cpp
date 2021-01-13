#include "GameScene.h"
#include "../common/Singleton.h"
#include "../entity/GameEntityManager.h"
#include "GameRestartScene.h"
#include "TitleScene.h"

//===============================
//ゲームシーンクラス
//===============================
void GameScene::Init()
{
	m_FrameCounter = 0;
	Singleton<GameEntityManager>::GetInstance().StartGame();
}

BaseScene* GameScene::Update()
{
	m_FrameCounter++;
	if (m_FrameCounter > GAME_START_WAIT_TIME)
	{
		Singleton<GameEntityManager>::GetInstance().Update();
	}

	if (Singleton<GameEntityManager>::GetInstance().IsGameRestart())
	{
		return new GameRestartScene();
	}
	else if (Singleton<GameEntityManager>::GetInstance().IsGameClear())
	{
		return new GameScene();
	}
	else if (Singleton<GameEntityManager>::GetInstance().IsGameOver())
	{
		return new TitleScene();
	}

	return this;
}

void GameScene::Draw()
{
	Singleton<GameEntityManager>::GetInstance().Draw();
}
