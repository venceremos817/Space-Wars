//Effect.h

#ifndef _EFFECT_H_
#define _EFFECT_H_

//===== �񋓌^ =====
typedef enum
{
	EXPLOSION,

}EFFECT_TYPE;

//===== �\���̒�` =====
typedef struct
{
	float fX;
	float fY;
	int nTime;
	int nType;
	int nFilm;
	bool bExist;
}EFFECT;

//===== �v���g�^�C�v�錾 =====
void InitEffect(void);
void CreateEffect(float x, float y, EFFECT_TYPE type);
void UpdEffect(void);
void DrawEffect(void);
void UnInitEffect(void);
EFFECT *GetEffect(void);
bool ChkRemainEffect(void);



#endif // !_EFFECT_H_
