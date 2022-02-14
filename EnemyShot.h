//EnemyShot.h


#ifndef _ENEMY_SHOT_H_
#define _ENEMY_SHOT_H_

//===== �C���N���[�h�� =====
#include"PlayerShot.h"

//===== �萔��` =====
#define MAX_ENEMY_SHOT	(50)


//===== �\���̐錾 =====
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

//===== �v���g�^�C�v�錾 =====
void InitEnemyShot(void);
void CreateEnemyShot(int enemynum, int pattern);
void CreateBossShot(int pattern);
void UpdEnemyShot(void);
void DrawEnemyShotToBuf(void);
void UnInitEnemyShot(void);







#endif // !_ENEMY_SHOT_H_
