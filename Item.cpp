//Item.cpp

//===== インクルード部 =====
#include"Item.h"
#include"Player.h"
#include"Enemy.h"
#include"Bmp.h"
#include"Console.h"
#include"Player.h"
#include"GameManager.h"
#include"Score.h"
#include"Sound.h"
#include<math.h>
#include<Windows.h>
#include<stdio.h>


//===== 定数定義 =====
#define ITEM_PIC	"BMP/PItem.bmp"
#define MAX_ITEM	(3)
#define LIFE_SPAN	(3000)
#define MAX_BOUND	(10)
#define GETITEM_SE	"sound/powerup04.mp3"

//===== プロトタイプ宣言 =====
void ChkColItemAndPlayer(void);


//===== グローバル変数 =====
ITEM g_Item[MAX_ITEM];
DRAW_OBJECT g_drObjPupItem;
int g_nGetItemSE;

void InitItem(void)
{
	int i;
	char filename[] = ITEM_PIC;

	ReadBmp(filename, &g_drObjPupItem);

	for (i = 0; i < MAX_ITEM; i++)
	{
		g_Item[i].bExist = false;
		g_Item[i].nHeight = g_drObjPupItem.nHeight;
		g_Item[i].nWidth = g_drObjPupItem.nWidth;
	}

	g_nGetItemSE = CreateSound(GETITEM_SE);
	if (g_nGetItemSE == INVALID_HANDLE)
	{
		printf("ファイルが開けません:%s", GETITEM_SE);
	}
}


void CreateItem(float x,float y)
{
	int i;

	for (i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bExist == true)	continue;

		g_Item[i].bExist = true;
		g_Item[i].fCurPosX = g_Item[i].fPrePosX = x;
		g_Item[i].fCurPosY = g_Item[i].fPrePosY = y;
		g_Item[i].nXdir = g_Item[i].nYdir = -1;
		g_Item[i].nTime = 0;
		g_Item[i].nBound = 0;
		g_Item[i].fAngle = rand();					//移動角度
		break;
	}
}


void UpdItem(void)
{
	int i;

	for (i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bExist == false)	continue;

		//----- 過去座標退避 -----
		g_Item[i].fPrePosX = g_Item[i].fCurPosX;
		g_Item[i].fPrePosY = g_Item[i].fCurPosY;


		//----- 移動 -----
		g_Item[i].fCurPosX += g_Item[i].nXdir *cos(g_Item[i].fAngle);
		g_Item[i].fCurPosY += g_Item[i].nYdir*sin(g_Item[i].fAngle);

		//----- 画面端に行ったら方向転換 -----
		if (g_Item[i].nBound < MAX_BOUND)		//バウンド可能数以下なら
		{
			if (g_Item[i].fCurPosX < LIMIT_LEFT || LIMIT_RIGHT < g_Item[i].fCurPosX)
			{
				g_Item[i].nXdir *= -1;
				g_Item[i].fCurPosX = g_Item[i].fPrePosX;
				g_Item[i].nBound++;
			}
			if (g_Item[i].fCurPosY < LIMIT_TOP || LIMIT_BOTTOM < g_Item[i].fCurPosY)
			{
				g_Item[i].nYdir *= -1;
				g_Item[i].fCurPosY = g_Item[i].fPrePosY;
				g_Item[i].nBound++;
			}
		}
		//----- 寿命が来たら消える -----
		if (g_Item[i].nTime > LIFE_SPAN)
			g_Item[i].bExist = false;

		g_Item[i].nTime++;		//時間経過

		//----- バウンドせずに画面外に行ったら消える -----
		if (LIMIT_LEFT < g_Item[i].fCurPosX < LIMIT_RIGHT)	continue;
		if (LIMIT_TOP < g_Item[i].fCurPosY < LIMIT_BOTTOM)	continue;
		g_Item[i].bExist = false;
	}

	ChkColItemAndPlayer();
}

void DrawItem(void)
{
	int i;

	for (i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bExist == false)	continue;

		g_drObjPupItem.fCurPosX = g_Item[i].fCurPosX;
		g_drObjPupItem.fCurPosY = g_Item[i].fCurPosY;

		AddObjectToBuf(&g_drObjPupItem);
	}
}


void ChkColItemAndPlayer(void)
{
	int i;
	float fDistanceX, fDistanceY;
	int nSumHeight, nSumWidth;
	PLAYER *pPlayer = GetPlayer();

	for (i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bExist == false)	continue;

		//----- 矩形同士の当たり判定 -----
		fDistanceY = fabs(g_Item[i].fCurPosY - pPlayer->fCurPosY);		//アイテムとプレイヤーのY距離の絶対値
		nSumHeight = (g_Item[i].nHeight + pPlayer->drObject->nHeight) / 2;
		if (fDistanceY > nSumHeight)	continue;

		fDistanceX = fabs(g_Item[i].fCurPosX - pPlayer->fCurPosX);
		nSumWidth = (g_Item[i].nWidth + pPlayer->drObject->nWidth) / 2;
		if (fDistanceX > nSumWidth)	continue;

		//----- 当たった時 -----
		g_Item[i].bExist = false;
		if (pPlayer->shotLevel < PLAYER_MAX_SHOTLEVEL)
			pPlayer->shotLevel += 2;
		else
			AddScore(1000);
		PlaySound(g_nGetItemSE, false);
	}
}

void UnInitItem(void)
{
	UnInitDrawObject(&g_drObjPupItem);
}