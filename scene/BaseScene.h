#pragma once

#include "../common/Main.h"

//=============================
// �V�[�����N���X
//===============================

class BaseScene
{
public:
	BaseScene():m_FrameCounter(0){}
	virtual ~BaseScene() {}

	virtual void Init() = 0;
	virtual BaseScene* Update() = 0;
	virtual void Draw() = 0;

protected:
	int m_FrameCounter;
};
