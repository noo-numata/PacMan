#pragma once

#include "../common/Main.h"

//=============================
// �G���e�B�e�B�N���X
//===============================

class Entity
{
protected:
	enum Mode
	{
		NONE,

		// �v���[���[
		GAME_START_WAIT,	// �Q�[���X�^�[�g�҂����[�h
		NORMAL,		// �ʏ탂�[�h
		POWER_UP,	// �p���[�A�b�v���[�h
		DEATH,		// ���S���[�h
		RESTART,	// ���X�^�[�g
		GAME_OVER,	// �Q�[���I��
		EAT_ALL,	// �h�b�g��H�ׂ��Ƃ�
		CLEAR,		// �Q�[���N���A

		// �G�l�~�[
		WAIT,		// �ړ��҂����[�h
		TERRIOTRY,	// �p���[�G�T�ɑ҂��������[�h
		CHASE,		// �p�b�N�}���ǐՃ��[�h
		WEAK,		// ��胂�[�h
		BACKNEST,	// ���ɖ߂鎞�̃��[�h
		STOP,		// ��~���[�h

	};

public:
	Entity() :m_Size(), m_Mode(NONE), m_ModeOld(NONE), m_ModeCounter(0) {}
	virtual ~Entity() {}

	virtual void SetGraphicData(int) = 0; 
	virtual void Init() = 0;
	virtual void StartGame() = 0;
	virtual void RestartGame() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	XY& GetSize() { return m_Size; }

protected:
	XY m_Size;
	int	m_Mode;
	int	m_ModeOld;
	int m_ModeCounter;
};

