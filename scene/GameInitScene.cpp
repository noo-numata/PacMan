#include "GameInitScene.h"
#include "../common/Singleton.h"
#include "../entity/GameEntityManager.h"
#include "GameScene.h"

//===============================
//�Q�[���������V�[���N���X
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
