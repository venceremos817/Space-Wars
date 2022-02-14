//PlayerShot.h



#ifndef _PLAYER_SHOT_H_
#define	_PLAYER_SHOT_H_
//===== インクルード部 =====
#include"Console.h"
#include"Player.h"


//===== 定数定義 =====
#define PLAYER_MAX_SHOT_WAY	(11)
#define PLAYER_MAX_SHOT_NUM	(10)


//===== 構造体宣言 =====
typedef struct
{
	float fX;
	float fY;
	int nHeight;
	int nWidth;
	int mBulletType;
	bool bExist;
}SHOT;

//===== プロトタイプ宣言 =====
void InitPlayerShot(void);
void CreatePlayerShot(PLAYER player);
void UpdPlayerShot(void);
void DrawPlayerShotToBuf(void);
//void CreateRaser(void);
bool ChkColPShotAndBoss(void);
void UnInitPlayerShot(void);
SHOT *GetShotLine1(void);





#endif // !_PLAYER_SHOT_H_
