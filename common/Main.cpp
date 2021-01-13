//===============================
//　メイン
//==============================
//
#include "Main.h"
#include "Singleton.h"
#include "../scene/SceneManager.h"
#include "Sound.h"
#include "GraphicData.h"
#include "../scene/TitleScene.h"

// ---------- 初期化関数
// ========== 最初の初期化
int SystemInit(void)
{
	// ----- ｼｽﾃﾑ処理
	Singleton<GraphicData>::GetInstance().SetWindow();

	// DxLib初期化
	if (DxLib_Init() == -1) {
		// 初期化失敗の場合
		return -1;
	}

	Singleton<GraphicData>::GetInstance().SetScreen();

	return 1;	// SystemInit関数の終了
}

// ---------- WinMain関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// システム初期化
	SystemInit();

	// データのロード
	Singleton<Sound>::GetInstance().LoadData();
	Singleton<GraphicData>::GetInstance().LoadData();

	// 開始シーンの設定
	Singleton <SceneManger>::GetInstance().SetStartScene(new TitleScene());

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Singleton <SceneManger>::GetInstance().Update();
		Singleton <SceneManger>::GetInstance().Draw();
	}

	return 0;
}


