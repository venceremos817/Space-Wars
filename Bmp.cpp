////////////////////////////////////////
//
//
//～～～ 更新履歴 ～～～
//2020/02/02	製作開始
//2020/02/03	ファイルのヘッダ情報から各ピクセルのRGB情報を格納する配列作成
//				RGB情報を格納
//				
////////////////////////////////////////


//===== インクルード部 =====
#include"Bmp.h"
#include"Console.h"
#include"Player.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

//===== 定数定義 =====




//===== プロトタイプ宣言 =====
void ReadRGBdata(FILE *, RGB **, int, int);
void SetObjectBmp(RGB **Rgb, DRAW_OBJECT *);


void ReadBmp(char *filename,DRAW_OBJECT *object)
{
	FILE *fp;
	BMP_INFO bmpInfo;
	RGB **pRgb;		//RGB情報を2次元配列で格納したいが、配列を動的に確保するためダブルポインタを利用する
	int i, j;	//ループ用
	errno_t error;

	if ((error = fopen_s(&fp, filename, "rb") != 0))
	{
		printf("Error:ファイルを開けません %s", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}

	//ファイルタイプを読み込む
	if (fread(&bmpInfo.ushType, sizeof(unsigned short), 1, fp) != 1)
	{
		fclose(fp);
		printf("Error:ファイルを読み込めません %s", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}
	//ファイルタイプがBMでなければ失敗
	if (bmpInfo.ushType != FILETYPE_BM)
	{
		fclose(fp);
		printf("Error:%sはbitmapファイルではありません", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}

	
	//画像データまでのオフセット取得	基本的にオフセット(54)から画像データとわかっているため不要
	//fseek(fp, 10, SEEK_SET);	//オフセット(10)に画像データまでの情報がある
	//if (fread(&bmpInfo.dwOffBits, sizeof(unsigned long), 1, fp) != 1)
	//{
	//	fclose(fp);
	//	printf("Error:ファイルを読み込めません %s", filename);
	//	rewind(stdin);	getchar();
	//	exit(EXIT_FAILURE);
	//}


	//BMPの横ピクセル数取得
	fseek(fp, 18, SEEK_SET);	//オフセット(18)に画像の幅情報がある
	if (fread(&bmpInfo.nWidth, sizeof(int), 1, fp) != 1)
	{// 失敗したらError処理
		fclose(fp);
		printf("Error:ファイルを読み込めません %s", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}

	

	//BMPの縦ピクセル数取得
	if (fread(&bmpInfo.nHeight, sizeof(int), 1, fp) != 1)
	{
		fclose(fp);
		printf("Error:ファイルを読み込めません %s", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}



	//色ビット数を取得
	fseek(fp, 28, SEEK_SET);
	if (fread(&bmpInfo.wBitCount, sizeof(unsigned int), 1, fp) != 1)
	{
		fclose(fp);
		printf("Error:ファイルを読み込めません %s", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}
	if (bmpInfo.wBitCount != 24)	//色数24しか取り扱わない
	{
		fclose(fp);
		printf("Error:%s は対応していません", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}



	//RGB情報を格納する 縦ピクセル数 * 横ピクセル数 の２次元配列を動的に確保する
	pRgb = (RGB **)malloc(sizeof(RGB *) * bmpInfo.nHeight);	//縦ピクセル個のポインタを格納するためのメモリ領域を確保
	if (pRgb == NULL)
	{//	メモリの確保に失敗したらError処理
		fclose(fp);
		printf("メモリの確保に失敗しました");
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < bmpInfo.nHeight; i++)	//横ピクセル個のデータ配列のためのメモリ領域を確保し、それへのポインタをpRgbの各要素に格納
	{
		pRgb[i] = (RGB *)malloc(sizeof(RGB *) * bmpInfo.nWidth);
		if (pRgb[i] == NULL)
		{
			fclose(fp);
			for (j = 0; j < i; j++)		//メモリ解放
			{
				free(pRgb[i]);
			}
			free(pRgb);
			printf("メモリの確保に失敗しました");
			rewind(stdin);	getchar();
			exit(EXIT_FAILURE);
		}

	}


	//画像RGB情報読み込み
	//fseek(fp, bmpInfo.dwOffBits, SEEK_SET);		//RGB情報はオフセット(54)から始まることが既知のため不要
	fseek(fp, 54, SEEK_SET);	//RGB情報はオフセット(54)から始まる
	ReadRGBdata(fp, pRgb, bmpInfo.nHeight, bmpInfo.nWidth);

	//ファイルクローズ
	fclose(fp);

	//画像の縦幅、横幅
	object->nHeight = bmpInfo.nHeight;
	object->nWidth = bmpInfo.nWidth * 2;	//横要素は2charで表現するため
	
	//画像サイズ分のメモリ確保
	object->pCell = (CHAR_INFO *)malloc(sizeof(CHAR_INFO) * object->nHeight * object->nWidth);
	if (object->pCell == NULL)
	{
		printf("Error:メモリの確保に失敗しました");
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}
	
	//RGB情報を色(16色)として変換する
	SetObjectBmp(pRgb, object);

	//メモリ解放
	for (i = 0; i < bmpInfo.nHeight; i++)
	{
		free(pRgb[i]);
	}
	free(pRgb);

}

void ReadRGBdata(FILE *fp, RGB **pRgb, int height, int width)
{
	int i, j, error;

	for (i = height - 1; i >= 0; i--)
	{
		for (j = 0; j < width; j++)
		{
			error = ftell(fp);
			if (fread(&pRgb[i][j].b, 1, 1, fp) != 1)	//Blue要素読み込み
			{//	失敗したらError処理
				fclose(fp);
				printf("Error:ファイルを読み込めません B");
				printf("%d\n", error);
				rewind(stdin);	getchar();
				exit(EXIT_FAILURE);
			}
			error = ftell(fp);
			if (fread(&pRgb[i][j].g, 1, 1, fp) != 1)	//Green要素読み込み
			{
				fclose(fp);
				printf("Error:ファイルを読み込めません G");
				printf("%d\n", error);
				rewind(stdin);	getchar();
				exit(EXIT_FAILURE);
			}
			error = ftell(fp);
			if (fread(&pRgb[i][j].r, 1, 1, fp) != 1)	//Red要素読み込み
			{
				fclose(fp);
				printf("Error:ファイルを読み込めません R");
				printf("%d\n", error);
				rewind(stdin);	getchar();
				exit(EXIT_FAILURE);
			}
		}
		fseek(fp, width % 4, SEEK_CUR);		//RGB情報は1行4Byte区切りで保存されているため、次の行に行くときは揃える
	}
}

void SetObjectBmp(RGB **Rgb, DRAW_OBJECT *object)
{
	int w, h;
	unsigned int r, g, b;
	unsigned char color;
	CHAR_INFO *pPict;

	pPict = object->pCell;

	for (h = 0; h < object->nHeight; h++)
	{
		for (w = 0; w < object->nWidth / 2; w++, pPict++)		//width / 2 ?
		{
			r = Rgb[h][w].r;
			g = Rgb[h][w].g;
			b = Rgb[h][w].b;

			//RGB情報を16色に振り分け
			if (r >= COLOUR_HI)							r = 2;
			else if (r < COLOUR_HI && r >= COLOUR_LOW)	r = 1;
			else										r = 0;

			if (g >= COLOUR_HI)							g = 2;
			else if (g < COLOUR_HI && g >= COLOUR_LOW)	g = 1;
			else										g = 0;

			if (b >= COLOUR_HI)							b = 2;
			else if (b < COLOUR_HI && b >= COLOUR_LOW)	b = 1;
			else										b = 0;

			if (r == 0 && g == 0 && b == 0)			color = 0;
			else if (r == 0 && g == 0 && b == 1)	color = 1;
			else if (r == 0 && g == 1 && b == 0)	color = 2;
			else if (r == 0 && g == 1 && b == 1)	color = 3;
			else if (r == 1 && g == 0 && b == 0)	color = 4;
			else if (r == 1 && g == 0 && b == 1)	color = 5;
			else if (r == 1 && g == 1 && b == 0)	color = 6;
			else if (r == 1 && g == 1 && b == 1)	color = 8;
			else if (r < 2 && g < 2 && b == 2)		color = 9;
			else if (r < 2 && g == 2 && b < 2)		color = 10;
			else if (r < 2 && g == 2 && b == 2)		color = 11;
			else if (r == 2 && g < 2 && b < 2)		color = 12;
			else if (r == 2 && g < 2 && b == 2)		color = 13;
			else if (r == 2 && g == 2 && b < 2)		color = 14;
			else if (r == 2 && g == 2 && b == 2)	color = 15;

			//printf("[%d]", h * object->nWidth + w);
			//printf("R:%d,G:%d,B:%d  Clr:%d\n", r, g, b,color);


			//object->pCell[h * object->nWidth + w].Attributes = color * 16;
			//object->pCell[h * object->nWidth + w].Char.AsciiChar = ' ';
			//object->pCell++;
			//object->pCell[h * object->nWidth + w].Attributes = color * 16;
			//object->pCell[h * object->nWidth + w].Char.AsciiChar = ' ';
			pPict->Attributes = color * 16;
			pPict->Char.AsciiChar = ' ';
			pPict++;
			pPict->Attributes = color * 16;
			pPict->Char.AsciiChar = ' ';

			//getchar();
		}
	}

}