#pragma once
#include "../common/Main.h"

class BaseScene;

//===============================
// シーン管理クラス
//===============================

class SceneManger
{
public:
	SceneManger();
	~SceneManger();

public:
	void SetStartScene(BaseScene* pScene);
	void Update();
	void Draw();

private:
	BaseScene* m_pScene;
};
