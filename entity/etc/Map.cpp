#include "Map.h"
#include "../player/Player.h"

//===============================
//マップクラス
//==============================
Map::~Map()
{
	for (int y = 0; y < m_Size.y; y++)
	{
		delete m_MapData[y];
	}
	delete m_MapData;

	for (int y = 0; y < m_Size.y; y++)
	{
		delete m_DotData[y];
	}
	delete m_DotData;
}

void Map::SetGraphicData(int entityImage)
{
	m_Size.x = MAP_SIZE_X;
	m_Size.y = MAP_SIZE_Y;

	m_MapData = new int* [m_Size.y];
	m_DotData = new int* [m_Size.y];

	for (int y = 0; y < m_Size.y; y++)
	{
		m_MapData[y] = new int[m_Size.x];
		m_DotData[y] = new int[m_Size.x];
	}

	m_DotImage = DerivationGraph(32 * 4, 32 * 6, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
	m_PowerUpImage = DerivationGraph(32 * 5, 32 * 6, CHIP_SIZE_X, CHIP_SIZE_Y, entityImage);
}

void Map::Init()
{
	StartGame();
}

void Map::StartGame()
{
	const int stageMapData[MAP_SIZE_Y][MAP_SIZE_X] =
	{
		{ 0x9,0x5,0x5,0x1,0x5,0x5,0x5,0x3,0x9,0x5,0x5,0x5,0x1,0x5,0x5,0x3 },
		{ 0xa,0xd,0x7,0xa,0xd,0x5,0x7,0xa,0xa,0xd,0x5,0x7,0xa,0xd,0x7,0xa },
		{ 0x8,0x5,0x5,0x0,0x1,0x5,0x5,0x4,0x4,0x5,0x5,0x1,0x0,0x5,0x5,0x2 },
		{ 0xc,0x5,0x5,0x2,0xc,0x5,0x5,0x3,0x9,0x5,0x5,0x6,0x8,0x5,0x5,0x6 },
		{ 0x5,0x5,0x7,0xa,0x9,0x5,0x5,0x4,0x4,0x5,0x5,0x3,0xa,0xd,0x5,0x5 },
		{ 0x5,0x5,0x5,0x0,0x2,0xd,0x5,0x4,0x4,0x5,0x7,0x8,0x0,0x5,0x5,0x5 },
		{ 0x5,0x5,0x7,0xa,0x8,0x5,0x5,0x5,0x5,0x5,0x5,0x2,0xa,0xd,0x5,0x5 },
		{ 0x9,0x5,0x5,0x0,0x4,0x5,0x5,0x3,0x9,0x5,0x5,0x4,0x0,0x5,0x5,0x3 },
		{ 0xc,0x5,0x3,0x8,0x1,0x5,0x5,0x4,0x4,0x5,0x5,0x1,0x2,0x9,0x5,0x6 },
		{ 0x9,0x5,0x4,0x6,0xc,0x5,0x5,0x3,0x9,0x5,0x5,0x6,0xc,0x4,0x5,0x3 },
		{ 0xc,0x5,0x5,0x5,0x5,0x5,0x5,0x4,0x4,0x5,0x5,0x5,0x5,0x5,0x5,0x6 },
	};

	const int stageDotData[MAP_SIZE_Y][MAP_SIZE_X] =
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 2,0,0,1,0,0,0,1,1,0,0,0,1,0,0,2 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0 },
		{ 1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1 },
		{ 0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	};

	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			m_MapData[y][x] = stageMapData[y][x];
			m_DotData[y][x] = stageDotData[y][x];
		}
	}

	RestartGame();
}

void Map::RestartGame()
{
	m_Mode = NORMAL;
	m_ModeOld = NORMAL;
	m_ModeCounter = 0;
}

void Map::Update()
{
	if (m_PlayerData != nullptr)
	{
		if (m_PlayerData->IsEatAll())
		{
			m_Mode = NONE;
		}

		if (m_Mode == NONE)
		{
			++m_ModeCounter;
		}
	}
}

void Map::Draw()
{
	int lineBaseColor	= 0x8080ff;
	int lineColor		= lineBaseColor;

	if (m_Mode == NONE)
	{
		int addColor = 0x020200;
		lineColor = lineBaseColor + addColor * m_ModeCounter;
		if (lineColor > 0xffffff)
		{
			lineColor = 0xffffff;
		}
	}

	// ラインの表示
	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			if (m_MapData[y][x] & BIT_UP)
			{
				DrawLine(x * CHIP_SIZE_X, y * CHIP_SIZE_Y + LINE_OFFSET, (x + 1) * CHIP_SIZE_X, y * CHIP_SIZE_Y + LINE_OFFSET, lineColor, 1);
			}
			if (m_MapData[y][x] & BIT_RIGHT)
			{
				DrawLine((x + 1) * CHIP_SIZE_X - LINE_OFFSET, y * CHIP_SIZE_Y, (x + 1) * CHIP_SIZE_X - LINE_OFFSET, (y + 1) * CHIP_SIZE_Y, lineColor, 1);
			}
			if (m_MapData[y][x] & BIT_DOWN)
			{
				DrawLine(x * CHIP_SIZE_X, (y + 1) * CHIP_SIZE_Y - LINE_OFFSET, (x + 1) * CHIP_SIZE_X, (y + 1) * CHIP_SIZE_Y - LINE_OFFSET, lineColor);
			}
			if (m_MapData[y][x] & BIT_LEFT)
			{
				DrawLine(x * CHIP_SIZE_X + LINE_OFFSET, y * CHIP_SIZE_Y, x * CHIP_SIZE_X + LINE_OFFSET, (y + 1) * CHIP_SIZE_Y, lineColor);
			}
		}
	}

	// ドットとパワー餌の表示
	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			if (m_DotData[y][x] == 1)
			{
				DrawGraph(x * CHIP_SIZE_X, y * CHIP_SIZE_Y, m_DotImage, true);
			}
			else if (m_DotData[y][x] == 2)
			{
				DrawGraph(x * CHIP_SIZE_X, y * CHIP_SIZE_Y, m_PowerUpImage, true);
			}
		}
	}
}

bool Map::HitCheck(int chipX, int chipY, int dir)
{
	int checkDirBit = (1 << dir);

	if (m_MapData[chipY][chipX] & checkDirBit)
	{
		return true;
	}
	return false;
}

bool Map::IsClear()
{
	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			if (m_DotData[y][x] == 1 || m_DotData[y][x] == 2)
			{
				return false;
			}
		}
	}
	return true;
}

bool Map::IsEatSomething(int chipX, int chipY)
{
	if (m_DotData[chipY][chipX] == 1 || m_DotData[chipY][chipX] == 2)
	{
		return true;
	}
	return false;
}

bool Map::IsEatPowerUpDot(int chipX, int chipY)
{
	if (m_DotData[chipY][chipX] == 2)
	{
		return true;
	}
	return false;
}

void Map::EatDat(int chipX, int chipY )
{
	m_DotData[chipY][chipX] = 0;
}
