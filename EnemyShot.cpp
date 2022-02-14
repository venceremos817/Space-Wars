//EnemyShot.cpp



//===== �C���N���[�h�� =====
#include"EnemyShot.h"
#include"Enemy.h"
#include"Console.h"
#include"Bmp.h"
#include"Player.h"
#include"GameManager.h"
#include"Effect.h"
#include"Boss.h"
#include"Sound.h"
#include<math.h>
#include<Windows.h>

//===== �萔��` =====
#define GREEN_BALL_FILE		"BMP/GreenBall.bmp"
#define GREEN_LASER_FILE	"BMP/GreenLaser.bmp"
#define RED_BALL_FILE		"BMP/RedBall.bmp"
#define RED_LASER_FILE		"BMP/RedLaser.bmp"
#define PINK_BALL_FILE		"BMP/PinkBall.bmp"

//===== �񋓌^ =====
typedef enum
{
	GreenBall,
	GreenLaser,
	RedBall,
	RedLaser,
	PinkBall,
	MAX_BULLET_TYPE
}BULLET_TYPE;

//===== �O���[�o���ϐ� =====
ENEMY_SHOT g_EnemyShot[MAX_ENEMY];
DRAW_OBJECT EnemyShotPic[MAX_BULLET_TYPE];

//===== �v���g�^�C�v�錾 =====
void EnemyShotPattern1(int i);
void EnemyShotPattern2(int i);
void EnemyShotPattern3(int i);
void ChkColEShotAndPBody(void);



void InitEnemyShot(void)
{
	int i, j;
	char filename[MAX_BULLET_TYPE][25] = { GREEN_BALL_FILE,GREEN_LASER_FILE,RED_BALL_FILE,RED_LASER_FILE,PINK_BALL_FILE };

	for (i = 0; i < MAX_BULLET_TYPE; i++)
	{
		ReadBmp(filename[i], &EnemyShotPic[i]);
	}

	

	for (i = 0; i < MAX_ENEMY; i++)
	{
		g_EnemyShot[i].bExist = false;

		for (j = 0; j < MAX_ENEMY_SHOT; j++)
		{
			g_EnemyShot[i].shot[j].bExist = false;
			//g_EnemyShot[i].shot[j].nHeight = EnemyShotPic.nHeight;
			//g_EnemyShot[i].shot[j].nWidth = EnemyShotPic.nWidth;
		}
	}
}

void CreateEnemyShot(int enemynum, int pattern)
{
	int i;
	ENEMY *pEnemy = GetEnemy();
	PLAYER *pPlayer = GetPlayer();

	for (i = 0; i < MAX_ENEMY_SHOT; i++)
		if (g_EnemyShot[i].bExist == false)
			break;
	g_EnemyShot[i].bExist = true;
	g_EnemyShot[i].nPattern = pattern;
	g_EnemyShot[i].m_ePosX = pEnemy[enemynum].fCurPosX;
	g_EnemyShot[i].m_ePosY = pEnemy[enemynum].fCurPosY;
	g_EnemyShot[i].m_pPosX = pPlayer->fCurPosX;
	g_EnemyShot[i].m_pPosY = pPlayer->fCurPosY;
	g_EnemyShot[i].nCounter = 0;
}

void CreateBossShot(int pattern)
{
	int i;
	ENEMY *pBoss = GetBoss();
	PLAYER *pPlayer = GetPlayer();

	for (i = 0; i < MAX_ENEMY; i++)
		if (g_EnemyShot[i].bExist == false)
			break;

	g_EnemyShot[i].bExist = true;
	g_EnemyShot[i].nPattern = pattern;
	g_EnemyShot[i].m_ePosX = pBoss->fCurPosX;
	g_EnemyShot[i].m_ePosY = pBoss->fCurPosY;
	g_EnemyShot[i].m_pPosX = pPlayer->fCurPosX;
	g_EnemyShot[i].m_pPosY = pPlayer->fCurPosY;
	g_EnemyShot[i].nCounter = 0;
}

void UpdEnemyShot(void)
{
	int i, j;
	int nExsitCnt;

	for (i = 0; i < MAX_ENEMY; i++)
	{
		if (g_EnemyShot[i].bExist == false)	continue;


		switch (g_EnemyShot[i].nPattern)
		{
		case 1:
			EnemyShotPattern1(i);
			break;

		case 2:
			EnemyShotPattern2(i);
			break;

		case 3:
			EnemyShotPattern3(i);
			break;

		default:
			break;
		}
		g_EnemyShot[i].nCounter++;


		//----- �e����ʊO�ɍs�������̏��� -----
		for (j = 0, nExsitCnt = 0; j < MAX_ENEMY_SHOT; j++)
		{
			if (g_EnemyShot[i].shot[j].bExist == false)	continue;

			if (g_EnemyShot[i].shot[j].fX < LIMIT_LEFT)		//��
				g_EnemyShot[i].shot[j].bExist = false;
			if (g_EnemyShot[i].shot[j].fX > LIMIT_RIGHT)	//�E
				g_EnemyShot[i].shot[j].bExist = false;
			if (g_EnemyShot[i].shot[j].fY< LIMIT_TOP)		//��
				g_EnemyShot[i].shot[j].bExist = false;
			if (g_EnemyShot[i].shot[j].fY  > LIMIT_BOTTOM)	//��
				g_EnemyShot[i].shot[j].bExist = false;

			if (g_EnemyShot[i].shot[j].bExist == true)
				nExsitCnt++;
		}
		if (nExsitCnt == 0)
			g_EnemyShot[i].bExist = false;
	}

	ChkColEShotAndPBody();			//�v���C���[�Ɠ������Ă��邩


}



void DrawEnemyShotToBuf(void)
{
	int i, j;

	for (i = 0; i < MAX_ENEMY; i++)
	{
		if (g_EnemyShot[i].bExist == false)	continue;
		for (j = 0; j < MAX_ENEMY_SHOT; j++)
		{
			if (g_EnemyShot[i].shot[j].bExist == false)	continue;
			EnemyShotPic[g_EnemyShot[i].shot[j].mBulletType].fCurPosX = g_EnemyShot[i].shot[j].fX;
			EnemyShotPic[g_EnemyShot[i].shot[j].mBulletType].fCurPosY = g_EnemyShot[i].shot[j].fY;

			//EnemyShotPic.fCurPosX = g_EnemyShot[i].shot[j].fX;
			//EnemyShotPic.fCurPosY = g_EnemyShot[i].shot[j].fY;
			AddObjectToBuf(&EnemyShotPic[g_EnemyShot[i].shot[j].mBulletType]);
		}
	}
}


///////////////////////////////////////
//�܂������������낵
///////////////////////////////////////
void EnemyShotPattern1(int i)
{
	if (g_EnemyShot[i].nCounter == 0)
	{
		g_EnemyShot[i].shot[0].bExist = true;
		g_EnemyShot[i].shot[0].mBulletType = GreenLaser;
		g_EnemyShot[i].shot[0].nHeight = EnemyShotPic[GreenLaser].nHeight;
		g_EnemyShot[i].shot[0].nWidth = EnemyShotPic[GreenLaser].nWidth;

		g_EnemyShot[i].shot[0].fX = g_EnemyShot[i].m_ePosX;
		g_EnemyShot[i].shot[0].fY = g_EnemyShot[i].m_ePosY;
	}
	g_EnemyShot[i].shot[0].fY += 1.0f;
}


//////////////////////////////////////////
//���ˎ��Ƀv���C���[���������W�Ɍ�����
/////////////////////////////////////////
void EnemyShotPattern2(int i)
{
	if (g_EnemyShot[i].nCounter == 0)
	{
		g_EnemyShot[i].shot[0].bExist = true;
		g_EnemyShot[i].shot[0].mBulletType = GreenBall;
		g_EnemyShot[i].shot[0].nHeight = EnemyShotPic[GreenBall].nHeight;
		g_EnemyShot[i].shot[0].nWidth = EnemyShotPic[GreenBall].nWidth;
		g_EnemyShot[i].shot[0].fX = g_EnemyShot[i].m_ePosX;
		g_EnemyShot[i].shot[0].fY = g_EnemyShot[i].m_ePosY;
		g_EnemyShot[i].Angle[0] = atan2f(g_EnemyShot[i].m_pPosY - g_EnemyShot[i].m_ePosY,
			g_EnemyShot[i].m_pPosX - g_EnemyShot[i].m_ePosX);
	}
	g_EnemyShot[i].shot[0].fX += 1.0*cos(g_EnemyShot[i].Angle[0]);
	g_EnemyShot[i].shot[0].fY += 1.0*sin(g_EnemyShot[i].Angle[0]);
}


/////////////////////////////////////////////
//���˒n�_����΂߂�2����
/////////////////////////////////////////////
void EnemyShotPattern3(int i)
{
	int j;
	if (g_EnemyShot[i].nCounter == 0)
	{
		for (j = 0; j < 2; j++)
		{
			g_EnemyShot[i].shot[j].bExist = true;
			g_EnemyShot[i].shot[j].mBulletType = RedBall;
			g_EnemyShot[i].shot[j].nHeight = EnemyShotPic[RedBall].nHeight;
			g_EnemyShot[i].shot[j].nWidth = EnemyShotPic[RedBall].nWidth;
			g_EnemyShot[i].shot[j].fX = g_EnemyShot[i].m_ePosX;
			g_EnemyShot[i].shot[j].fY = g_EnemyShot[i].m_ePosY;
		}
	}

	g_EnemyShot[i].shot[0].fX += 1.0f;
	g_EnemyShot[i].shot[1].fX -= 1.0f;
	for (j = 0; j < 2; j++)
	{
		g_EnemyShot[i].shot[j].fY += 1.0f;
	}
}

void ChkColEShotAndPBody(void)
{
	int i, j;
	float fDistanceX, fDistanceY;
	int nSumWidth, nSumHeight;
	PLAYER *pPlayer = GetPlayer();

	for (i = 0; i < MAX_ENEMY; i++)
	{
		if (g_EnemyShot[i].bExist == false)	continue;

		for (j = 0; j < MAX_ENEMY_SHOT; j++)
		{
			if (g_EnemyShot[i].shot[j].bExist == false)	continue;
			if (pPlayer->bExist == false)	continue;

			//----- ��`���m�œ����蔻����Ƃ� -----
			fDistanceY = fabs(g_EnemyShot[i].shot[j].fY - pPlayer->fCurPosY);
			nSumHeight = (g_EnemyShot[i].shot[j].nHeight + pPlayer->drObject->nHeight) / 2;
			if (fDistanceY > nSumHeight)	continue;

			fDistanceX = fabs(g_EnemyShot[i].shot[j].fX - pPlayer->fCurPosX);
			nSumWidth = (g_EnemyShot[i].shot[j].nWidth + pPlayer->drObject->nWidth) / 2;
			if (fDistanceX > nSumWidth)	continue;

			//----- ����������
			if (pPlayer->nInvincible < 0)
			{
				g_EnemyShot[i].shot[j].bExist = false;
				DestroyPlayer();
			}
		}
	}

}

void UnInitEnemyShot(void)
{
	int i;

	for (i = 0; i < MAX_BULLET_TYPE; i++)
	{
		UnInitDrawObject(&EnemyShotPic[i]);
	}

}
