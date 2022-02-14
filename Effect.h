//Effect.h

#ifndef _EFFECT_H_
#define _EFFECT_H_

//===== 列挙型 =====
typedef enum
{
	EXPLOSION,

}EFFECT_TYPE;

//===== 構造体定義 =====
typedef struct
{
	float fX;
	float fY;
	int nTime;
	int nType;
	int nFilm;
	bool bExist;
}EFFECT;

//===== プロトタイプ宣言 =====
void InitEffect(void);
void CreateEffect(float x, float y, EFFECT_TYPE type);
void UpdEffect(void);
void DrawEffect(void);
void UnInitEffect(void);
EFFECT *GetEffect(void);
bool ChkRemainEffect(void);



#endif // !_EFFECT_H_
