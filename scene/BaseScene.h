#pragma once

#include "../common/Main.h"

//=============================
// シーン基底クラス
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
