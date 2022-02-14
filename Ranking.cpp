//Ranking.cpp

//===== インクルード部 ====-
#include"Ranking.h"
#include"Score.h"
#include"Bmp.h"
#include"Console.h"
#include"GameManager.h"
#include"main.h"
#include<stdio.h>

//===== 定数定義 =====
#define RANKING_TENPLATE_PIC	"BMP/rankingtempla.bmp"
#define NUM_LIST_PIC			"BMP/ResultScore.bmp"
#define CHAR_TABLE_PIC			"BMP/CharTable.bmp"
#define NUM_WIDTH		(10)
#define CHAR_WIDTH		(10)
#define MAX_RANK	(5)

typedef enum
{
	ZERO,
	FIRST,
	SECOND,
	THIRD,
	FORTH,
	FIFTH,
}RANK;

//===== 構造体宣言 =====
typedef struct
{
	int anCharNum[MAX_NAME];
	int anDispScore[SCORE_DIGIT];
}CONV_SCORE;

//===== グローバル変数 =====
DRAW_OBJECT DrObjTemplate;
DRAW_OBJECT DrObjCharTable;
DRAW_OBJECT DrObjNumList;
CONV_SCORE g_CS[MAX_RANK];
float g_DispPosY;

void InitRanking(void)
{
	char szTemplateFile[] = { RANKING_TENPLATE_PIC };
	char szNumListFile[] = { NUM_LIST_PIC };
	char szCharTable[] = { CHAR_TABLE_PIC };
	FILE *fp;
	errno_t error;
	SCORE sScore[MAX_RANK];
	int i, j;
	int cnt;
	int work;

	memset(sScore, -1, sizeof(sScore));
	ZeroMemory(g_CS, sizeof(g_CS));

	ReadBmp(szTemplateFile, &DrObjTemplate);
	ReadBmp(szNumListFile, &DrObjNumList);
	ReadBmp(szCharTable, &DrObjCharTable);

	DrObjTemplate.fCurPosX = (LIMIT_LEFT + LIMIT_RIGHT) / 2.2;
	DrObjTemplate.fCurPosY = LIMIT_BOTTOM * 2;
	g_DispPosY = DrObjTemplate.fCurPosY - DrObjTemplate.nHeight / 3.3;

	//----- ランキングファイル読み込み -----
	if (error = fopen_s(&fp, RANKING_FILE, "r") != 0)
	{
		printf("Error:ファイルを開けません:%s", RANKING_FILE);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}
	else
	{
		for (i = 0, cnt = 0; i < MAX_RANK && fscanf(fp, " %[^,],%d", sScore[i].szName, &sScore[i].nScore) != EOF; i++, cnt++);	//","を含めず読み込む　\nよけるために頭に" "スペース
	}

	fclose(fp);

	//----- 画面に表示できるように変換 -----
	for (i = 0; i < cnt; i++)
	{
		for (j = 0; j < MAX_NAME; j++)
		{
			switch (sScore[i].szName[j])
			{
			case 'A':
				g_CS[i].anCharNum[j] = 0;
				break;
			case 'B':
				g_CS[i].anCharNum[j] = 1;
				break;
			case 'C':
				g_CS[i].anCharNum[j] = 2;
				break;
			case 'D':
				g_CS[i].anCharNum[j] = 3;
				break;
			case 'E':
				g_CS[i].anCharNum[j] = 4;
				break;
			case 'F':
				g_CS[i].anCharNum[j] = 5;
				break;
			case 'G':
				g_CS[i].anCharNum[j] = 6;
				break;
			case 'H':
				g_CS[i].anCharNum[j] = 7;
				break;
			case 'I':
				g_CS[i].anCharNum[j] = 8;
				break;
			case 'J':
				g_CS[i].anCharNum[j] = 9;
				break;
			case 'K':
				g_CS[i].anCharNum[j] = 10;
				break;
			case 'L':
				g_CS[i].anCharNum[j] = 11;
				break;
			case 'M':
				g_CS[i].anCharNum[j] = 12;
				break;
			case 'N':
				g_CS[i].anCharNum[j] = 13;
				break;
			case 'O':
				g_CS[i].anCharNum[j] = 14;
				break;
			case 'P':
				g_CS[i].anCharNum[j] = 15;
				break;
			case 'Q':
				g_CS[i].anCharNum[j] = 16;
				break;
			case 'R':
				g_CS[i].anCharNum[j] = 17;
				break;
			case 'S':
				g_CS[i].anCharNum[j] = 18;
				break;
			case 'T':
				g_CS[i].anCharNum[j] = 19;
				break;
			case 'U':
				g_CS[i].anCharNum[j] = 20;
				break;
			case 'V':
				g_CS[i].anCharNum[j] = 21;
				break;
			case 'W':
				g_CS[i].anCharNum[j] = 22;
				break;
			case 'X':
				g_CS[i].anCharNum[j] = 23;
				break;
			case 'Y':
				g_CS[i].anCharNum[j] = 24;
				break;
			case 'Z':
				g_CS[i].anCharNum[j] = 25;
				break;
			default:
				break;
			}

		}
		work = sScore[i].nScore;
		for (j = 0; j < SCORE_DIGIT && work>0; j++)
		{
			g_CS[i].anDispScore[SCORE_DIGIT - 1 - j] = work % 10;
			work /= 10;
		}
	}

}

void UpdRanking(void)
{
	if (DrObjTemplate.fCurPosY > LIMIT_BOTTOM / 2)
		DrObjTemplate.fCurPosY--;

	if (g_DispPosY > 41 )
		g_DispPosY--;

	if (GetKeyState(VK_RETURN) & 0x80)
	{
		UnInit();
		SetMode(MODE_TITLE);
		Init();
	}
}

void DrawRanking(void)
{
	int i, j;

	AddObjectToBuf(&DrObjTemplate);

	for (i = 0; i < MAX_RANK; i++)
	{
		DrObjCharTable.pos.fY = DrObjNumList.pos.fY = g_DispPosY + i * 26;
		
		//----- 名前表示 -----
		for (j = 0; j < MAX_NAME; j++)
		{
			DrObjCharTable.pos.fX = (LIMIT_LEFT + LIMIT_RIGHT) / 2.5 + j * CHAR_WIDTH * 2;
			CutObjectAndAddToBuf(&DrObjCharTable, g_CS[i].anCharNum[j] * CHAR_WIDTH, g_CS[i].anCharNum[j] * CHAR_WIDTH + CHAR_WIDTH);
		}

		//----- スコア表示 -----
		for (j = 0; j < SCORE_DIGIT; j++)
		{
			DrObjNumList.pos.fX = (LIMIT_LEFT + LIMIT_RIGHT) /1.8 + j * NUM_WIDTH * 2;
			CutObjectAndAddToBuf(&DrObjNumList, g_CS[i].anDispScore[j] * NUM_WIDTH, g_CS[i].anDispScore[j] * NUM_WIDTH + NUM_WIDTH);
		}
	}
}

void UnInitRanking(void)
{
	UnInitDrawObject(&DrObjTemplate);
	UnInitDrawObject(&DrObjCharTable);
	UnInitDrawObject(&DrObjNumList);
}