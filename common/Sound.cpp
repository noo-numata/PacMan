#include "Main.h"
#include "Sound.h"

//===============================
//サウンドクラス
//==============================
void  Sound::Init()
{
	for (int i = 0; i < BGM_MAX; i++) { m_BGM[i] = 0; }
	for (int i = 0; i < SE_MAX; i++) { m_SE[i] = 0; }
}

void Sound::LoadData()
{
	m_BGM[GAME_INTRO] = LoadSoundMem("sound/pacman_beginning.wav");

	m_SE[EAT_DOT] = LoadSoundMem("sound/pacman_chomp.wav");
	m_SE[EAT_GHOST] = LoadSoundMem("sound/pacman_eatghost.wav");
	m_SE[DEATH] = LoadSoundMem("sound/pacman_death.wav");
}

void Sound::PlayBGM(int bgmType)
{
	PlaySoundMem(m_BGM[bgmType], DX_PLAYTYPE_BACK);
}

void Sound::PlaySE(int seType)
{
	PlaySoundMem(m_SE[seType], DX_PLAYTYPE_BACK);
}
