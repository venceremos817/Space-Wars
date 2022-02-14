//Title.cpp

//===== インクルード部 =====
#include"main.h"
#include"Title.h"
#include"Console.h"
#include"Bmp.h"
#include"PlayerShot.h"
#include"GameManager.h"
#include"Effect.h"
#include"Enemy.h"
#include<math.h>

//===== 定数定義 =====
#define TITLE_PIC	"BMP/title.bmp"
#define PLAY_PIC	"BMP/play.bmp"
#define RANKING_PIC	"BMP/ranking.bmp"
#define	EXIT_PIC	"BMP/exit.bmp"
#define ENDLESS_PIC	"BMP/endless.bmp"
#define MAX_HP			(100)

typedef enum
{
	PLAY,
	RANKING,
	EXIT,
	ENDLESS,
	MAX_MEMU
}TITLE_MEMU;

//===== 構造体宣言 =====
typedef struct
{
	//float fX;
	//float fY;
	//int nWidth;
	//int nHeight;
	int nHp;
	DRAW_OBJECT droPic;
}MENU_OBJECT;


//===== プロトタイプ宣言 =====
void ChkPShotAndMenu(void);


//===== グローバル変数 =====
int g_cursor;
DRAW_OBJECT g_DrObjTitle;
MENU_OBJECT g_Menu[MAX_MEMU];

void InitTitle(void)
{
	int i;
	char TitleFilename[] = { TITLE_PIC };
	char MenuFilename[MAX_MEMU][20] = { PLAY_PIC,RANKING_PIC,EXIT_PIC,ENDLESS_PIC };

	ReadBmp(TitleFilename, &g_DrObjTitle);
	g_DrObjTitle.fCurPosX = (LIMIT_LEFT + LIMIT_RIGHT) / 2;
	g_DrObjTitle.fCurPosY = g_DrObjTitle.nHeight / 2 + 10;


	for (i = 0; i < MAX_MEMU; i++)
	{
		ReadBmp(MenuFilename[i], &g_Menu[i].droPic);
		g_Menu[i].droPic.bExist = true;
		g_Menu[i].nHp = MAX_HP;
	}
	g_Menu[PLAY].droPic.fCurPosX = (LIMIT_LEFT + LIMIT_RIGHT) / 2;
	g_Menu[PLAY].droPic.fCurPosY = (LIMIT_TOP + LIMIT_BOTTOM) / 2 + 20;

	g_Menu[RANKING].droPic.fCurPosX = (LIMIT_LEFT + g_Menu[RANKING].droPic.nWidth / 2 + 10);
	g_Menu[RANKING].droPic.fCurPosY = (LIMIT_TOP + LIMIT_BOTTOM) / 2 + 10;

	g_Menu[EXIT].droPic.fCurPosX = (LIMIT_RIGHT - g_Menu[EXIT].droPic.nWidth);
	g_Menu[EXIT].droPic.fCurPosY = (LIMIT_TOP + LIMIT_BOTTOM) / 2 + 10;

	g_Menu[ENDLESS].droPic.fCurPosX = LIMIT_RIGHT- g_Menu[ENDLESS].droPic.nWidth/1.5;
	g_Menu[ENDLESS].droPic.fCurPosY = g_Menu[ENDLESS].droPic.nHeight/1.5;

}

void UpdTitle(void)
{
	ChkPShotAndMenu();

	if (g_Menu[PLAY].nHp < 0)
	{
		UnInit();
		SetPlayMode(NORMAL_MODE);
		SetMode(MODE_GAME);
		Init();
	}

	if (g_Menu[RANKING].nHp < 0)
	{
		UnInit();
		SetMode(MODE_RANKING);
		Init();
	}

	if (g_Menu[EXIT].nHp < 0)
	{
		UnInit();
		SetMode(END_GAME);
	}
	if (g_Menu[ENDLESS].nHp < 0)
	{
		UnInit();
		SetPlayMode(ENDLESS_MODE);
		SetMode(MODE_GAME);
		Init();
	}
}

void DrawTitle(void)
{
	int i;

	AddObjectToBuf(&g_DrObjTitle);
	for (i = 0; i < MAX_MEMU; i++)
	{
		if(g_Menu[i].droPic.bExist==true)
		AddObjectToBuf(&g_Menu[i].droPic);
	}
	//NoChangePosAddObjectToBuf(&g_DrobjTitle);
}

void ChkPShotAndMenu(void)
{
	int i, j;
	float fDistanceX, fDistanceY;
	int nSumWidth, nSumHeight;
	SHOT *pShot = GetShotLine1();


	for (i = 0; i < PLAYER_MAX_SHOT_NUM; i++)
	{
		if (pShot[i].bExist == false)	continue;
		for (j = 0; j < MAX_MEMU; j++)
		{
			if (g_Menu[j].nHp < MAX_HP)
				g_Menu[j].nHp++;

			//----- 矩形同士で当たり判定をとる -----
			fDistanceY = fabs(pShot[i].fY - g_Menu[j].droPic.fCurPosY);
			nSumHeight = (pShot[i].nHeight + g_Menu[j].droPic.nHeight) / 2;
			if (fDistanceY > nSumHeight)	continue;

			fDistanceX = fabs(pShot[i].fX - g_Menu[j].droPic.fCurPosX);
			nSumWidth = (pShot[i].nWidth + g_Menu[j].droPic.nWidth) / 2;
			if (fDistanceX > nSumWidth)	continue;

			//----- 当たった時 -----
			pShot[i].bExist = false;		//弾消滅
			g_Menu[j].nHp -= 25;
			CreateEffect(pShot[i].fX, g_Menu[j].droPic.fCurPosY, EXPLOSION);
		}
	}
}


void UnInitTitle(void)
{
	UnInitDrawObject(&g_DrObjTitle);
	for (int i = 0; i < MAX_MEMU; i++)
		UnInitDrawObject(&g_Menu[i].droPic);
}