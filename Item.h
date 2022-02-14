//Item.h

#ifndef _ITEM_H_
#define _ITEM_H_

typedef struct
{
	float fCurPosX;
	float fCurPosY;
	float fPrePosX;
	float fPrePosY;
	int nHeight;
	int nWidth;
	int nXdir;
	int nYdir;
	float fAngle;
	int nTime;
	int nBound;
	bool bExist;
}ITEM;


//===== プロトタイプ宣言 =====
void InitItem(void);
void CreateItem(float x, float y);
void UpdItem(void);
void DrawItem(void);
void UnInitItem(void);






#endif // !_ITEM_H_
