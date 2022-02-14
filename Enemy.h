//Enemy.h

#ifndef _ENEMY_H_
#define _ENEMY_H_

//===== 定数定義 =====
#define MAX_ENEMY	(100)

typedef enum
{
	NORMAL_MODE,
	ENDLESS_MODE,
	RANKING_MODE
}PLAY_MODE;


//===== 構造体宣言 =====
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


//===== プロトタイプ宣言 =====
void InitEnemy(void);
void CreateEnemy(void);
void UpdEnemy(void);
void DrawEnemyToBuf(void);
ENEMY *GetEnemy(void);
void UnInitEnemy(void);
void SetPlayMode(PLAY_MODE mode);







#endif // !_ENEMY_H_
