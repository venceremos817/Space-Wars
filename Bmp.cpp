////////////////////////////////////////
//
//
//�`�`�` �X�V���� �`�`�`
//2020/02/02	����J�n
//2020/02/03	�t�@�C���̃w�b�_��񂩂�e�s�N�Z����RGB�����i�[����z��쐬
//				RGB�����i�[
//				
////////////////////////////////////////


//===== �C���N���[�h�� =====
#include"Bmp.h"
#include"Console.h"
#include"Player.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

//===== �萔��` =====




//===== �v���g�^�C�v�錾 =====
void ReadRGBdata(FILE *, RGB **, int, int);
void SetObjectBmp(RGB **Rgb, DRAW_OBJECT *);


void ReadBmp(char *filename,DRAW_OBJECT *object)
{
	FILE *fp;
	BMP_INFO bmpInfo;
	RGB **pRgb;		//RGB����2�����z��Ŋi�[���������A�z��𓮓I�Ɋm�ۂ��邽�߃_�u���|�C���^�𗘗p����
	int i, j;	//���[�v�p
	errno_t error;

	if ((error = fopen_s(&fp, filename, "rb") != 0))
	{
		printf("Error:�t�@�C�����J���܂��� %s", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}

	//�t�@�C���^�C�v��ǂݍ���
	if (fread(&bmpInfo.ushType, sizeof(unsigned short), 1, fp) != 1)
	{
		fclose(fp);
		printf("Error:�t�@�C����ǂݍ��߂܂��� %s", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}
	//�t�@�C���^�C�v��BM�łȂ���Ύ��s
	if (bmpInfo.ushType != FILETYPE_BM)
	{
		fclose(fp);
		printf("Error:%s��bitmap�t�@�C���ł͂���܂���", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}

	
	//�摜�f�[�^�܂ł̃I�t�Z�b�g�擾	��{�I�ɃI�t�Z�b�g(54)����摜�f�[�^�Ƃ킩���Ă��邽�ߕs�v
	//fseek(fp, 10, SEEK_SET);	//�I�t�Z�b�g(10)�ɉ摜�f�[�^�܂ł̏�񂪂���
	//if (fread(&bmpInfo.dwOffBits, sizeof(unsigned long), 1, fp) != 1)
	//{
	//	fclose(fp);
	//	printf("Error:�t�@�C����ǂݍ��߂܂��� %s", filename);
	//	rewind(stdin);	getchar();
	//	exit(EXIT_FAILURE);
	//}


	//BMP�̉��s�N�Z�����擾
	fseek(fp, 18, SEEK_SET);	//�I�t�Z�b�g(18)�ɉ摜�̕���񂪂���
	if (fread(&bmpInfo.nWidth, sizeof(int), 1, fp) != 1)
	{// ���s������Error����
		fclose(fp);
		printf("Error:�t�@�C����ǂݍ��߂܂��� %s", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}

	

	//BMP�̏c�s�N�Z�����擾
	if (fread(&bmpInfo.nHeight, sizeof(int), 1, fp) != 1)
	{
		fclose(fp);
		printf("Error:�t�@�C����ǂݍ��߂܂��� %s", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}



	//�F�r�b�g�����擾
	fseek(fp, 28, SEEK_SET);
	if (fread(&bmpInfo.wBitCount, sizeof(unsigned int), 1, fp) != 1)
	{
		fclose(fp);
		printf("Error:�t�@�C����ǂݍ��߂܂��� %s", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}
	if (bmpInfo.wBitCount != 24)	//�F��24������舵��Ȃ�
	{
		fclose(fp);
		printf("Error:%s �͑Ή����Ă��܂���", filename);
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}



	//RGB�����i�[���� �c�s�N�Z���� * ���s�N�Z���� �̂Q�����z��𓮓I�Ɋm�ۂ���
	pRgb = (RGB **)malloc(sizeof(RGB *) * bmpInfo.nHeight);	//�c�s�N�Z���̃|�C���^���i�[���邽�߂̃������̈���m��
	if (pRgb == NULL)
	{//	�������̊m�ۂɎ��s������Error����
		fclose(fp);
		printf("�������̊m�ۂɎ��s���܂���");
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < bmpInfo.nHeight; i++)	//���s�N�Z���̃f�[�^�z��̂��߂̃������̈���m�ۂ��A����ւ̃|�C���^��pRgb�̊e�v�f�Ɋi�[
	{
		pRgb[i] = (RGB *)malloc(sizeof(RGB *) * bmpInfo.nWidth);
		if (pRgb[i] == NULL)
		{
			fclose(fp);
			for (j = 0; j < i; j++)		//���������
			{
				free(pRgb[i]);
			}
			free(pRgb);
			printf("�������̊m�ۂɎ��s���܂���");
			rewind(stdin);	getchar();
			exit(EXIT_FAILURE);
		}

	}


	//�摜RGB���ǂݍ���
	//fseek(fp, bmpInfo.dwOffBits, SEEK_SET);		//RGB���̓I�t�Z�b�g(54)����n�܂邱�Ƃ����m�̂��ߕs�v
	fseek(fp, 54, SEEK_SET);	//RGB���̓I�t�Z�b�g(54)����n�܂�
	ReadRGBdata(fp, pRgb, bmpInfo.nHeight, bmpInfo.nWidth);

	//�t�@�C���N���[�Y
	fclose(fp);

	//�摜�̏c���A����
	object->nHeight = bmpInfo.nHeight;
	object->nWidth = bmpInfo.nWidth * 2;	//���v�f��2char�ŕ\�����邽��
	
	//�摜�T�C�Y���̃������m��
	object->pCell = (CHAR_INFO *)malloc(sizeof(CHAR_INFO) * object->nHeight * object->nWidth);
	if (object->pCell == NULL)
	{
		printf("Error:�������̊m�ۂɎ��s���܂���");
		rewind(stdin);	getchar();
		exit(EXIT_FAILURE);
	}
	
	//RGB����F(16�F)�Ƃ��ĕϊ�����
	SetObjectBmp(pRgb, object);

	//���������
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
			if (fread(&pRgb[i][j].b, 1, 1, fp) != 1)	//Blue�v�f�ǂݍ���
			{//	���s������Error����
				fclose(fp);
				printf("Error:�t�@�C����ǂݍ��߂܂��� B");
				printf("%d\n", error);
				rewind(stdin);	getchar();
				exit(EXIT_FAILURE);
			}
			error = ftell(fp);
			if (fread(&pRgb[i][j].g, 1, 1, fp) != 1)	//Green�v�f�ǂݍ���
			{
				fclose(fp);
				printf("Error:�t�@�C����ǂݍ��߂܂��� G");
				printf("%d\n", error);
				rewind(stdin);	getchar();
				exit(EXIT_FAILURE);
			}
			error = ftell(fp);
			if (fread(&pRgb[i][j].r, 1, 1, fp) != 1)	//Red�v�f�ǂݍ���
			{
				fclose(fp);
				printf("Error:�t�@�C����ǂݍ��߂܂��� R");
				printf("%d\n", error);
				rewind(stdin);	getchar();
				exit(EXIT_FAILURE);
			}
		}
		fseek(fp, width % 4, SEEK_CUR);		//RGB����1�s4Byte��؂�ŕۑ�����Ă��邽�߁A���̍s�ɍs���Ƃ��͑�����
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

			//RGB����16�F�ɐU�蕪��
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