//Player.h

#ifndef _PLAYER_H_
#define _PLAYER_H_

//===== �C���N���[�h�� =====
#include"Console.h"

//===== �萔��` =====
#define PLAYER_MAX_SHOTLEVEL	(11)


//===== �񋓌^ =====
typedef enum
{
	MIDDLE,
	LEFT,
	RIGHT,
	MAX_FORM
}PLAYER_FORM;

//===== �\���̐錾 =====
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
	int nLeft;			//�c�@
	int nInvincible;
}PLAYER;



//===== �v���g�^�C�v�錾 =====
////////////////////////////////////
//�֐����FInitPlayer
//����	�F�Ȃ�
//�߂�l�F�Ȃ�
//���e	�FPlayer������������
////////////////////////////////////
void InitPlayer(void);

////////////////////////////////////
//�֐����FCreatePlayer
//����	�F�Ȃ�
//�߂�l�F�Ȃ�
//���e	�FPlayer�𐶐�����
////////////////////////////////////
void CreatePlayer(void);


////////////////////////////////////
//�֐����FUpdPlayer
//����	�F�Ȃ�
//�߂�l�F�Ȃ�
//���e	�F�v���C���[�̏�Ԃ�ύX����
////////////////////////////////////
void UpdPlayer(void);


////////////////////////////////////
//�֐����FDrawToBufferPlayer
//����	�F�Ȃ�
//�߂�l�F�Ȃ�
//���e	�F�o�b�t�@��Player��`������
////////////////////////////////////
void DrawPlayerToBuf(void);


void DestroyPlayer(void);

////////////////////////////////////
//�֐����FUnInitPlayer
//����	�F�Ȃ�
//�߂�l�F�Ȃ�
//���e	�F�������̉���Ȃ�
////////////////////////////////////
void UniInitPlayer(void);




////////////////////////////////////
//�֐����FGetPlayer
//����	�F�Ȃ�
//�߂�l�FPLAYER *
//���e	�FPlayer�̏���n��
////////////////////////////////////
PLAYER *GetPlayer(void);








#endif // !_PLAYER_H_
