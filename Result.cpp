//Result.cpp


//===== インクルード部 =====
#include"Result.h"
#include"Score.h"
#include"Ranking.h"
#include"Bmp.h"
#include"Console.h"
#include"main.h"
#include"GameManager.h"
#include"Sound.h"
#include<Windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//===== 定数定義 =====
#define NUM_LIST_PIC	"BMP/ResultScore.bmp"
#define CHAR_TABLE_PIC	"BMP/CharTable.bmp"
#define NAME_CURSOR_PIC	"BMP/NameCursor.bmp"
#define	MAX_PLAYER		(100)
#define NUM_WIDTH		(10)
#define CHAR_WIDTH		(10)
#define CHAR_NUM		(26)
#define KEY_DELAY		(15)
#define CURSOR_SE		""
#define	SELECT_SE		""


//===== プロトタイプ宣言 =====
void SaveScore(void);
void SortScore(void);

//===== グローバル変数 =====
DRAW_OBJECT g_DrObjCharTable;
DRAW_OBJECT g_DrObjNumList;
DRAW_OBJECT g_DrObjCursor;
int g_aDispScore[SCORE_DIGIT] = {};
int g_aPlayerName[MAX_NAME] = {};
int g_nCursorPos;
bool bKey;
int g_KeyDelay;

void InitResult(void)
{
	int i;
	int work;
	int nScore = GetScore();

	char CharTableFile[] = { CHAR_TABLE_PIC };
	char NumListFile[] = { NUM_LIST_PIC };
	char NameCursorFile[] = { NAME_CURSOR_PIC };

	ReadBmp(CharTableFile, &g_DrObjCharTable);
	ReadBmp(NumListFile, &g_DrObjNumList);
	ReadBmp(NameCursorFile, &g_DrObjCursor);

	work = nScore;
	for (i = 0; work > 0 && i < SCORE_DIGIT; i++)
	{
		g_aDispScore[SCORE_DIGIT - 1 - i] = work % 10;
		work /= 10;
	}
	g_DrObjNumList.pos.fY = (LIMIT_BOTTOM) / 2;
	g_DrObjCharTable.pos.fY = LIMIT_BOTTOM / 2;

	g_DrObjCursor.pos.fY = g_DrObjCharTable.pos.fY - g_DrObjCursor.nHeight-1;

}

void UpdResult(void)
{

	if (GetKeyState(VK_LEFT) & 0x80)
	{
		if (bKey)
		{
			g_nCursorPos--;
			bKey = false;
			g_KeyDelay = 0;
		}
	}
	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		if (bKey)
		{
			g_nCursorPos++;
			bKey = false;
			g_KeyDelay = 0;
		}
	}

	if (g_nCursorPos < 0)
		g_nCursorPos = MAX_NAME - 1;
	g_nCursorPos %= MAX_NAME;

	if (GetKeyState(VK_UP) & 0x80)
	{
		if (bKey)
		{
			g_aPlayerName[g_nCursorPos]++;
			bKey = false;
			g_KeyDelay = 0;
		}
	}
	if (GetKeyState(VK_DOWN) & 0x80)
	{
		if (bKey)
		{
			g_aPlayerName[g_nCursorPos]--;
			bKey = false;
			g_KeyDelay = 0;
		}
	}

	if (g_KeyDelay > KEY_DELAY)
	{
		bKey = true;
		g_KeyDelay = 0;
	}
	g_KeyDelay++;

	if (g_aPlayerName[g_nCursorPos] < 0)
		g_aPlayerName[g_nCursorPos] = CHAR_NUM - 1;
	g_aPlayerName[g_nCursorPos] %= CHAR_NUM;

	if (GetKeyState(VK_RETURN) & 0x80)
	{
		SaveScore();
		UnInit();
		SetMode(MODE_TITLE);
		Init();
	}
}

void DrawResult(void)
{
	int i;

	//----- スコア表示 -----
	for (i = 0; i < SCORE_DIGIT; i++)
	{
		g_DrObjNumList.pos.fX = (LIMIT_LEFT + LIMIT_RIGHT) / 2 + i * NUM_WIDTH * 2;
		CutObjectAndAddToBuf(&g_DrObjNumList, g_aDispScore[i] * NUM_WIDTH, g_aDispScore[i] * NUM_WIDTH + NUM_WIDTH);
	}

	//----- 入力中の名前表示 -----
	for (i = 0; i < MAX_NAME; i++)
	{
		g_DrObjCharTable.pos.fX = (LIMIT_LEFT + LIMIT_RIGHT) / 4 + i * CHAR_WIDTH * 2;
		CutObjectAndAddToBuf(&g_DrObjCharTable, g_aPlayerName[i] * CHAR_WIDTH, g_aPlayerName[i] * CHAR_WIDTH + CHAR_WIDTH);
	}

	//----- カーソル表示 -----
	g_DrObjCursor.pos.fX = (LIMIT_LEFT + LIMIT_RIGHT) / 4 + g_nCursorPos * CHAR_WIDTH * 2;
	g_DrObjCursor.pos.fY = g_DrObjCharTable.pos.fY - g_DrObjCursor.nHeight - 1;
	CutObjectAndAddToBuf(&g_DrObjCursor, 0, 9);
	g_DrObjCursor.pos.fY = g_DrObjCharTable.pos.fY +g_DrObjCharTable.nHeight + 1;
	CutObjectAndAddToBuf(&g_DrObjCursor, 9, 18);
}

void SaveScore(void)
{
	char szPlayerName[10] = "\0";
	int nScore = GetScore();
	int i;
	FILE *fp;
	errno_t error;
	

	for (i = 0; i < MAX_NAME; i++)
	{
		switch (g_aPlayerName[i])
		{
		case 0:
			strcat_s(szPlayerName, "A");
			break;
		case 1:
			strcat_s(szPlayerName, "B");
			break;
		case 2:
			strcat_s(szPlayerName, "C");
			break;
		case 3:
			strcat_s(szPlayerName, "D");
			break;
		case 4:
			strcat_s(szPlayerName, "E");
			break;
		case 5:
			strcat_s(szPlayerName, "F");
			break;
		case 6:
			strcat_s(szPlayerName, "G");
			break;
		case 7:
			strcat_s(szPlayerName, "H");
			break;
		case 8:
			strcat_s(szPlayerName, "I");
			break;
		case 9:
			strcat_s(szPlayerName, "J");
			break;
		case 10:
			strcat_s(szPlayerName, "K");
			break;
		case 11:
			strcat_s(szPlayerName, "L");
			break;
		case 12:
			strcat_s(szPlayerName, "M");
			break;
		case 13:
			strcat_s(szPlayerName, "N");
			break;
		case 14:
			strcat_s(szPlayerName, "O");
			break;
		case 15:
			strcat_s(szPlayerName, "P");
			break;
		case 16:
			strcat_s(szPlayerName, "Q");
			break;
		case 17:
			strcat_s(szPlayerName, "R");
			break;
		case 18:
			strcat_s(szPlayerName, "S");
			break;
		case 19:
			strcat_s(szPlayerName, "T");
			break;
		case 20:
			strcat_s(szPlayerName, "U");
			break;
		case 21:
			strcat_s(szPlayerName, "V");
			break;
		case 22:
			strcat_s(szPlayerName, "W");
			break;
		case 23:
			strcat_s(szPlayerName, "X");
			break;
		case 24:
			strcat_s(szPlayerName, "Y");
			break;
		case 25:
			strcat_s(szPlayerName, "Z");
			break;
		default:
			break;
		}
	}
	
	if (error = fopen_s(&fp, RANKING_FILE, "a") != 0)
	{
		printf("Error:ファイルを開けません:%s", RANKING_FILE);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}

	fprintf(fp, "%s,%d", szPlayerName, nScore);
	fclose(fp);

	SortScore();
}

void SortScore(void)
{
	FILE *fp;
	errno_t error;
	SCORE Score[MAX_PLAYER];
	char szWorkName[MAX_NAME + 1] = "\0";	//一時退避用
	int nWorkScore;						//一時退避用
	int i, j;
	int cnt = 0;

	ZeroMemory(Score, sizeof(Score));
	

	//----- ファイル読み込み -----
	if (error = fopen_s(&fp, RANKING_FILE, "r") != 0)
	{
		printf("Error:ファイルを開けません:%s", RANKING_FILE);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}
	else
	{
		for (i = 0; i < MAX_PLAYER && fscanf(fp, " %[^,],%d", Score[i].szName, &Score[i].nScore) != EOF; i++, cnt++);	//","を含めず読み込む　\nよけるために頭に" "スペース
	}
	//Score[i].nScore = -1;


	fclose(fp);
	//----- 降順バブルソート -----
	for (i = 0; i < cnt-1; i++)
	{
		
		for (j = i + 1; j < cnt; j++)
		{
			if (Score[i].nScore < Score[j].nScore)
			{
				nWorkScore = Score[i].nScore;
				Score[i].nScore = Score[j].nScore;
				Score[j].nScore = nWorkScore;

				strcpy(szWorkName, Score[i].szName);
				strcpy(Score[i].szName, Score[j].szName);
				strcpy(Score[j].szName, szWorkName);
			}
		}
	}

	//----- ファイルへ書き込み -----
	if (error = fopen_s(&fp, RANKING_FILE, "w") != 0)
	{
		printf("Error:ファイルを開けません:%s", RANKING_FILE);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}


	for (i = 0; i < cnt; i++)
	{
		fprintf(fp, "%s,%d\n", Score[i].szName, Score[i].nScore);
	}

	fclose(fp);

}

void UnInitResult(void)
{

}