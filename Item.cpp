//Item.cpp

//===== �C���N���[�h�� =====
#include"Item.h"
#include"Player.h"
#include"Enemy.h"
#include"Bmp.h"
#include"Console.h"
#include"Player.h"
#include"GameManager.h"
#include"Score.h"
#include"Sound.h"
#include<math.h>
#include<Windows.h>
#include<stdio.h>


//===== �萔��` =====
#define ITEM_PIC	"BMP/PItem.bmp"
#define MAX_ITEM	(3)
#define LIFE_SPAN	(3000)
#define MAX_BOUND	(10)
#define GETITEM_SE	"sound/powerup04.mp3"

//===== �v���g�^�C�v�錾 =====
void ChkColItemAndPlayer(void);


//===== �O���[�o���ϐ� =====
ITEM g_Item[MAX_ITEM];
DRAW_OBJECT g_drObjPupItem;
int g_nGetItemSE;

void InitItem(void)
{
	int i;
	char filename[] = ITEM_PIC;

	ReadBmp(filename, &g_drObjPupItem);

	for (i = 0; i < MAX_ITEM; i++)
	{
		g_Item[i].bExist = false;
		g_Item[i].nHeight = g_drObjPupItem.nHeight;
		g_Item[i].nWidth = g_drObjPupItem.nWidth;
	}

	g_nGetItemSE = CreateSound(GETITEM_SE);
	if (g_nGetItemSE == INVALID_HANDLE)
	{
		printf("�t�@�C�����J���܂���:%s", GETITEM_SE);
	}
}


void CreateItem(float x,float y)
{
	int i;

	for (i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bExist == true)	continue;

		g_Item[i].bExist = true;
		g_Item[i].fCurPosX = g_Item[i].fPrePosX = x;
		g_Item[i].fCurPosY = g_Item[i].fPrePosY = y;
		g_Item[i].nXdir = g_Item[i].nYdir = -1;
		g_Item[i].nTime = 0;
		g_Item[i].nBound = 0;
		g_Item[i].fAngle = rand();					//�ړ��p�x
		break;
	}
}


void UpdItem(void)
{
	int i;

	for (i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bExist == false)	continue;

		//----- �ߋ����W�ޔ� -----
		g_Item[i].fPrePosX = g_Item[i].fCurPosX;
		g_Item[i].fPrePosY = g_Item[i].fCurPosY;


		//----- �ړ� -----
		g_Item[i].fCurPosX += g_Item[i].nXdir *cos(g_Item[i].fAngle);
		g_Item[i].fCurPosY += g_Item[i].nYdir*sin(g_Item[i].fAngle);

		//----- ��ʒ[�ɍs����������]�� -----
		if (g_Item[i].nBound < MAX_BOUND)		//�o�E���h�\���ȉ��Ȃ�
		{
			if (g_Item[i].fCurPosX < LIMIT_LEFT || LIMIT_RIGHT < g_Item[i].fCurPosX)
			{
				g_Item[i].nXdir *= -1;
				g_Item[i].fCurPosX = g_Item[i].fPrePosX;
				g_Item[i].nBound++;
			}
			if (g_Item[i].fCurPosY < LIMIT_TOP || LIMIT_BOTTOM < g_Item[i].fCurPosY)
			{
				g_Item[i].nYdir *= -1;
				g_Item[i].fCurPosY = g_Item[i].fPrePosY;
				g_Item[i].nBound++;
			}
		}
		//----- ����������������� -----
		if (g_Item[i].nTime > LIFE_SPAN)
			g_Item[i].bExist = false;

		g_Item[i].nTime++;		//���Ԍo��

		//----- �o�E���h�����ɉ�ʊO�ɍs����������� -----
		if (LIMIT_LEFT < g_Item[i].fCurPosX < LIMIT_RIGHT)	continue;
		if (LIMIT_TOP < g_Item[i].fCurPosY < LIMIT_BOTTOM)	continue;
		g_Item[i].bExist = false;
	}

	ChkColItemAndPlayer();
}

void DrawItem(void)
{
	int i;

	for (i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bExist == false)	continue;

		g_drObjPupItem.fCurPosX = g_Item[i].fCurPosX;
		g_drObjPupItem.fCurPosY = g_Item[i].fCurPosY;

		AddObjectToBuf(&g_drObjPupItem);
	}
}


void ChkColItemAndPlayer(void)
{
	int i;
	float fDistanceX, fDistanceY;
	int nSumHeight, nSumWidth;
	PLAYER *pPlayer = GetPlayer();

	for (i = 0; i < MAX_ITEM; i++)
	{
		if (g_Item[i].bExist == false)	continue;

		//----- ��`���m�̓����蔻�� -----
		fDistanceY = fabs(g_Item[i].fCurPosY - pPlayer->fCurPosY);		//�A�C�e���ƃv���C���[��Y�����̐�Βl
		nSumHeight = (g_Item[i].nHeight + pPlayer->drObject->nHeight) / 2;
		if (fDistanceY > nSumHeight)	continue;

		fDistanceX = fabs(g_Item[i].fCurPosX - pPlayer->fCurPosX);
		nSumWidth = (g_Item[i].nWidth + pPlayer->drObject->nWidth) / 2;
		if (fDistanceX > nSumWidth)	continue;

		//----- ���������� -----
		g_Item[i].bExist = false;
		if (pPlayer->shotLevel < PLAYER_MAX_SHOTLEVEL)
			pPlayer->shotLevel += 2;
		else
			AddScore(1000);
		PlaySound(g_nGetItemSE, false);
	}
}

void UnInitItem(void)
{
	UnInitDrawObject(&g_drObjPupItem);
}