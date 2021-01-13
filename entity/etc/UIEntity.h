#pragma once

#include "../Entity.h"

//=============================
// UIƒNƒ‰ƒX
//===============================
class Player;

class UIEntity : public Entity
{
public:
	enum Size
	{
		STATUS_DISP_SIZE_X = 100
	};

public:
	UIEntity(Player* pPlayer) : m_ReadyImage(0), m_GameOverImage(0), m_PlayerData(pPlayer) {}
	virtual ~UIEntity() {}

	void SetGraphicData(int) override;
	void Init() override;
	void StartGame() override;
	void RestartGame();
	void Update() override;
	void Draw() override;

private:
	void StratWaitDraw();
	void GameOverDraw();
	void StatusDraw();

private:
	int m_ReadyImage;
	int m_GameOverImage;

	Player* m_PlayerData;
};

