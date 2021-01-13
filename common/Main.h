#pragma once

#include "Dxlib.h"	// DxLibﾗｲﾌﾞﾗﾘを使用する

#define CHIP_SIZE_X 32
#define CHIP_SIZE_Y 32

//#define TERITORY_TIME (5*60)
//#define ClEAR_TIME (2*60)

// 座標用の構造体
struct XY {

	XY():x(0),y(0){}
	~XY() {};

	int x;
	int y;
};

