//Enemy.h

#ifndef _ENEMY_H_
#define _ENEMY_H_

//===== �萔��` =====
#define MAX_ENEMY	(100)

typedef enum
{
	NORMAL_MODE,
	ENDLESS_MODE,
	RANKING_MODE
}PLAY_MODE;


//===== �\���̐錾 =====
typedef struct
{
	float fCurPosX;
	float fCurPosY;
	float fPrePosX;
	float fPrePosY;
	int nHeight;
	int nWidth;
	int nHP;
	int nExistTime;
	int nApperTime;
	int nPattern;
	int nType;
	bool bExist;
}ENEMY;


//===== �v���g�^�C�v�錾 =====
void InitEnemy(void);
void CreateEnemy(void);
void UpdEnemy(void);
void DrawEnemyToBuf(void);
ENEMY *GetEnemy(void);
void UnInitEnemy(void);
void SetPlayMode(PLAY_MODE mode);







#endif // !_ENEMY_H_
