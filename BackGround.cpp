//BackGround.cpp

//===== インクルード部 =====
#include"BackGround.h"
#include"GameManager.h"
#include"Bmp.h"
#include"Console.h"


//===== 定数・マクロ定義 =====
#define	MAX_STAR			(30)
#define STAR_PIC			"BMP/star.bmp"
#define STAR_TYPE			(2)
#define	LIMIT_RAND(a,b)		(a + (float)rand() * (b - a + 1.0) / (1.0 + RAND_MAX))		// a～b の範囲で乱数を生成
#define STAR_MIN_SPD		(1)
#define	STAR_MAX_SPD		(3)

//===== 構造体宣言 =====
typedef struct
{
	float fX;
	float fY;
	float fMoveSpd;
	int nType;
	int nTime;
	bool bExist;
}STAR;


//===== プロトタイプ宣言 =====
void InitStar(void);
void CreateStar(void);
void UpdStar(void);
void DrawStar(void);


//===== グローバル変数 =====
STAR g_star[MAX_STAR];
DRAW_OBJECT	g_DrObjStar;


void InitBackGround(void)
{
	InitStar();
}

void UpdBackGround(void)
{
	UpdStar();
}

void DrawBackGround(void)
{
	DrawStar();
}

//---------------------------------- STAR -----------------------------

void InitStar(void)
{
	int i;
	char starFile[] = { STAR_PIC };

	ReadBmp(starFile, &g_DrObjStar);

	for (i = 0; i < MAX_STAR; i++)
	{
		g_star[i].bExist = false;
	}
}

void CreateStar(void)
{
	int i;

	for (i = 0; i < MAX_STAR; i++)
	{
		if (g_star[i].bExist == true)	continue;

		g_star[i].bExist = true;
		g_star[i].fY = LIMIT_TOP;
		g_star[i].fX = LIMIT_RAND(LIMIT_LEFT, LIMIT_RIGHT);
		g_star[i].fMoveSpd = LIMIT_RAND(STAR_MIN_SPD, STAR_MAX_SPD) / 20;
		g_star[i].nType = 0;
		g_star[i].nTime = 0;

		break;
	}
}

void UpdStar(void)
{
	int i;

	for (i = 0; i < MAX_STAR; i++)
	{
		if (g_star[i].bExist == false)	continue;

		g_star[i].fY += g_star[i].fMoveSpd;
		g_star[i].nTime++;
		if (g_star[i].nTime < 100)
		{
			g_star[i].nType = 0;
		}
		else if (g_star[i].nTime < 200)
		{
			g_star[i].nType = 1;
		}
		else
		{
			g_star[i].nTime = 0;
		}
		//----- 画面外に行ったとき
		if (g_star[i].fY > LIMIT_BOTTOM)
			g_star[i].bExist = false;


	}
	if (rand() % 100 == 0)
		CreateStar();
}

void DrawStar(void)
{
	int i;

	for (i = 0; i < MAX_STAR; i++)
	{
		if (g_star[i].bExist == false)	continue;

		g_DrObjStar.pos.fX = g_star[i].fX;
		g_DrObjStar.pos.fY = g_star[i].fY;


		CutObjectAndAddToBuf(&g_DrObjStar, g_star[i].nType * 4, g_star[i].nType * 4 + 3);
	}
}

void UnInitBackGround(void)
{
	UnInitDrawObject(&g_DrObjStar);
}