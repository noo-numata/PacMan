#pragma once

#include "../common/Main.h"

//=============================
// エンティティクラス
//===============================

class Entity
{
protected:
	enum Mode
	{
		NONE,

		// プレーヤー
		GAME_START_WAIT,	// ゲームスタート待ちモード
		NORMAL,		// 通常モード
		POWER_UP,	// パワーアップモード
		DEATH,		// 死亡モード
		RESTART,	// リスタート
		GAME_OVER,	// ゲーム終了
		EAT_ALL,	// ドットを食べたとき
		CLEAR,		// ゲームクリア

		// エネミー
		WAIT,		// 移動待ちモード
		TERRIOTRY,	// パワーエサに待ち伏せモード
		CHASE,		// パックマン追跡モード
		WEAK,		// 弱りモード
		BACKNEST,	// 巣に戻る時のモード
		STOP,		// 停止モード

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

