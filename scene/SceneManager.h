#pragma once
#include "../common/Main.h"

class BaseScene;

//===============================
// �V�[���Ǘ��N���X
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
