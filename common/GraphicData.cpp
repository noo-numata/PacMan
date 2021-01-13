#include "GraphicData.h"
#include "../entity/etc/Map.h"
#include "../entity/etc/UIEntity.h"

//===============================
//画像データクラス
//==============================
void GraphicData::SetWindow()
{
	int screenSizeX = CHIP_SIZE_X * Map::MAP_SIZE_X + UIEntity::STATUS_DISP_SIZE_X;
	int screenSizeY = CHIP_SIZE_Y * Map::MAP_SIZE_Y;

	// ----- ｼｽﾃﾑ処理
	SetGraphMode(screenSizeX, screenSizeY, 16);	// ｽｸﾘｰﾝｻｲｽﾞ
	ChangeWindowMode(true);	// (true:Windowﾓｰﾄﾞ, false:ﾌﾙｽｸﾘｰﾝ)
	SetWindowText("PACK-MAN");	// Window名の設定
}

void GraphicData::SetScreen()
{
	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面に描画する設定
}

void GraphicData::LoadData()
{
	m_DataID[TITLE_DATA] = LoadGraph("image/title.png");
	m_DataID[ENTITY_DATA] = LoadGraph("image/pacnman.png");
}

int GraphicData::GetData(int data)
{
	if (data >= TITLE_DATA && data < DATA_MAX)
	{
		return m_DataID[data];
	}
	return 0;
}
