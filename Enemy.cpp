//Enemy.cpp

//===== インクルード部 =====
#include"Enemy.h"
#include"Console.h"
#include"Bmp.h"
#include"Player.h"
#include"GameManager.h"
#include"EnemyShot.h"
#include"Item.h"
#include"Score.h"
#include"Effect.h"
#include"main.h"
#include"Boss.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//===== 定数・マクロ定義 =====
#define ENEMY_1_PIC		"BMP/Enemy1.bmp"
#define ENEMY_2_PIC		"BMP/Enemy2.bmp"
#define ENEMY_3_PIC		"BMP/Enemy3.bmp"
#define ENEMY_4_PIC		"BMP/Enemy4.bmp"
#define ENEMY_5_PIC		"BMP/Enemy5.bmp"
#define ENEMY_6_PIC		"BMP/Enemy6.bmp"
#define ENEMY_7_PIC		"BMP/Enemy7.bmp"
#define DEAD			(0)
#define ENEMY1_HP		(1)
#define	ENEMY2_HP		(5)
#define	ENEMY3_HP		(3)
#define ENEMY4_HP		(3)
#define ENEMY5_HP		(7)
#define ENEMY6_HP		(7)
#define ENEMY7_HP		(7)
#define PI				(3.141592)
#define RAND_MIN		(30)
#define RAND_RANGE		(600 - RAND_MIN + 1)
#define RANDAM(a,b)		a + rand() * (b - a + 1.0) / (1.0 + RAND_MAX)
#define	ENEMY_DATAEND		(-1)

//===== 列挙型 =====
typedef enum
{
	ENEMY_TYPE1,
	ENEMY_TYPE2,
	ENEMY_TYPE3,
	ENEMY_TYPE4,
	ENEMY_TYPE5,
	ENEMY_TYPE6,
	ENEMY_TYPE7,
	MAX_ENEMY_TYPE
}ENEMY_TYPE;

typedef enum
{
	STAGE_0,
	STAGE_1,
	STAGE_2,
	END_STAGE
}STAGE_NUM;

//===== プロトタイプ宣言 =====
void InitEnemyPic(void);
void InitEnemyData(void);
void EnemyPattern1(int enemynum);
void EnemyPattern2(int enemynum);
void EnemyPattern3(int enemynum);
void EnemyPattern4(int enemynum);
void EnemyPattern5(int enemynum);
void EnemyPattern6(int enemynum);
void EnemyPattern7(int enemynum);
bool ChkColEnemyAndPlayer(int enemynum);

//===== グローバル変数 =====
ENEMY g_enemy[MAX_ENEMY];
DRAW_OBJECT g_DrObjEnemyPict[MAX_ENEMY_TYPE];
int g_Time = 0;
int g_EnemyCnt;
STAGE_NUM g_stagenum = STAGE_1;
char szEnemyMakeData[END_STAGE][20] = { "","Stage1EnemyMake.csv" };
PLAY_MODE g_playmode;


void InitEnemy(void)
{
	int i;

	//ZeroMemory(g_enemy, sizeof(g_enemy));
	InitEnemyPic();
	InitEnemyData();


	for (i = 0; i < MAX_ENEMY; i++)
	{
		g_enemy[i].bExist = false;
		g_enemy[i].nHP = 1;
	}
	g_Time = 0;


	InitBoss();
}

void InitEnemyPic(void)
{
	int i;
	char filename[MAX_ENEMY_TYPE][20] = { ENEMY_1_PIC , ENEMY_2_PIC ,ENEMY_3_PIC , ENEMY_4_PIC , ENEMY_5_PIC , ENEMY_6_PIC , ENEMY_7_PIC };

	for (i = 0; i < MAX_ENEMY_TYPE; i++)
		ReadBmp(filename[i], &g_DrObjEnemyPict[i]);
}

void InitEnemyData(void)
{
	FILE *fp;
	errno_t error;
	int i;
	int nApperTime;
	int type;
	int x, y;


	if ((error = fopen_s(&fp, "Stage1EnemyMake.csv", "r+") != 0))
	{
		printf("Error:ファイルを開けません %s", szEnemyMakeData[g_stagenum]);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}
	else
	{
		for (i = 0; i < MAX_ENEMY && fscanf(fp, "%d,%d,%d,%d", &nApperTime, &type, &x, &y) != EOF; i++)
		{
			g_enemy[i].nApperTime = nApperTime;
			g_enemy[i].nType = type;
			g_enemy[i].fCurPosX = (float)x;
			g_enemy[i].fCurPosY = (float)y;
		}
		g_enemy[i].nApperTime = ENEMY_DATAEND;	//敵データの終わりを示す
	}

	fclose(fp);
	g_EnemyCnt = 0;
}

void CreateEnemy(void)
{
	int i;
	int existcnt;
	PLAYER *pPlayer = GetPlayer();

	switch (g_playmode)
	{
	case NORMAL_MODE:
		if (pPlayer->bExist == true)
		{
			for (i = 0, existcnt = 0; i < g_EnemyCnt&&existcnt == 0; i++)
			{
				if (g_enemy[i].bExist == true)
					existcnt++;
			}

			if (existcnt == 0 || (g_enemy[g_EnemyCnt].nApperTime < g_Time))//&&g_enemy[g_EnemyCnt].nApperTime != ENEMY_DATAEND
			{
				g_enemy[g_EnemyCnt].bExist = true;
				g_enemy[g_EnemyCnt].nExistTime = 0;

				if (g_enemy[g_EnemyCnt].nApperTime == ENEMY_DATAEND)
				{
					CreateBoss();

				}
				switch (g_enemy[g_EnemyCnt].nType)
				{
				case 1:
					g_enemy[g_EnemyCnt].nHP = ENEMY1_HP;
					g_enemy[g_EnemyCnt].nHeight = g_DrObjEnemyPict[ENEMY_TYPE1].nHeight;
					g_enemy[g_EnemyCnt].nWidth = g_DrObjEnemyPict[ENEMY_TYPE1].nWidth;
					g_enemy[g_EnemyCnt].nPattern = 1;
					g_enemy[g_EnemyCnt].nExistTime = 0;
					g_enemy[g_EnemyCnt].nType = ENEMY_TYPE1;
					break;

				case 2:
					g_enemy[g_EnemyCnt].nHP = ENEMY2_HP;
					g_enemy[g_EnemyCnt].nHeight = g_DrObjEnemyPict[ENEMY_TYPE2].nHeight;
					g_enemy[g_EnemyCnt].nWidth = g_DrObjEnemyPict[ENEMY_TYPE2].nWidth;
					g_enemy[g_EnemyCnt].nPattern = 2;
					g_enemy[g_EnemyCnt].nExistTime = 0;
					g_enemy[g_EnemyCnt].nType = ENEMY_TYPE2;
					break;

				case 3:
					g_enemy[g_EnemyCnt].nHP = ENEMY3_HP;
					g_enemy[g_EnemyCnt].nHeight = g_DrObjEnemyPict[ENEMY_TYPE3].nHeight;
					g_enemy[g_EnemyCnt].nWidth = g_DrObjEnemyPict[ENEMY_TYPE3].nWidth;
					g_enemy[g_EnemyCnt].nPattern = 3;
					g_enemy[g_EnemyCnt].nExistTime = 0;
					g_enemy[g_EnemyCnt].nType = ENEMY_TYPE3;
					break;

				case 4:
					g_enemy[g_EnemyCnt].nHP = ENEMY4_HP;
					g_enemy[g_EnemyCnt].nHeight = g_DrObjEnemyPict[ENEMY_TYPE4].nHeight;
					g_enemy[g_EnemyCnt].nWidth = g_DrObjEnemyPict[ENEMY_TYPE4].nWidth;
					g_enemy[g_EnemyCnt].nPattern = 4;
					g_enemy[g_EnemyCnt].nExistTime = 0;
					g_enemy[g_EnemyCnt].nType = ENEMY_TYPE4;
					break;

				case 5:
					g_enemy[g_EnemyCnt].nHP = ENEMY5_HP;
					g_enemy[g_EnemyCnt].nHeight = g_DrObjEnemyPict[ENEMY_TYPE5].nHeight;
					g_enemy[g_EnemyCnt].nWidth = g_DrObjEnemyPict[ENEMY_TYPE5].nWidth;
					g_enemy[g_EnemyCnt].nPattern = 5;
					g_enemy[g_EnemyCnt].nExistTime = 0;
					g_enemy[g_EnemyCnt].nType = ENEMY_TYPE5;
					break;

				case 6:
					g_enemy[g_EnemyCnt].nHP = ENEMY6_HP;
					g_enemy[g_EnemyCnt].nHeight = g_DrObjEnemyPict[ENEMY_TYPE6].nHeight;
					g_enemy[g_EnemyCnt].nWidth = g_DrObjEnemyPict[ENEMY_TYPE6].nWidth;
					g_enemy[g_EnemyCnt].nPattern = 6;
					g_enemy[g_EnemyCnt].nExistTime = 0;
					g_enemy[g_EnemyCnt].nType = ENEMY_TYPE6;
					break;

				case 7:
					g_enemy[g_EnemyCnt].nHP = ENEMY7_HP;
					g_enemy[g_EnemyCnt].nHeight = g_DrObjEnemyPict[ENEMY_TYPE7].nHeight;
					g_enemy[g_EnemyCnt].nWidth = g_DrObjEnemyPict[ENEMY_TYPE7].nWidth;
					g_enemy[g_EnemyCnt].nPattern = 7;
					g_enemy[g_EnemyCnt].nExistTime = 0;
					g_enemy[g_EnemyCnt].nType = ENEMY_TYPE7;
					break;

				default:
					break;
				}
				g_EnemyCnt++;
				g_Time = 1;
			}


		}
		break;
	
	case ENDLESS_MODE:
		/////////////////////////////////// 旧ver エンドレスモードに使えるかも

			
			for (i = 0; i < MAX_ENEMY; i++)
				if (g_enemy[i].bExist == false)
					break;						//存在していないenemyの添え字 i を保持してbreak
		
			switch (g_Time)
			{
			case 0:
//			case 100:
			case 200:
				g_enemy[i].bExist = true;
				g_enemy[i].nHP = ENEMY1_HP;
				g_enemy[i].nHeight = g_DrObjEnemyPict[ENEMY_TYPE1].nHeight;
				g_enemy[i].nWidth = g_DrObjEnemyPict[ENEMY_TYPE1].nWidth;
				g_enemy[i].fCurPosX = RAND_MIN + (float)rand()*RAND_RANGE / (1.0 + RAND_MAX);
				g_enemy[i].fCurPosY = g_enemy[i].nHeight / 2.0f + 1.0f;
				g_enemy[i].nPattern = 1;
				g_enemy[i].nExistTime = 0;
				g_enemy[i].nType = ENEMY_TYPE1;
				break;
		
			case 30:
//			case 130:
			case 230:
				g_enemy[i].bExist = true;
				g_enemy[i].nHP = ENEMY2_HP;
				g_enemy[i].nHeight = g_DrObjEnemyPict[ENEMY_TYPE2].nHeight;
				g_enemy[i].nWidth = g_DrObjEnemyPict[ENEMY_TYPE2].nWidth;
				g_enemy[i].fCurPosX = RAND_MIN + (float)rand()*RAND_RANGE / (1.0 + RAND_MAX);
				g_enemy[i].fCurPosY = g_enemy[i].nHeight / 2.0f + 1.0f;
				g_enemy[i].nPattern = 2;
				g_enemy[i].nExistTime = 0;
				g_enemy[i].nType = ENEMY_TYPE2;
				break;
		
			case 40:
//			case 140:
			case 240:
				g_enemy[i].bExist = true;
				g_enemy[i].nHP = ENEMY3_HP;
				g_enemy[i].nHeight = g_DrObjEnemyPict[ENEMY_TYPE3].nHeight;
				g_enemy[i].nWidth = g_DrObjEnemyPict[ENEMY_TYPE3].nWidth;
				g_enemy[i].fCurPosX = RAND_MIN + (float)rand()*RAND_RANGE / (1.0 + RAND_MAX);
				g_enemy[i].fCurPosY = g_enemy[i].nHeight / 2.0f + 1.0f;
				g_enemy[i].nPattern = 3;
				g_enemy[i].nExistTime = 0;
				g_enemy[i].nType = ENEMY_TYPE3;
				break;
		
			case 50:
//			case 150:
			case 250:
				g_enemy[i].bExist = true;
				g_enemy[i].nHP = ENEMY4_HP;
				g_enemy[i].nHeight = g_DrObjEnemyPict[ENEMY_TYPE4].nHeight;
				g_enemy[i].nWidth = g_DrObjEnemyPict[ENEMY_TYPE4].nWidth;
				g_enemy[i].fCurPosX = RAND_MIN + (float)rand()*RAND_RANGE / (1.0 + RAND_MAX);
				g_enemy[i].fCurPosY = g_enemy[i].nHeight / 2.0f + 1.0f;
				g_enemy[i].nPattern = 4;
				g_enemy[i].nExistTime = 0;
				g_enemy[i].nType = ENEMY_TYPE4;
				break;
		
			case 60:
//			case 160:
			case 260:
				g_enemy[i].bExist = true;
				g_enemy[i].nHP = ENEMY5_HP;
				g_enemy[i].nHeight = g_DrObjEnemyPict[ENEMY_TYPE5].nHeight;
				g_enemy[i].nWidth = g_DrObjEnemyPict[ENEMY_TYPE5].nWidth;
				g_enemy[i].fCurPosX = RAND_MIN + (float)rand()*RAND_RANGE / (1.0 + RAND_MAX);
				g_enemy[i].fCurPosY = g_enemy[i].nHeight / 2.0f + 1.0f;
				g_enemy[i].nPattern = 5;
				g_enemy[i].nExistTime = 0;
				g_enemy[i].nType = ENEMY_TYPE5;
				break;
		
			case 70:
//			case 170:
			case 270:
				g_enemy[i].bExist = true;
				g_enemy[i].nHP = ENEMY6_HP;
				g_enemy[i].nHeight = g_DrObjEnemyPict[ENEMY_TYPE6].nHeight;
				g_enemy[i].nWidth = g_DrObjEnemyPict[ENEMY_TYPE6].nWidth;
				g_enemy[i].fCurPosX = LIMIT_LEFT + g_enemy[i].nWidth / 2;
				g_enemy[i].fCurPosY = RANDAM(g_DrObjEnemyPict[ENEMY_TYPE6].nHeight / 2 + LIMIT_TOP, LIMIT_BOTTOM - g_DrObjEnemyPict[ENEMY_TYPE6].nHeight / 2);
				g_enemy[i].nPattern = 6;
				g_enemy[i].nExistTime = 0;
				g_enemy[i].nType = ENEMY_TYPE6;
				break;
		
			case 80:
//			case 180:
			case 280:
				g_enemy[i].bExist = true;
				g_enemy[i].nHP = ENEMY7_HP;
				g_enemy[i].nHeight = g_DrObjEnemyPict[ENEMY_TYPE7].nHeight;
				g_enemy[i].nWidth = g_DrObjEnemyPict[ENEMY_TYPE7].nWidth;
				g_enemy[i].fCurPosX = LIMIT_RIGHT - g_enemy[i].nWidth / 2;
				g_enemy[i].fCurPosY = RANDAM(g_DrObjEnemyPict[ENEMY_TYPE7].nHeight / 2 + LIMIT_TOP, LIMIT_BOTTOM - g_DrObjEnemyPict[ENEMY_TYPE7].nHeight / 2);
				g_enemy[i].nPattern = 7;
				g_enemy[i].nExistTime = 0;
				g_enemy[i].nType = ENEMY_TYPE7;
				break;
		
			default:
				break;
			}
			g_Time %= 300;
		//	/////////////////// ここまで旧ver
		break;
	default:
		break;
	}
}

void UpdEnemy(void)
{
	int i;
	PLAYER *pPlayer = GetPlayer();

	for (i = 0; i < MAX_ENEMY; i++)
	{
		if (g_enemy[i].bExist == false)	continue;

		//----- 過去座標の退避 -----
		g_enemy[i].fPrePosX = g_enemy[i].fCurPosX;
		g_enemy[i].fPrePosY = g_enemy[i].fCurPosY;

		switch (g_enemy[i].nPattern)
		{
		case 1:
			EnemyPattern1(i);
			break;
		case 2:
			EnemyPattern2(i);
			break;
		case 3:
			EnemyPattern3(i);
			break;
		case 4:
			EnemyPattern4(i);
			break;
		case 5:
			EnemyPattern5(i);
			break;
		case 6:
			EnemyPattern6(i);
			break;
		case 7:
			EnemyPattern7(i);
			break;
		default:
			break;
		}

		if (ChkColEnemyAndPlayer(i))	//プレイヤーとぶつかったら
		{
			DestroyPlayer();
		}

		//----- 画面外に行ったとき -----
		if (g_enemy[i].fCurPosX < LIMIT_LEFT)	//左
			g_enemy[i].bExist = false;
		if (g_enemy[i].fCurPosX  >LIMIT_RIGHT)	//右
			g_enemy[i].bExist = false;
		if (g_enemy[i].fCurPosY  < LIMIT_TOP)	//上
			g_enemy[i].bExist = false;
		if (g_enemy[i].fCurPosY >LIMIT_BOTTOM)	//下
			g_enemy[i].bExist = false;

		if (g_enemy[i].nHP <= DEAD)
		{
			AddScore(g_enemy[i].nPattern * 100);
			g_enemy[i].bExist = false;
			CreateEffect(g_enemy[i].fCurPosX, g_enemy[i].fCurPosY, EXPLOSION);

			if (rand() % 5 == 0)
				CreateItem(g_enemy[i].fCurPosX, g_enemy[i].fCurPosY);
		}
		g_enemy[i].nExistTime++;		//カウントアップ
	}
	CreateEnemy();
	g_Time++;

	UpdBoss();
}

void DrawEnemyToBuf(void)
{
	int i;
	for (i = 0; i < MAX_ENEMY; i++)
	{
		if (g_enemy[i].bExist == false)	continue;

		g_DrObjEnemyPict[g_enemy[i].nType].fCurPosX = g_enemy[i].fCurPosX;
		g_DrObjEnemyPict[g_enemy[i].nType].fCurPosY = g_enemy[i].fCurPosY;

		AddObjectToBuf(&g_DrObjEnemyPict[g_enemy[i].nType]);
	}
	DrawBoss();
}

//////////////////////////////////////////////
//	pattern1	まっすぐ降りてく
//////////////////////////////////////////////
void EnemyPattern1(int enemynum)
{
	g_enemy[enemynum].fCurPosY += 0.8f;
	if (g_enemy[enemynum].nExistTime % 150 == 50)
		CreateEnemyShot(enemynum, 3);
}

//////////////////////////////////////////////
//	pattern2	ある程度降りて、そのあと昇っていく
//////////////////////////////////////////////
void EnemyPattern2(int enemynum)
{
	if (g_enemy[enemynum].nExistTime < 100)
		g_enemy[enemynum].fCurPosY += 0.5f;
	if (g_enemy[enemynum].nExistTime == 130)
		CreateEnemyShot(enemynum, 2);
	if (g_enemy[enemynum].nExistTime > 200)
		g_enemy[enemynum].fCurPosY -= 0.5f;
}

//////////////////////////////////////////////
//	pattern3 左右に揺れながら降りてく
//////////////////////////////////////////////
void EnemyPattern3(int enemynum)
{
	g_enemy[enemynum].fCurPosX += sin(PI*g_enemy[enemynum].nExistTime / 80) * 2.0f;
	if (g_enemy[enemynum].fCurPosX - g_DrObjEnemyPict[g_enemy[enemynum].nType].nWidth / 2 < LIMIT_LEFT)		//左に行きすぎ
		g_enemy[enemynum].fCurPosX = g_enemy[enemynum].fPrePosX;
	if (g_enemy[enemynum].fCurPosX + g_DrObjEnemyPict[g_enemy[enemynum].nType].nWidth / 2 > LIMIT_RIGHT)		//右に行きすぎ
		g_enemy[enemynum].fCurPosX = g_enemy[enemynum].fPrePosX;

	g_enemy[enemynum].fCurPosY += 0.25f;

	if (g_enemy[enemynum].nExistTime % 150 == 50)
		CreateEnemyShot(enemynum, 1);
}

//////////////////////////////////////////////
//	pattern4	ある程度降りて、円運動
//////////////////////////////////////////////
void EnemyPattern4(int enemynum)
{
	if (g_enemy[enemynum].nExistTime < 100)
	{
		g_enemy[enemynum].fCurPosY += 0.5f;
	}
	else
	{
		g_enemy[enemynum].fCurPosX += sin(PI*(g_enemy[enemynum].nExistTime - 100.0f) / 100)*1.0f;
		g_enemy[enemynum].fCurPosY += sin(PI*(g_enemy[enemynum].nExistTime - 100.0f + 50.0f) / 100)*1.0f;
	}

	if (g_enemy[enemynum].nExistTime > 900)
		g_enemy[enemynum].fCurPosY -= 0.5f;

	if (g_enemy[enemynum].nExistTime % 150 == 50)
		CreateEnemyShot(enemynum, 1);

}

//////////////////////////////////////////////
//	pattern5	playerを追尾する、一定時間たつと下にフェードアウト
//////////////////////////////////////////////
void EnemyPattern5(int enemynum)
{
	PLAYER *player;
	player = GetPlayer();
	int nDirectX, nDirectY;

	if (g_enemy[enemynum].nExistTime < 800)
	{
		if (player->fCurPosX - g_enemy[enemynum].fCurPosX < 0)
			nDirectX = -1;
		else
			nDirectX = 1;
		if (player->fCurPosY - g_enemy[enemynum].fCurPosY < 0)
			nDirectY = -1;
		else
			nDirectY = 1;

		g_enemy[enemynum].fCurPosX += nDirectX * 0.25f;
		g_enemy[enemynum].fCurPosY += nDirectY * 0.25f;
	}

	if (g_enemy[enemynum].nExistTime >= 800)
	{
		if (g_enemy[enemynum].fCurPosX < (LIMIT_LEFT + LIMIT_RIGHT) / 2)
			nDirectX = -1;
		else
			nDirectX = 1;
		if (g_enemy[enemynum].fCurPosY < (LIMIT_TOP + LIMIT_BOTTOM) / 2)
			nDirectY = -1;
		else
			nDirectY = 1;
		g_enemy[enemynum].fCurPosX += nDirectX * 0.25f;
		g_enemy[enemynum].fCurPosY += nDirectY * 0.25f;
	}

	if (g_enemy[enemynum].nExistTime % 200 == 50)
		CreateEnemyShot(enemynum, 2);
}

///////////////////////////////////////////
//	pattern6	左から右へ
///////////////////////////////////////////
void EnemyPattern6(int enemynum)
{
	g_enemy[enemynum].fCurPosX += 1.0f;
	if (g_enemy[enemynum].nExistTime % 150 == 50)
		CreateEnemyShot(enemynum, 1);
}

//////////////////////////////////////////
//	pattern7	右から左へ
//////////////////////////////////////////
void EnemyPattern7(int enemynum)
{
	g_enemy[enemynum].fCurPosX -= 1.0f;
	if (g_enemy[enemynum].nExistTime % 150 == 50)
		CreateEnemyShot(enemynum, 1);
}

bool ChkColEnemyAndPlayer(int enemynum)
{
	PLAYER *pPlayer = GetPlayer();
	float fDistanceX, fDistanceY;
	int nSumHeight, nSumWidth;

	if (pPlayer->bExist == false)
		return false;
	if (pPlayer->nInvincible > 0)
		return false;

	//----- 矩形同士の当たり判定 -----
	fDistanceY = fabs(pPlayer->fCurPosY - g_enemy[enemynum].fCurPosY);
	nSumHeight = (pPlayer->drObject->nHeight + g_enemy[enemynum].nHeight) / 2;
	fDistanceX = fabs(pPlayer->fCurPosX - g_enemy[enemynum].fCurPosX);
	nSumWidth = (pPlayer->drObject->nWidth + g_enemy[enemynum].nWidth) / 2;

	if (fDistanceY < nSumHeight && fDistanceX < nSumWidth)
		return true;
	return false;
}

ENEMY *GetEnemy(void)
{
	return g_enemy;
}

void SetPlayMode(PLAY_MODE mode)
{
	g_playmode = mode;
}

void UnInitEnemy(void)
{
	int i;
	for (i = 0; i < MAX_ENEMY_TYPE; i++)
		UnInitDrawObject(&g_DrObjEnemyPict[i]);
}