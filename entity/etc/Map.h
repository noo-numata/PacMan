#pragma once

#include "../Entity.h"

//=============================
// マップクラス
//===============================
class Player;

class Map : public Entity
{
private:
	enum Offset
	{
		LINE_OFFSET = 2,
		DOT_OFFSET = 14
	};

	enum BitData
	{
		BIT_UP = (1 << 0),
		BIT_RIGHT = (1 << 1),
		BIT_DOWN = (1 << 2),
		BIT_LEFT = (1 << 3)
	};

public:
	enum Size
	{
		MAP_SIZE_X = 16,
		MAP_SIZE_Y = 11
	};

public:
	Map() : m_MapData(nullptr), m_DotData(nullptr), m_DotImage(0), m_PowerUpImage(0), m_PlayerData(nullptr){}
	~Map();

	void SetGraphicData(int) override;
	void Init() override;
	void StartGame() override;
	void RestartGame();
	void Update() override;
	void Draw() override;

	bool HitCheck(int, int, int);
	bool IsClear();

	XY& GetSize() { return m_Size; }
	bool IsEatSomething(int chipX, int chipY);
	bool IsEatPowerUpDot(int chipX, int chipY);
	void EatDat(int, int);
	void SetPlayer(Player* pPlayer) { m_PlayerData = pPlayer; }

private:
	int** m_MapData;
	int** m_DotData;
	int m_DotImage;
	int m_PowerUpImage;

	Player* m_PlayerData;
};
