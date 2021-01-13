#include "../common/Main.h"
#include "BaseScene.h"
#include "SceneManager.h"

//===============================
//シーン管理クラス
//==============================

SceneManger::SceneManger():
m_pScene(nullptr)
{
}

SceneManger::~SceneManger()
{
	if (m_pScene!= nullptr)
	{
		delete m_pScene;
	}
}

void SceneManger::SetStartScene(BaseScene* pScene)
{
	if (m_pScene == nullptr)
	{
		m_pScene = pScene;
		m_pScene->Init();
	}
}

void SceneManger::Update()
{
	if (m_pScene != nullptr)
	{
		BaseScene* pCurrentScene = m_pScene->Update();
		if (pCurrentScene != m_pScene)
		{
			delete m_pScene;
			m_pScene = pCurrentScene;
			m_pScene->Init();
		}
	}
}

void SceneManger::Draw()
{
	if (m_pScene != nullptr)
	{
		ClsDrawScreen();

		m_pScene->Draw();

		ScreenFlip();
	}
}

