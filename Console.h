//Console.h


#ifndef _CONSOLE_H_
#define _CONSOLE_H_

//===== �C���N���[�h�� ====-
#include<Windows.h>
#include"GameManager.h"

//===== �萔��` =====
#define SCREEN_WIDTH	(LIMIT_RIGHT + 2)	//�X�N���[������
#define SCREEN_HEIGHT	(LIMIT_BOTTOM + 2)	//�X�N���[���c��
//#define MAX_OBJ_WIDTH	(454)
//#define MAX_OBJ_HEIGHT	(131)


//===== �\���̐錾 =====
typedef struct
{
	HANDLE handle;		//�X�N���[���o�b�t�@�̃n���h��
	COORD BufferSize;	//���o�b�t�@�T�C�Y
	COORD StartPos;		//���o�b�t�@�̌��_�i������j
	SMALL_RECT sr;		//�������ݐ�G���A
	CHAR_INFO cell[SCREEN_HEIGHT][SCREEN_WIDTH];	//��ʂɕ\������cell���e�̊i�[��
}CONSOLE;

//�I�u�W�F�N�g�̈ʒu
typedef struct
{
	float fX;
	float fY;
}POSITION;

typedef struct
{
	CHAR_INFO *pCell;	//�I�u�W�F�N�g�̌����ڂ̏��i�[��
	float fCurPosX;		//�I�u�W�F�N�g�̒��S���WX
	float fCurPosY;		//				���S���WY
	float fPrePosX;
	float fPrePosY;
	int nHeight;
	int nWidth;
	bool bExist;
	POSITION pos;	//�I�u�W�F�N�g�̍����
}DRAW_OBJECT;


//===== �v���g�^�C�v�錾 =====
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