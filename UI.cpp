//UI.cpp


//===== インクルード部 =====
#include"Console.h"
#include"Bmp.h"
#include"Player.h"
#include"GameManager.h"

//===== 定数定義 =====
#define LEFT_PIC	"BMP/zanki.bmp"
#define NUM_PIC		"BMP/numbers.bmp"
#define NUM_WIDTH	(5)


//===== グローバル変数 =====
DRAW_OBJECT g_DrObjLeft;
DRAW_OBJECT g_DrObjNum;


void InitUI(void)
{
	char leftFile[] = LEFT_PIC;
	char numFile[] = NUM_PIC;
	ReadBmp(leftFile, &g_DrObjLeft);
	ReadBmp(numFile, &g_DrObjNum);

	g_DrObjLeft.fCurPosX = LIMIT_LEFT + g_DrObjLeft.nWidth / 2;
	g_DrObjLeft.fCurPosY = LIMIT_BOTTOM - g_DrObjLeft.nHeight / 2;
	g_DrObjNum.pos.fY = g_DrObjLeft.fCurPosY - g_DrObjNum.nHeight / 2;
	g_DrObjNum.pos.fX = g_DrObjLeft.fCurPosX + g_DrObjLeft.nWidth / 2 + 2;;
}

void DrawUI(void)
{
	PLAYER *pPlayer = GetPlayer();

	AddObjectToBuf(&g_DrObjLeft);
	CutObjectAndAddToBuf(&g_DrObjNum, pPlayer->nLeft * NUM_WIDTH, pPlayer->nLeft * NUM_WIDTH + NUM_WIDTH);
}

void UnInitUI(void)
{
	UnInitDrawObject(&g_DrObjLeft);
	UnInitDrawObject(&g_DrObjNum);
}