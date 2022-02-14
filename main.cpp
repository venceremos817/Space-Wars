//main.cpp

///////////////////////////////////////////////////////////
//	HEW課題
//縦スクロールSTG
//
//
//
//
//
//
//
//
//
//
///////////////////////////////////////////////////////////

//===== インクルード部 =====
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include <mmsystem.h>
//#pragma comment (lib, "winmm.lib")
#include"main.h"
#include"GameManager.h"
#include"Console.h"
#include"Player.h"
#include"PlayerShot.h"
#include"Enemy.h"
#include"EnemyShot.h"
#include"Score.h"
#include"Item.h"
#include"BackGround.h"
#include"Effect.h"
#include"Title.h"
#include"Boss.h"
#include"Ranking.h"
#include"Result.h"
#include"Sound.h"
#include"UI.h"

//===== 定数定義 =====
#define MAIN_BGM	"sound/bgm_maoudamashii_cyber01.mp3"


//===== プロトタイプ宣言 =====
void Update(void);
void Draw(void);
void UnInitALL(void);
void InitFPS(void);
void DispFPS(void);
void UnInitFps(void);

//===== グローバル宣言 =====
int g_nCountFps;	//FPS用カウンタ
DRAW_OBJECT FPS;
MODE g_mode;
int g_nMainBGM;

int main(void)
{
	//----- 変数宣言 -----
	int nCurrentTime;	//現在時間
	int nExecLastTime;	//前回実行時間
	int nFPSLastTime;	//前回FPS計測時間
	int nFrameCount;	//フレーム処理回数

	//----- 前処理 -----
	timeBeginPeriod(1);		//分解能を1msに設定


	//----- 初期化処理 -----
	Init();
//	InitPlayer();
	nFPSLastTime = nExecLastTime = nCurrentTime = timeGetTime();	//時間を取得
	nFrameCount = 0;
	ShowConsoleCursor(false);
	SetMode(MODE_TITLE);

	//----- BGM -----
	g_nMainBGM = CreateSound(MAIN_BGM);
	if (g_nMainBGM == INVALID_HANDLE)
	{
		printf("failed create sound.");
		getchar();
	}
	SetVolume(g_nMainBGM, 0.5f);
	PlaySound(g_nMainBGM, true);


	do
	{
		//----- 更新処理 -----
		nCurrentTime = timeGetTime();
		//FPS計測
		if (nCurrentTime - nFPSLastTime >= 500)	//500ms毎に判定
		{
			g_nCountFps = nFrameCount * 1000 / (nCurrentTime - nFPSLastTime);
			nFPSLastTime = nCurrentTime;
			nFrameCount = 0;
		}

		if (nCurrentTime - nExecLastTime >= FRAME_RATE)
		{
			nExecLastTime = nCurrentTime;

			//----- 更新処理 -----
			Update();

			//----- 描画処理 -----
			Draw();


			if (GetKeyState(VK_ESCAPE) & 0x80)
				SetMode(END_GAME);

			nFrameCount++;
		}
	} while (!(g_mode == END_GAME));



	UnInitALL();
	ShowConsoleCursor(true);
	timeEndPeriod(1);
	rewind(stdin);
	return 0;
}



void Init(void)
{
	InitConsole();
	InitSound();
	switch (g_mode)
	{
	case MODE_TITLE:
		InitPlayer();
		InitPlayerShot();
		InitTitle();
		InitEffect();
		InitBackGround();

		break;

	case MODE_GAME:
		InitFPS();
		InitEnemy();
		InitEnemyShot();
		InitScore();
		InitItem();
		InitUI();
		//	InitBackGround();
		break;

	case MODE_RANKING:
		InitRanking();
		break;

	case MODE_RESULT:
		InitResult();

		break;

	default:
		break;
	}
}

void Update(void)
{
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdTitle();
		UpdPlayer();
		UpdPlayerShot();
		UpdEffect();
		UpdBackGround();

		break;

	case MODE_GAME:
		UpdPlayer();
		UpdEnemy();
		UpdPlayerShot();
		UpdEnemyShot();
		UpdItem();
		UpdBackGround();
		UpdEffect();
		break;

	case MODE_RANKING:
		UpdRanking();
		UpdBackGround();
		break;

	case MODE_RESULT:
		UpdBackGround();
		UpdResult();
		break;

	default:
		break;
	}
}

void Draw(void)
{
	switch (g_mode)
	{
	case MODE_TITLE:
		DrawBackGround();
		DrawPlayerShotToBuf();
		DrawPlayerToBuf();
		DrawTitle();
		DrawEffect();

		
		DrawBuf();
		break;

	case MODE_GAME:
		DrawBackGround();
		DrawUI();
		DrawItem();
		DrawScore();
		DrawPlayerShotToBuf();
		DrawPlayerToBuf();
		DrawEnemyToBuf();
		DrawEnemyShotToBuf();
		DrawEffect();
		DispFPS();
		DrawBuf();
		break;

	case MODE_RANKING:
		DrawBackGround();
		DrawRanking();
		DrawBuf();
		break;

	case MODE_RESULT:
		DrawBackGround();
		DrawResult();
		DrawBuf();

		break;

	default:
		break;
	}
}

void UnInit(void)
{
	switch (g_mode)
	{
	case MODE_TITLE:
		UnInitTitle();
		break;

	case MODE_GAME:
		//UniInitPlayer();
		//UnInitPlayerShot();
		//UnInitEnemy();
		//UnInitEnemyShot();
		//UnInitItem();

		break;

	case MODE_RANKING:
	//	UnInitTitle();
		break;

	case MODE_RESULT:
		UnInitBackGround();
		UnInitEffect();
		UnInitScore();
		break;

	default:
		break;
	}
}

void UnInitALL(void)
{
	UniInitPlayer();
	UnInitFps();
	UnInitPlayerShot();
	UnInitEnemy();
	UnInitItem();
	UnInitBackGround();
	UnInitScore();
	UnInitEffect();
	UnInitBoss();
	UninitSound();
	UnInitUI();
	UnInitRanking();
}



void InitFPS(void)
{
	char szFPS[10] = { "\0" };
	int i;
	sprintf_s(szFPS, "FPS:%02d", g_nCountFps);
	InitDrawObject(&FPS, 1, strlen(szFPS));

	FPS.fCurPosX = 3;
	FPS.fCurPosY = 1;
	for (i = 0; szFPS[i] != '\0'; i++)
		FPS.pCell[i].Attributes = 0 * 16 + 7;
}




void DispFPS(void)
{
	char szFPS[10] = { "\0" };
	sprintf_s(szFPS, "FPS:%02d", g_nCountFps);
	SetObjectChar(&FPS, szFPS);

	AddObjectToBuf(&FPS);
}

void UnInitFps()
{
//	UnInitDrawObject(&FPS);
}

void SetMode(MODE mode)
{
	g_mode = mode;
}

MODE GetMode(void)
{
	return g_mode;
}