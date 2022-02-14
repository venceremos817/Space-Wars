//Effect.cpp


//===== インクルード部 =====
#include"Effect.h"
#include"Console.h"
#include"Bmp.h"
#include"Sound.h"
#include<Windows.h>
#include<stdio.h>

//===== 定数定義 =====
#define MAX_EFFECT	(30)
#define	EXPLOSION_PIC	"BMP/explosion.bmp"
#define EXPLOSION_MAX_FILM	(5)
#define SEXPLO_SE		"sound/damage2.mp3"


//===== プロトタイプ宣言 =====
void InitExplosion(void);
void UpdExplosion(int effectnum);
void DrawExplosion(int effectnum);

//===== グローバル変数 =====
EFFECT g_Effect[MAX_EFFECT];
DRAW_OBJECT g_DrObjExplosion;
int g_nSmExploSE[MAX_EFFECT];


void InitEffect(void)
{
	int i;

	for (i = 0; i < MAX_EFFECT; i++)
	{
		g_Effect[i].bExist = false;
	}

	InitExplosion();
}

void CreateEffect(float x, float y, EFFECT_TYPE type)
{
	int i;

	for (i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].bExist == true)	continue;

		g_Effect[i].bExist = true;
		g_Effect[i].fX = x;
		g_Effect[i].fY = y;
		g_Effect[i].nType = type;
		g_Effect[i].nTime = 0;
		g_Effect[i].nFilm = 0;
		PlaySound(g_nSmExploSE[i], false);
		break;
	}

}



void UpdEffect(void)
{
	int i;

	for (i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].bExist == false)	continue;

		switch (g_Effect[i].nType)
		{
		case EXPLOSION:
			UpdExplosion(i);
			break;
		default:
			break;
		}
	}


}

void DrawEffect(void)
{
	int i;

	for (i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].bExist == false)	continue;

		switch (g_Effect[i].nType)
		{
		case EXPLOSION:
			DrawExplosion(i);
			break;

		default:
			break;
		}
	}


}

void InitExplosion(void)
{
	int i;
	char filename[] = { EXPLOSION_PIC };

	ReadBmp(filename, &g_DrObjExplosion);

	for (i = 0; i < MAX_EFFECT; i++)
	{
		g_nSmExploSE[i] = CreateSound(SEXPLO_SE);
		if (g_nSmExploSE[i] == INVALID_HANDLE)
		{
			printf("ファイルが開けません:%s", SEXPLO_SE);
			getchar();
		}
		SetVolume(g_nSmExploSE[i], 0.5f);
	}
}

void UpdExplosion(int effectnum)
{
	if (g_Effect[effectnum].nTime % 5 == 0)
		g_Effect[effectnum].nFilm++;

	if (g_Effect[effectnum].nFilm > EXPLOSION_MAX_FILM)
		g_Effect[effectnum].bExist = false;

	g_Effect[effectnum].nTime++;
}

void DrawExplosion(int effectnum)
{
		g_DrObjExplosion.pos.fX = g_Effect[effectnum].fX - 11;
		g_DrObjExplosion.pos.fY = g_Effect[effectnum].fY - 5;

		CutObjectAndAddToBuf(&g_DrObjExplosion, 10 * g_Effect[effectnum].nFilm, 10 * g_Effect[effectnum].nFilm + 9);
	
}

EFFECT *GetEffect(void)
{
	return g_Effect;
}

bool ChkRemainEffect(void)
{
	int i;
	for (i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].bExist == true)
			return true;
	}
	return false;
}

void UnInitEffect(void)
{
	UnInitDrawObject(&g_DrObjExplosion);
}