//Player.h

#ifndef _PLAYER_H_
#define _PLAYER_H_

//===== インクルード部 =====
#include"Console.h"

//===== 定数定義 =====
#define PLAYER_MAX_SHOTLEVEL	(11)


//===== 列挙型 =====
typedef enum
{
	MIDDLE,
	LEFT,
	RIGHT,
	MAX_FORM
}PLAYER_FORM;

//===== 構造体宣言 =====
typedef struct
{
	DRAW_OBJECT drObject[MAX_FORM];
	float fCurPosX;
	float fCurPosY;
	float fPrePosX;
	float fPrePosY;
	float fMoveSpdX;
	float fMoveSpdY;
	int shotLevel;
	bool bExist;
	int nDirection;
	int nLeft;			//残機
	int nInvincible;
}PLAYER;



//===== プロトタイプ宣言 =====
////////////////////////////////////
//関数名：InitPlayer
//引数	：なし
//戻り値：なし
//内容	：Playerを初期化する
////////////////////////////////////
void InitPlayer(void);

////////////////////////////////////
//関数名：CreatePlayer
//引数	：なし
//戻り値：なし
//内容	：Playerを生成する
////////////////////////////////////
void CreatePlayer(void);


////////////////////////////////////
//関数名：UpdPlayer
//引数	：なし
//戻り値：なし
//内容	：プレイヤーの状態を変更する
////////////////////////////////////
void UpdPlayer(void);


////////////////////////////////////
//関数名：DrawToBufferPlayer
//引数	：なし
//戻り値：なし
//内容	：バッファにPlayerを描き込む
////////////////////////////////////
void DrawPlayerToBuf(void);


void DestroyPlayer(void);

////////////////////////////////////
//関数名：UnInitPlayer
//引数	：なし
//戻り値：なし
//内容	：メモリの解放など
////////////////////////////////////
void UniInitPlayer(void);




////////////////////////////////////
//関数名：GetPlayer
//引数	：なし
//戻り値：PLAYER *
//内容	：Playerの情報を渡す
////////////////////////////////////
PLAYER *GetPlayer(void);








#endif // !_PLAYER_H_
