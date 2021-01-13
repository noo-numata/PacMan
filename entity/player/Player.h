#pragma once

#include "../MoveEntity.h"

//=============================
// プレーヤークラス
//===============================
class Map;

class Player : public MoveEntity
{
private:
	enum AnimPtn
	{
		NORMAL_NUM = 8,
		DEATH_NUM = 11,
		PLAYER_PTN_NUM = 2
	};

	enum Life
	{
		LIFE_NUM = 3
	};

	enum Time
	{
		CLEAR_TIME = (2 * 60)
	};

public:
	Player(Map* mapData) : m_IsFirstHit(false), m_NormalImage(), m_StopImage(0), m_DeathImage(), m_MapData(mapData), m_LifeNum(0), m_Score(0), m_StageNum(0){}
	~Player() {}
	 
	void SetGraphicData(int) override;
	void Init() override;
	void StartGame() override;
	void RestartGame() override;
	void Update() override;
	void Draw() override;

	void Death();
	void AddEatScore();
	int GetPowerUpCount();
	int GetLineNum();
	int GetScore();
	int GetStageNum();
	bool IsGameStartWait();
	bool IsGameRestart();
	bool IsGameClear();
	bool IsGameOver();
	bool IsDeath();
	bool IsChangedPowerUp();
	bool IsChangedNormal();
	bool IsEatAll();

protected:
	int GetMoveDir() override;
	void  UpdateMode(void) override;
	void  UpdateMove(void) override;
	void  UpdatePos(void) override;

protected:
	bool	m_IsFirstHit;

	int m_NormalImage[4][2];
	int m_StopImage;
	int m_DeathImage[DEATH_NUM];

	Map* m_MapData;

	int m_LifeNum;
	int m_Score;
	int m_StageNum;
};
