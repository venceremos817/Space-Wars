//Boss.cpp

//===== インクルード部 =====
#include"Boss.h"
#include"Bmp.h"
#include"Console.h"
#include"Enemy.h"
#include"EnemyShot.h"
#include"GameManager.h"
#include"Effect.h"
#include"PlayerShot.h"
#include"Item.h"
#include"main.h"
#include<math.h>

//===== 定数定義 =====
#define BOSS_PIC			"BMP/Boss.bmp"
#define BOSS_HP				(200)
#define BOSS_VERTICAL_SPD	(1.0)
#define BOSS_HORIZON_SPD	(2.0)
#define BOSS_SHOT_RATE		(10)
#define DEAD				(0)

//===== プロトタイプ宣言 ＝＝＝＝＝
bool ChkPBodyAndBBody(void);
void DestroyBoss(void);

//===== グローバル変数 =====
ENEMY g_Boss;
DRAW_OBJECT g_DrObjBoss;
int g_nDirection;
//int g_nBossDestroyTime;
//bool g_bDestroy;

void InitBoss(void)
{
	char filename[] = { BOSS_PIC };
	ReadBmp(filename, &g_DrObjBoss);

	g_Boss.bExist = false;
	g_Boss.nHeight = g_DrObjBoss.nHeight;
	g_Boss.nWidth = g_DrObjBoss.nWidth;
	g_Boss.nHP = BOSS_HP;
	g_Boss.fCurPosX = (LIMIT_LEFT + LIMIT_RIGHT) / 2;
	g_Boss.fCurPosY = LIMIT_TOP - g_Boss.nHeight / 2;
	g_nDirection = 1;
	g_Boss.nExistTime = 0;
	//g_bDestroy = false;
}

void CreateBoss(void)
{
	g_Boss.bExist = true;
}

void UpdBoss(void)
{
	if (g_Boss.bExist == true)
	{
		if (g_Boss.fCurPosY - g_Boss.nHeight / 2 < LIMIT_TOP)
		{
			g_Boss.fCurPosY += 0.2;
		}
		else
		{
			g_Boss.fCurPosX += g_nDirection * BOSS_HORIZON_SPD;

		if (g_Boss.nExistTime%BOSS_SHOT_RATE == 0)
				CreateBossShot(rand() % 3 + 1);
		}

		if (g_Boss.fCurPosX < LIMIT_LEFT)
			g_nDirection = 1;
		if (g_Boss.fCurPosX > LIMIT_RIGHT)
			g_nDirection = -1;

		if (ChkPBodyAndBBody())
		{
			DestroyPlayer();
		}

		if (ChkColPShotAndBoss())
		{
			g_Boss.nHP--;
			if (g_Boss.nHP % 30 == 0)
				CreateItem(g_Boss.fCurPosX, g_Boss.fCurPosY);

		}
		if (g_Boss.nHP <= DEAD)
		{
			//if (g_bDestroy == false)
			//	DestroyBoss();
			//if (ChkRemainEffect == false)
			//{
				PLAYER *pPlayer = GetPlayer();
				g_Boss.bExist = false;
				pPlayer->shotLevel = 1;
				UnInit();
				SetMode(MODE_RESULT);
				Init();
			//}
		}

		g_Boss.nExistTime++;
	}
}

void DrawBoss(void)
{
	if (g_Boss.bExist == true)
	{
		g_DrObjBoss.fCurPosX = g_Boss.fCurPosX;
		g_DrObjBoss.fCurPosY = g_Boss.fCurPosY;
		AddObjectToBuf(&g_DrObjBoss);
	}
}

bool ChkPBodyAndBBody(void)
{
	PLAYER *pPlayer = GetPlayer();
	float fDistanceX, fDistanceY;
	int nSumHeight, nSumWidth;

	if (pPlayer->bExist == false)
		return false;
	if (pPlayer->nInvincible > 0)
		return false;

	//----- 矩形同士の当たり判定 -----
	fDistanceY = fabs(pPlayer->fCurPosY - g_Boss.fCurPosY);
	nSumHeight = (pPlayer->drObject->nHeight + g_Boss.nHeight) / 2;
	fDistanceX = fabs(pPlayer->fCurPosX - g_Boss.fCurPosX);
	nSumWidth = (pPlayer->drObject->nWidth + g_Boss.nWidth) / 2;

	if (fDistanceY < nSumHeight && fDistanceX < nSumWidth)
		return true;
	return false;
}

void DestroyBoss(void)		//改良の余地あり
{
	int i, j, k;

	for (k = 0; k < 3; k++)
	{
		for (i = 0; i < g_Boss.nHeight; i++)
		{
			for (j = 0; j < g_Boss.nWidth; j++)
				CreateEffect((int)(g_DrObjBoss.pos.fX + j), (int)(g_DrObjBoss.pos.fY + i), EXPLOSION);
		}
	}
	//g_bDestroy = true;
}

ENEMY *GetBoss(void)
{
	return &g_Boss;
}

void UnInitBoss(void)
{
	UnInitDrawObject(&g_DrObjBoss);
}