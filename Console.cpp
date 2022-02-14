//Console.cpp

//===== �C���N���[�h�� =====
#include"Console.h"
#include"Bmp.h"
#include"Player.h"
#include<Windows.h>	
#include<stdio.h>

//===== �萔��` =====
#define	TRANSMISSION	(0x00)	//���ߐF	0x00 = ��



//===== �O���[�o���ϐ� =====
CONSOLE console;
//CHAR_INFO PreCell[SCREEN_HEIGHT][SCREEN_WIDTH];	//�_�u���o�b�t�@�H�p

void InitConsole(void)
{
	console.handle = GetStdHandle(STD_OUTPUT_HANDLE);		//�W���̃R���\�[���n���h���擾
	console.BufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };	//���o�b�t�@�̃T�C�Y
	console.StartPos = { 0,0 };								//���o�b�t�@�̍����				
	console.sr = { 0,0,SCREEN_WIDTH - 1,SCREEN_HEIGHT - 1 };//�������ݐ�̍��W
	ZeroMemory(console.cell, sizeof(console.cell));			//�Z���̏������ׂ�0������	(-1�Ƃ��̂ق������������H)
	//ZeroMemory(PreCell, sizeof(console.cell));
}

//���o�b�t�@�ɕۑ�����Ă���G����C�ɃR���\�[���֕`�悷��(������̖h�~�ɂȂ�͂�)
void DrawBuf(void)
{
	//���o�b�t�@���R���\�[���ɕ`��
	WriteConsoleOutput(console.handle, (CHAR_INFO*)console.cell, console.BufferSize, console.StartPos, &console.sr);

	//memcpy(PreCell, console.cell, sizeof(console.cell));	

	//���o�b�t�@�̃Z�������N���A
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
	//�R���\�[���T�C�Y�ɍ��킹���̈���m��
	ZeroMemory(object->pCell, sizeof(object->pCell));	//0������(-1�Ƃ��̂ق��������H)


	//������BMP��ǂݍ����cell�Ɋi�[������
}


//���o�b�t�@�ɃI�u�W�F�N�g��`��
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
			if (object->pCell[h*object->nWidth + w].Attributes == TRANSMISSION)		continue;	//����
			if ((int)(object->pos.fY + h) < 0 || (int)(object->pos.fY + h) > SCREEN_HEIGHT)	continue;	//�o�b�t�@���O�Ȃ�i�[���Ȃ�
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
			if (object->pCell[h*object->nWidth + w].Attributes == TRANSMISSION)				continue;	//����
			if ((int)(object->pos.fY + h) < 0 || (int)(object->pos.fY + h) > SCREEN_HEIGHT)	continue;	//�o�b�t�@���O�Ȃ�i�[���Ȃ�
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
			if (object->pCell[(int)(h*object->nWidth + w)].Attributes == TRANSMISSION)		continue;	 //����
			if ((int)(object->pos.fY + h) < 0 || (int)(object->pos.fY + h) > SCREEN_HEIGHT)	continue;	//�o�b�t�@���O�Ȃ�i�[���Ȃ�
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
				//10 ~ 16��
				fg = c[n] - 87;
			}
			else if (c[n] >= 'A' && c[n] <= 'F')
			{
				//10 ~ 16��
				fg = c[n] - 55;
			}
			else if (c[n] >= '0' && c[n] <= '9')
			{
				//0 ~ 9��
				fg = c[n] - 48;
			}
			else
			{
				//����ȊO�̏ꍇ�͐F��ύX���Ȃ�
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
				//10 ~ 16��
				bg = c[n] - 87;
			}
			else if (c[n] >= 'A' && c[n] <= 'F')
			{
				//10 ~ 16��
				bg = c[n] - 55;
			}
			else if (c[n] >= '0' && c[n] <= '9')
			{
				//0 ~ 9��
				bg = c[n] - 48;
			}
			else
			{
				//����ȊO�̏ꍇ�͐F��ύX���Ȃ�
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
	//���������
	//for (i = 0; i < object->nHeight; i++)
	//{
	//	free(&object->pCell[i]);
	//}
	free(object->pCell);
}