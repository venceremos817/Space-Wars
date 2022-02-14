//GameManager.h

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

//===== 定数定義 =====
#define LIMIT_TOP		(1)
#define LIMIT_BOTTOM	(173)
#define	LIMIT_LEFT		(1)
#define LIMIT_RIGHT		(608)
#define FRAME_RATE		(1000/60)

typedef enum
{
	OVER_LEFT,
	OVER_RIGHT,
	OVER_TOP,
	OVER_BOTTM,
	INSIDE
}SCREEN_OVER;



//===== プロトタイプ宣言 =====
/////////////////////////////////////
//内容：ゲーム時間経過
/////////////////////////////////////
void TimePass(void);

/////////////////////////////////////
//引数	：float x,y(中心座標)	int width,height (見た目の幅、高さ)
//戻り値：画面内ならtrue 外ならfalse
/////////////////////////////////////
//int ChkBodyInsideScreen(float x, float y, int width, int height);

////////////////////////////////////
//時間取得
////////////////////////////////////
//unsigned long GetGameTime(void)




#endif // !_GAME_MANAGER_H_
