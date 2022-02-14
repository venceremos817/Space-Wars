//Player.cpp



//===== インクルード部 =====
#include"Player.h"
#include"Bmp.h"
#include"Console.h"
#include"GameManager.h"
#include"PlayerShot.h"
#include"Score.h"
#include"Effect.h"
#include"Sound.h"
#include"main.h"
#include<Windows.h>
#include<stdio.h>

//===== 定数定義 =====
#define PLAYER_PICT_CENTER	"BMP/Player_middle.bmp"
#define PLAYER_PICT_LEFT	"BMP/Player_left.bmp"
#define PLAYER_PICT_RIGHT	"BMP/Player_right.bmp"
#define SHOT_DELAY			(10)
#define INVINCIBLE_TIME		(100)
#define DAMAGE_SE			"sound/bomb.mp3"



//===== グローバル変数 =====
PLAYER g_player;
int g_ShotCnt;
int g_time;
int g_nPDamageSE;

void InitPlayer(void)
{
	int i;
	char filename[MAX_FORM][30] = { PLAYER_PICT_CENTER , PLAYER_PICT_LEFT , PLAYER_PICT_RIGHT };


	g_ShotCnt = -1;
	g_player.bExist = true;
	g_player.fCurPosX = g_player.fPrePosX = LIMIT_RIGHT / 2 - 10;
	g_player.fCurPosY = g_player.fPrePosY = LIMIT_BOTTOM - 10;
	g_player.fMoveSpdX = 3.5f;
	g_player.fMoveSpdY = 2.5f;
	g_player.shotLevel = 1;
	g_player.nLeft = 3;
	g_player.nInvincible = 0;

	for (i = 0; i < MAX_FORM; i++)
		ReadBmp(filename[i], &g_player.drObject[i]);

	//g_nPDamageSE = CreateSound(DAMAGE_SE);
	//if (g_nPDamageSE == INVALID_HANDLE);
	//{
	//	printf("ファイルが開けません:%s", DAMAGE_SE);
	//}

	g_nPDamageSE = CreateSound(DAMAGE_SE);
	if (g_nPDamageSE == INVALID_HANDLE)
	{
		printf("ファイルが開けません:%s", DAMAGE_SE);
		getchar();
	}
	SetVolume(g_nPDamageSE, 1.0f);

}

void CreatePlayer(void)
{
	g_player.bExist = true;
	g_player.fCurPosX = g_player.fPrePosX = LIMIT_RIGHT / 2-10;
	g_player.fCurPosY = g_player.fPrePosY = LIMIT_BOTTOM-10;
	g_player.shotLevel = 1;
	g_player.nInvincible = INVINCIBLE_TIME;
	//g_player.object.fMoveSpdX = g_player.object.fMoveSpdY = 0.5f;
	//g_player.object.Drawobject.pos.fX = g_player.object.Drawobject.pos.fY = 0.0f;
}

void UpdPlayer(void)
{
	if(g_player.bExist == false && g_player.nLeft > -1)
		if (GetKeyState(VK_SPACE) & 0x80)
		{
			CreatePlayer();
		}
	if (g_player.nLeft < 0)
	{
		UnInit();
		SetMode(MODE_RESULT);
		Init();
	}


	if (g_player.bExist == true)
	{
		//過去座標の退避
		g_player.fPrePosX = g_player.fCurPosX;
		g_player.fPrePosY = g_player.fCurPosY;


		//キー入力による移動
		g_player.nDirection = MIDDLE;

		if (GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)
		{
			g_player.fCurPosY -= g_player.fMoveSpdY;
		}
		if (GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)
		{
			g_player.fCurPosY += g_player.fMoveSpdY;
		}
		if (GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)
		{
			g_player.fCurPosX -= g_player.fMoveSpdX;
			g_player.nDirection = LEFT;
		}
		if (GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)
		{
			g_player.fCurPosX += g_player.fMoveSpdX;
			g_player.nDirection = RIGHT;
		}
		if (GetKeyState('Z') & 0x80 && !(GetKeyState('X') & 0x80))
		{
			if (g_ShotCnt < 0)
			{
				CreatePlayerShot(g_player);
				g_ShotCnt = SHOT_DELAY;
			}
		}
		//if (GetKeyState('X') & 0x80 && !(GetKeyState('Z') & 0x80))			//ゲームバランス崩れそうなのでなし
		//{
		//	CreateRaser();
		//}


		if (g_ShotCnt > -1)
			g_ShotCnt--;


		//画面外に行ったときの処理
		if (g_player.fCurPosX - g_player.drObject->nWidth / 2 < LIMIT_LEFT)
			g_player.fCurPosX = g_player.fPrePosX;
		if (g_player.fCurPosX + g_player.drObject->nWidth / 2 > LIMIT_RIGHT)
			g_player.fCurPosX = g_player.fPrePosX;
		if (g_player.fCurPosY - g_player.drObject->nHeight / 2 < LIMIT_TOP)
			g_player.fCurPosY = g_player.fPrePosY;
		if (g_player.fCurPosY + g_player.drObject->nHeight / 2 > LIMIT_BOTTOM)
			g_player.fCurPosY = g_player.fPrePosY;

		g_time++;

		if (g_time % 10 == 0)
		{
			AddScore(1);
			g_time = 0;
		}
		if (g_player.nInvincible > -1)
		{
			g_player.nInvincible--;
		}
	}
}

void DrawPlayerToBuf(void)
{
	if (g_player.bExist == true)
	{
		if (g_player.nInvincible % 6 < 4)
		{
			g_player.drObject[g_player.nDirection].fCurPosX = g_player.fCurPosX;
			g_player.drObject[g_player.nDirection].fCurPosY = g_player.fCurPosY;

			AddObjectToBuf(&g_player.drObject[g_player.nDirection]);
		}
	}
}

void DestroyPlayer(void)
{
	g_player.bExist = false;
	PlaySound(g_nPDamageSE, false);
	CreateEffect(g_player.fCurPosX, g_player.fCurPosY, EXPLOSION);
	g_player.nLeft--;
}

PLAYER *GetPlayer(void)
{
	return &g_player;
}

void UniInitPlayer(void)
{
	for (int i = 0; i < 3; i++)
		UnInitDrawObject(&g_player.drObject[i]);
}