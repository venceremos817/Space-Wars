//main.h

#ifndef _MAIN_H
#define _MAIN_H_

//===== �萔��` =====

typedef enum
{
	MODE_TITLE,
	MODE_GAME,
	MODE_RANKING,
	MODE_RESULT,
	END_GAME,
	MODE_MAX
}MODE;

//===== �v���g�^�C�v�錾 =====
void Init(void);
void SetMode(MODE);
MODE GetMode(void);
void UnInit(void);






#endif // !_MAIN_H
