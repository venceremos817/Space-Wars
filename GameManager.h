//GameManager.h

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

//===== �萔��` =====
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



//===== �v���g�^�C�v�錾 =====
/////////////////////////////////////
//���e�F�Q�[�����Ԍo��
/////////////////////////////////////
void TimePass(void);

/////////////////////////////////////
//����	�Ffloat x,y(���S���W)	int width,height (�����ڂ̕��A����)
//�߂�l�F��ʓ��Ȃ�true �O�Ȃ�false
/////////////////////////////////////
//int ChkBodyInsideScreen(float x, float y, int width, int height);

////////////////////////////////////
//���Ԏ擾
////////////////////////////////////
//unsigned long GetGameTime(void)




#endif // !_GAME_MANAGER_H_
