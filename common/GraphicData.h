#pragma once

#include "Main.h"

//=============================
// �摜�f�[�^�N���X
//===============================

class GraphicData
{
public:
	enum Data
	{
		TITLE_DATA,
		ENTITY_DATA,

		DATA_MAX
	};

public:
	GraphicData() : m_DataID() {}
	~GraphicData() {}

	void SetWindow();
	void SetScreen();

	void LoadData();
	int GetData(int data);

private:
	int m_DataID[DATA_MAX];
};
