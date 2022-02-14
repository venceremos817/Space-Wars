//Boss.h

#ifndef _BOSS_H_
#define _BOSS_H_

//===== インクルード部 =====
#include"Enemy.h"

//===== プロトタイプ宣言 =====
void InitBoss(void);
void CreateBoss(void);
void UpdBoss(void);
void DrawBoss(void);
void UnInitBoss(void);
ENEMY *GetBoss(void);



#endif // !_BOSS_H_
