//Score.cpp


//===== インクルード部 =====
#include"Score.h"
#include"Console.h"
#include"Bmp.h"
#include"GameManager.h"

//===== 定数定義 =====
#define NUMBERS_PIC	"BMP/numbers.bmp"
#define SCORE_PIC	"BMP/SCORE.bmp"
#define NUM_WIDTH	(5)

//===== 列挙型 =====
typedef enum
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	MAX_NUM
}NUMBERS;



//===== グローバル変数 =====
int g_Score;
DRAW_OBJECT DrObjNumbers;
DRAW_OBJECT DrObjSCORE;


void InitScore(void)
{
	g_Score = 0;
	char NumbersFilen[30] = { NUMBERS_PIC };
	char ScoreFile[30] = { SCORE_PIC };

	ReadBmp(ScoreFile, &DrObjSCORE);
	ReadBmp(NumbersFilen, &DrObjNumbers);

	DrObjSCORE.fCurPosX = (float)(LIMIT_LEFT + DrObjSCORE.nWidth / 2 +2);
	DrObjSCORE.fCurPosY = (float)(LIMIT_TOP + DrObjSCORE.nHeight / 2);
	DrObjNumbers.pos.fY = LIMIT_TOP;
}


int GetScore(void)
{
	return g_Score;
}

void SetScore(int score)
{
	g_Score = score;
}

void AddScore(int add)
{
	g_Score += add;
}

//void UpdScore(void)
//{
//	int i;
//	int work;
//
//
//}

void DrawScore(void)
{
	int i;
	int work;
	int aDispScore[SCORE_DIGIT] = {};	//全要素 0 初期化

	AddObjectToBuf(&DrObjSCORE);

	work = g_Score;
	for (i = 0; work > 0 && i < SCORE_DIGIT; i++)
	{
		aDispScore[SCORE_DIGIT - 1 - i] = work % 10;
		work /= 10;
	}

	for (i = 0; i < SCORE_DIGIT; i++)
	{
		DrObjNumbers.pos.fX = DrObjSCORE.pos.fX + DrObjSCORE.nWidth + i * NUM_WIDTH * 2 + 1;
		CutObjectAndAddToBuf(&DrObjNumbers, aDispScore[i] * NUM_WIDTH, aDispScore[i] * NUM_WIDTH + NUM_WIDTH);
	}

}

void UnInitScore(void)
{
	//UnInitDrawObject(&DrObjNumbers);
//	UnInitDrawObject(&DrObjSCORE);
}