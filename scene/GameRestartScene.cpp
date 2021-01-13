#include "GameRestartScene.h"
#include "../common/Singleton.h"
#include "../entity/GameEntityManager.h"

//===============================
//ゲームシーンクラス
//===============================
void GameRestartScene::Init()
{
	m_FrameCounter = 0;
	Singleton<GameEntityManager>::GetInstance().RestartGame();
}
