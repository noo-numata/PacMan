#pragma once

#include "Sound.h"

//=============================
// サウンドクラス
//===============================

class Sound
{
public:
	enum BGM
	{
		GAME_INTRO,
		BGM_MAX
	};
	enum SE
	{
		EAT_DOT,
		EAT_GHOST,
		DEATH,
		SE_MAX
	};

public:
	Sound() : m_BGM(), m_SE() {};
	~Sound() {};

	void Init();
	void LoadData();
	void PlayBGM(int bgmType);
	void PlaySE(int seType);

private:
	int m_BGM[BGM_MAX];
	int m_SE[SE_MAX];
};

