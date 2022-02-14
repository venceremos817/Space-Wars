//Console.cpp

//===== インクルード部 =====
#include"Console.h"
#include"Bmp.h"
#include"Player.h"
#include<Windows.h>	
#include<stdio.h>

//===== 定数定義 =====
#define	TRANSMISSION	(0x00)	//透過色	0x00 = 黒



//===== グローバル変数 =====
CONSOLE console;
//CHAR_INFO PreCell[SCREEN_HEIGHT][SCREEN_WIDTH];	//ダブルバッファ？用

void InitConsole(void)
{
	console.handle = GetStdHandle(STD_OUTPUT_HANDLE);		//標準のコンソールハンドル取得
	console.BufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };	//裏バッファのサイズ
	console.StartPos = { 0,0 };								//裏バッファの左上隅				
	console.sr = { 0,0,SCREEN_WIDTH - 1,SCREEN_HEIGHT - 1 };//書き込み先の座標
	ZeroMemory(console.cell, sizeof(console.cell));			//セルの情報をすべて0初期化	(-1とかのほうがいいかも？)
	//ZeroMemory(PreCell, sizeof(console.cell));
}

//裏バッファに保存されている絵を一気にコンソールへ描画する(ちらつきの防止になるはず)
void DrawBuf(void)
{
	//裏バッファをコンソールに描画
	WriteConsoleOutput(console.handle, (CHAR_INFO*)console.cell, console.BufferSize, console.StartPos, &console.sr);

	//memcpy(PreCell, console.cell, sizeof(console.cell));	

	//裏バッファのセル情報をクリア
	ZeroMemory(console.cell, sizeof(console.cell));
}

void InitDrawObject(DRAW_OBJECT *object, int height, int width)
{
	object->pos.fX = 0;
	object->pos.fY = 0;
	object->nHeight = height;
	object->nWidth = width;
	//object->bExist = true;
	//object->fCurPosX = object->fPrePosX = object->pos.fX + object->nWidth / 2.0f;
	//object->fCurPosY = object->fPrePosY = object->pos.fY + object->nHeight / 2.0f;


	object->pCell = (CHAR_INFO *)malloc(sizeof(CHAR_INFO) * object->nHeight * object->nWidth);
	//コンソールサイズに合わせた領域を確保
	ZeroMemory(object->pCell, sizeof(object->pCell));	//0初期化(-1とかのほうがいい？)


	//ここでBMPを読み込んでcellに格納したい
}


//裏バッファにオブジェクトを描画
void AddObjectToBuf(DRAW_OBJECT *object)
{
	int w, h;
	//CHAR_INFO *pict;

	//pict = object->pCell;
	object->pos.fX = object->fCurPosX - object->nWidth / 2.0f;
	object->pos.fY = object->fCurPosY - object->nHeight / 2.0f;


	for (w = 0; w < object->nWidth; w++)
	{
		for (h = 0; h < object->nHeight; h++)
		{
			//if (object->pCell[h * object->nWidth + w].Char.AsciiChar != 0)
			if (object->pCell[h*object->nWidth + w].Attributes == TRANSMISSION)		continue;	//透過
			if ((int)(object->pos.fY + h) < 0 || (int)(object->pos.fY + h) > SCREEN_HEIGHT)	continue;	//バッファより外なら格納しない
			if ((int)(object->pos.fX + w) < 0 || (int)(object->pos.fX + w) > SCREEN_WIDTH)	continue;

			if (console.cell[(int)(object->pos.fY + h)][(int)(object->pos.fX + w)].Attributes == object->pCell[(int)(h * object->nWidth + w)].Attributes)	continue;
			console.cell[(int)(object->pos.fY + h)][(int)(object->pos.fX + w)] = object->pCell[(int)(h * object->nWidth + w)];
		}
	}
}

void NoChangePosAddObjectToBuf(DRAW_OBJECT *object)
{
	int w, h;

	for (w = 0; w < object->nWidth; w++)
	{
		for (h = 0; h < object->nHeight; h++)
		{
			if (object->pCell[h*object->nWidth + w].Attributes == TRANSMISSION)				continue;	//透過
			if ((int)(object->pos.fY + h) < 0 || (int)(object->pos.fY + h) > SCREEN_HEIGHT)	continue;	//バッファより外なら格納しない
			if ((int)(object->pos.fX + w) < 0 || (int)(object->pos.fX + w) > SCREEN_WIDTH)	continue;

			if (console.cell[(int)(object->pos.fY + h)][(int)(object->pos.fX + w)].Attributes == object->pCell[(int)(h * object->nWidth + w)].Attributes)	continue;
			console.cell[(int)(object->pos.fY + h)][(int)(object->pos.fX + w)] = object->pCell[(int)(h * object->nWidth + w)];
		}
	}
}

void CutObjectAndAddToBuf(DRAW_OBJECT *object, int start, int end)
{
	int w, h;
	int x;

	for (w = start * 2, x = 0; w < end * 2; w++, x++)
	{
		for (h = 0; h < object->nHeight; h++)
		{
			if (object->pCell[(int)(h*object->nWidth + w)].Attributes == TRANSMISSION)		continue;	 //透過
			if ((int)(object->pos.fY + h) < 0 || (int)(object->pos.fY + h) > SCREEN_HEIGHT)	continue;	//バッファより外なら格納しない
			if ((int)(object->pos.fX + x) < 0 || (int)(object->pos.fX + x) > SCREEN_WIDTH)	continue;

			if (console.cell[(int)(object->pos.fY + h)][(int)(object->pos.fX + w)].Attributes == object->pCell[(int)(h * object->nWidth + w)].Attributes)	continue;
			console.cell[(int)(object->pos.fY + h)][(int)(object->pos.fX + x)] = object->pCell[(int)(h * object->nWidth + w)];
		}
	}
}

void SetObjectChar(DRAW_OBJECT * obj, const char * c)
{
	int x = 0;
	int y = 0;
	for (int n = 0; c[n] != '\0'; n++)
	{
		if (c[n] == '\n')
		{
			++y;
			x = 0;
		}
		else
		{
		//	obj->pCell_[(int)obj->position_.y + y][(int)obj->position_.x + x].Char.AsciiChar = c[n];
			obj->pCell[(int)obj->nWidth * y + (int)obj->pos.fX + x].Char.AsciiChar = c[n];
			++x;
		}
	}
}

void SetObjectFGColor(DRAW_OBJECT * obj, const char * c)
{
	int x = 0;
	int y = 0;
	int fg = 0;
	for (int n = 0; c[n] != '\0'; n++)
	{
		if (c[n] == '\n')
		{
			++y;
			x = 0;
		}
		else
		{
			if (c[n] >= 'a' && c[n] <= 'f')
			{
				//10 ~ 16に
				fg = c[n] - 87;
			}
			else if (c[n] >= 'A' && c[n] <= 'F')
			{
				//10 ~ 16に
				fg = c[n] - 55;
			}
			else if (c[n] >= '0' && c[n] <= '9')
			{
				//0 ~ 9に
				fg = c[n] - 48;
			}
			else
			{
				//それ以外の場合は色を変更しない
				++x;
				continue;
			}
			obj->pCell[(int)obj->nWidth * y + (int)obj->pos.fX + x].Attributes -= obj->pCell[(int)obj->nWidth * y + (int)obj->pos.fX + x].Attributes % 16;
			obj->pCell[(int)obj->nWidth * y + (int)obj->pos.fX + x].Attributes += fg;
			++x;
		}
	}
}

void SetObjectBGColor(DRAW_OBJECT * obj, const char * c)
{
	int x = 0;
	int y = 0;
	int bg = 0;
	for (int n = 0; c[n] != '\0'; n++)
	{
		if (c[n] == '\n')
		{
			++y;
			x = 0;
		}
		else
		{
			if (c[n] >= 'a' && c[n] <= 'f')
			{
				//10 ~ 16に
				bg = c[n] - 87;
			}
			else if (c[n] >= 'A' && c[n] <= 'F')
			{
				//10 ~ 16に
				bg = c[n] - 55;
			}
			else if (c[n] >= '0' && c[n] <= '9')
			{
				//0 ~ 9に
				bg = c[n] - 48;
			}
			else
			{
				//それ以外の場合は色を変更しない
				++x;
				continue;
			}
			obj->pCell[(int)obj->nWidth * y + (int)obj->pos.fX + x].Attributes = obj->pCell[(int)obj->nWidth * y + (int)obj->pos.fX + x].Attributes % 16;
			obj->pCell[(int)obj->nWidth * y + (int)obj->pos.fX + x].Attributes += bg * 16;
			++x;
		}
	}
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void UnInitDrawObject(DRAW_OBJECT *object)
{
	//int i;
	//メモリ解放
	//for (i = 0; i < object->nHeight; i++)
	//{
	//	free(&object->pCell[i]);
	//}
	free(object->pCell);
}