//Shot.cpp

//===== インクルード部 =====
#include"PlayerShot.h"
#include"Player.h"
#include"Bmp.h"
#include"GameManager.h"
#include"Enemy.h"
#include"Score.h"
#include"Effect.h"
#include"Boss.h"
#include"Sound.h"
#include<math.h>
#include<stdio.h>
#include<Windows.h>

//===== 定数定義 =====
#define PSHOT_1_PIC			"BMP/OrangeLaser.bmp"
#define PSHOT_2_PIC			"BMP/OrangeBall.bmp"
//#define	PRASER_PIC			"BMP/power_raser.bmp"
#define	PSHOT_SE			"sound/shoot3.mp3"

//===== 列挙型 =====
enum
{
	PSHOT1,
	PSHOT2,
	MAX_PSHOT
};

//===== 構造体宣言 =====
typedef struct
{
	float fX;
	float fY;
	float fTop;
	float fBottom;
	int nWidth;
	bool bExist;
}RASER;


//===== プロトタイプ宣言 =====
void ChkColPShotAndEBody(void);
//void UpdRaser(void);
//void DrawRaser(void);


//===== グローバル変数宣言 =====
SHOT g_playerShot[PLAYER_MAX_SHOT_WAY][PLAYER_MAX_SHOT_NUM];
DRAW_OBJECT DrObjPShot[MAX_PSHOT];
//RASER g_raser;
//DRAW_OBJECT DrObjRaser;
int g_nPShotSE;

void InitPlayerShot(void)
{
	char shotfilename[MAX_PSHOT][25] = { PSHOT_1_PIC  , PSHOT_2_PIC };
	//char raserfilename[] = { PRASER_PIC };

	int i, j;

	for (i = 0; i < MAX_PSHOT; i++)
	{
		ReadBmp(shotfilename[i], &DrObjPShot[i]);
	}

	//ReadBmp(raserfilename, &DrObjRaser);

	for (i = 0; i < PLAYER_MAX_SHOT_WAY; i++)
	{
		for (j = 0; j < PLAYER_MAX_SHOT_NUM; j++)
		{
			g_playerShot[i][j].bExist = false;
		}
	}

	//----- SE -----
	g_nPShotSE = CreateSound(PSHOT_SE);
	if (g_nPShotSE == INVALID_HANDLE)
	{
		printf("ファイルが開けません:%s", PSHOT_SE);
		getchar();
	}
	SetVolume(g_nPShotSE, 0.3f);
}


void CreatePlayerShot(PLAYER player)
{
	int i, j;
	int posX[11] = { 0,-5,5,-5,5,-8,8,-5,5,-5,5 };
	int posY[11] = { -5,-1,-1,3,3,-3,-3,1,1,5,5 };

	for (i = 0; i < player.shotLevel; i++)
	{
		for (j = 0; j < PLAYER_MAX_SHOT_NUM; j++)
		{
			if (g_playerShot[i][j].bExist == true)	continue;	//配列が使用中ならcontinue
			g_playerShot[i][j].bExist = true;
			g_playerShot[i][j].fX = player.fCurPosX + (float)posX[i];
			g_playerShot[i][j].fY = player.fCurPosY + (float)posY[i];
			switch (i)
			{
			case 0:
			case 5:
			case 6:
				g_playerShot[i][j].nHeight = DrObjPShot[PSHOT1].nHeight;
				g_playerShot[i][j].nWidth = DrObjPShot[PSHOT1].nWidth;
				break;
			default:
				g_playerShot[i][j].nHeight = DrObjPShot[PSHOT2].nHeight;
				g_playerShot[i][j].nWidth = DrObjPShot[PSHOT2].nWidth;
				break;
			}
			PlaySound(g_nPShotSE, false);
			break;
		}
	}
}

void UpdPlayerShot(void)
{
	int i, j;
	float moveX[11] = { 0 , -0.5 , 0.5 , -1.5 , 1.5 , 0 , 0 , -1.0 , 1.0 , -2.0 , 2.0 };

	for (i = 0; i < PLAYER_MAX_SHOT_WAY; i++)
	{
		for (j = 0; j < PLAYER_MAX_SHOT_NUM; j++)
		{
			if (g_playerShot[i][j].bExist == false)	continue;	//存在していなけれれcontinue
			g_playerShot[i][j].fX += moveX[i];
			g_playerShot[i][j].fY -= 3.5f;

			//画面外に行った時の処理
			if (g_playerShot[i][j].fY  < LIMIT_TOP)
				g_playerShot[i][j].bExist = false;
			if (g_playerShot[i][j].fX  < LIMIT_LEFT)
				g_playerShot[i][j].bExist = false;
			if (g_playerShot[i][j].fX  > LIMIT_RIGHT)
				g_playerShot[i][j].bExist = false;
		}
	}
	//UpdRaser();
	ChkColPShotAndEBody();
}

void DrawPlayerShotToBuf(void)
{
	int i, j;

//	DrawRaser();
	for (i = 0; i < PLAYER_MAX_SHOT_WAY; i++)
	{
		for (j = 0; j < PLAYER_MAX_SHOT_NUM; j++)
		{
			if (g_playerShot[i][j].bExist == false)	continue;

			switch (i)
			{
			case 0:
			case 5:
			case 6:
				DrObjPShot[PSHOT1].fCurPosX = g_playerShot[i][j].fX;
				DrObjPShot[PSHOT1].fCurPosY = g_playerShot[i][j].fY;
				AddObjectToBuf(&DrObjPShot[PSHOT1]);
				break;
			default:
				DrObjPShot[PSHOT2].fCurPosX = g_playerShot[i][j].fX;
				DrObjPShot[PSHOT2].fCurPosY = g_playerShot[i][j].fY;
				AddObjectToBuf(&DrObjPShot[PSHOT2]);
				break;
			}
		}
	}
}

void ChkColPShotAndEBody(void)
{
	int i, j, k;
	float fDistanceX, fDistanceY;
	int nSumWidth, nSumHeight;
	ENEMY *pEnemy = GetEnemy();

	for (i = 0; i < PLAYER_MAX_SHOT_WAY; i++)
	{
		for (j = 0; j < PLAYER_MAX_SHOT_NUM; j++)
		{
			if (g_playerShot[i][j].bExist == false)	continue;
			for (k = 0; k < MAX_ENEMY; k++)
			{
				if (pEnemy[k].bExist == false)	continue;

				//----- 矩形同士で当たり判定をとる -----
				fDistanceY = fabs(g_playerShot[i][j].fY - pEnemy[k].fCurPosY);
				nSumHeight = (g_playerShot[i][j].nHeight + pEnemy[k].nHeight) / 2;
				if (fDistanceY > nSumHeight)	continue;

				fDistanceX = fabs(g_playerShot[i][j].fX - pEnemy[k].fCurPosX);
				nSumWidth = (g_playerShot[i][j].nWidth + pEnemy[k].nWidth) / 2;
				if (fDistanceX > nSumWidth)	continue;

				//----- 当たった時 -----
				g_playerShot[i][j].bExist = false;		//弾消滅
				pEnemy[k].nHP--;						//敵にダメージ
				CreateEffect(pEnemy[k].fCurPosX, pEnemy[k].fCurPosY, EXPLOSION);
				AddScore(100);
			}
		}
	}
}

bool ChkColPShotAndBoss(void)
{
	int i, j;
	float fDistanceX, fDistanceY;
	int nSumWidth, nSumHeight;
	ENEMY *pBoss = GetBoss();

	for (i = 0; i < PLAYER_MAX_SHOT_WAY; i++)
	{
		for (j = 0; j < PLAYER_MAX_SHOT_NUM; j++)
		{
			if (g_playerShot[i][j].bExist == false)	continue;

			//----- 矩形同士で当たり判定をとる -----
			fDistanceY = fabs(g_playerShot[i][j].fY - pBoss->fCurPosY);
			nSumHeight = (g_playerShot[i][j].nHeight + pBoss->nHeight) / 2;
			if (fDistanceY > nSumHeight)	continue;

			fDistanceX = fabs(g_playerShot[i][j].fX - pBoss->fCurPosX);
			nSumWidth = (g_playerShot[i][j].nWidth + pBoss->nWidth) / 2;
			if (fDistanceX > nSumWidth)	continue;

			//----- 当たってる -----
			CreateEffect(g_playerShot[i][j].fX, g_playerShot[i][j].fY, EXPLOSION);
			g_playerShot[i][j].bExist = false;
			return true;
		}
	}
	//----- あたってない -----
	return false;
}

//void CreateRaser(void)
//{
//	PLAYER *pPlayer = GetPlayer();
//
//	g_raser.bExist = true;
//}

//void UpdRaser(void)
//{
//	if (g_raser.bExist == true)
//	{
//		PLAYER *pPlayer = GetPlayer();
//
//		g_raser.fX = pPlayer->fCurPosX;
//		g_raser.fBottom = pPlayer->fCurPosY - pPlayer->drObject->nHeight / 2;
//		g_raser.fY = g_raser.fBottom - DrObjRaser.nHeight / 2;
//		g_raser.fTop = g_raser.fY - DrObjRaser.nHeight / 2;
//	}
//}
//
//void DrawRaser(void)
//{
//	if (g_raser.bExist == true)
//	{
//		DrObjRaser.fCurPosX = g_raser.fX;
//		DrObjRaser.fCurPosY = g_raser.fY;
//		AddObjectToBuf(&DrObjRaser);
//		g_raser.bExist = false;
//	}
//}

void UnInitPlayerShot(void)
{
	UnInitDrawObject(&DrObjPShot[PSHOT1]);
	UnInitDrawObject(&DrObjPShot[PSHOT2]);
	//UnInitDrawObject(&DrObjRaser);
}

SHOT *GetShotLine1(void)
{
	return g_playerShot[0];
}