#include "GameInitScene.h"
#include "../common/Singleton.h"
#include "../entity/GameEntityManager.h"
#include "GameScene.h"

//===============================
//ゲーム初期化シーンクラス
//==============================
void GameInitScene::Init()
{
	Singleton<GameEntityManager>::GetInstance().CreateEntity();
}

BaseScene* GameInitScene::Update()
{
	return new GameScene();
}

void GameInitScene::Draw()
{
}
