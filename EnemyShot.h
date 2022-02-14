//EnemyShot.h


#ifndef _ENEMY_SHOT_H_
#define _ENEMY_SHOT_H_

//===== インクルード部 =====
#include"PlayerShot.h"

//===== 定数定義 =====
#define MAX_ENEMY_SHOT	(50)


//===== 構造体宣言 =====
typedef struct
{
	SHOT shot[MAX_ENEMY_SHOT];
	float m_ePosX;
	float m_ePosY;
	float m_pPosX;
	float m_pPosY;
	float Angle[MAX_ENEMY_SHOT];
	int nPattern;
	int nCounter;
	bool bExist;
}ENEMY_SHOT;

//===== プロトタイプ宣言 =====
void InitEnemyShot(void);
void CreateEnemyShot(int enemynum, int pattern);
void CreateBossShot(int pattern);
void UpdEnemyShot(void);
void DrawEnemyShotToBuf(void);
void UnInitEnemyShot(void);







#endif // !_ENEMY_SHOT_H_
