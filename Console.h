//Console.h


#ifndef _CONSOLE_H_
#define _CONSOLE_H_

//===== インクルード部 ====-
#include<Windows.h>
#include"GameManager.h"

//===== 定数定義 =====
#define SCREEN_WIDTH	(LIMIT_RIGHT + 2)	//スクリーン横幅
#define SCREEN_HEIGHT	(LIMIT_BOTTOM + 2)	//スクリーン縦幅
//#define MAX_OBJ_WIDTH	(454)
//#define MAX_OBJ_HEIGHT	(131)


//===== 構造体宣言 =====
typedef struct
{
	HANDLE handle;		//スクリーンバッファのハンドル
	COORD BufferSize;	//裏バッファサイズ
	COORD StartPos;		//裏バッファの原点（左上隅）
	SMALL_RECT sr;		//書き込み先エリア
	CHAR_INFO cell[SCREEN_HEIGHT][SCREEN_WIDTH];	//画面に表示するcell内容の格納先
}CONSOLE;

//オブジェクトの位置
typedef struct
{
	float fX;
	float fY;
}POSITION;

typedef struct
{
	CHAR_INFO *pCell;	//オブジェクトの見た目の情報格納先
	float fCurPosX;		//オブジェクトの中心座標X
	float fCurPosY;		//				中心座標Y
	float fPrePosX;
	float fPrePosY;
	int nHeight;
	int nWidth;
	bool bExist;
	POSITION pos;	//オブジェクトの左上隅
}DRAW_OBJECT;


//===== プロトタイプ宣言 =====
void InitConsole(void);
void InitDrawObject(DRAW_OBJECT *object, int height, int width);
//void InitObject(DRAW_OBJECT *);
void AddObjectToBuf(DRAW_OBJECT *);
void DrawBuf(void);
void SetObjectChar(DRAW_OBJECT * obj, const char * c);
void SetObjectFGColor(DRAW_OBJECT * obj, const char * c);
void SetObjectBGColor(DRAW_OBJECT * obj, const char * c);
void UnInitDrawObject(DRAW_OBJECT *object);
void CutObjectAndAddToBuf(DRAW_OBJECT *object, int start, int end);
void ShowConsoleCursor(bool showFlag);
void NoChangePosAddObjectToBuf(DRAW_OBJECT *object);









#endif // !_CONSOLE_H_