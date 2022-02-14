

#ifndef _BMP_H_
#define _BMP_H_

//===== �C���N���[�h�� =====
#include"Console.h"

//===== �萔��` =====
#define FILEHEADERSIZE	(14)	//�t�@�C���w�b�_�̃T�C�Y
#define INFOHEADERSIZE	(40)	//���w�b�_�̃T�C�Y
#define HEADERSIZE		(FILEHEADERSIZE + INFOHEADERSIZE)	//�t�@�C���̃w�b�_�̃T�C�Y
#define FILETYPE_BM		(0x4D42)	//���g���G���f�B�A���ł̃t�@�C���^�C�vBM
#define COLOUR_HI  170
#define COLOUR_LOW 85

//===== �}�N����` =====
#define test(a)		printf("%d\n",a);	getchar();

//===== �\���̐錾 =====

//BMP�t�@�C���̃w�b�_
//typedef struct
//{
//	//--- �t�@�C���w�b�_
//	unsigned short bfType;		//�I�t�Z�b�g(0-1)�t�@�C���^�C�v
//	unsigned long bfSize;		//�I�t�Z�b�g(2-5)�t�@�C���T�C�YByte
//	unsigned short bfReserved1;	//�I�t�Z�b�g(6-7)�\��̈�1
//	unsigned short bfReserved2;	//�I�t�Z�b�g(8-9)�\��̈�2
//	unsigned long bfOffBits;	//�I�t�Z�b�g(10-13)�摜�f�[�^�܂ł̃I�t�Z�b�g
//	//--- ���w�b�_
//	unsigned int bitSize;		//�I�t�Z�b�g(14-17)���w�b�_�̃T�C�Y
//	int biWidth;				//�I�t�Z�b�g(18-21)�摜�̕�(�s�N�Z���P��)
//	int biHeight;				//�I�t�Z�b�g(22-25)�摜�̍���(�s�N�Z���P��)
//	unsigned short biPlanes;	//�I�t�Z�b�g(26-27)�v���[����
//	unsigned short biBitCount;	//�I�t�Z�b�g(28-29)���r�b�g�J���[�摜��
//	unsigned int bitCompression;//�I�t�Z�b�g(30-33)���k�`��
//	unsigned int biSizeImage;	//�I�t�Z�b�g(34-37)�w�b�_�������܂܂Ȃ��摜�f�[�^�̃T�C�Y
//	int biXPixPerMeter;			//�I�t�Z�b�g(38-41)�����𑜓x
//	int biYPixPerMeter;			//�I�t�Z�b�g(42-45)�����𑜓x
//	unsigned int biClrUsed;		//�I�t�Z�b�g(46-49)�p���b�g�̐F��
//	unsigned int biClrImportant;//�I�t�Z�b�g(50-53)�d�v�ȃp���b�g�̃C���f�b�N�X
//}BMP_HEADER;


//RGB���
typedef struct
{
	unsigned char b;	//Blue
	unsigned char g;	//Green
	unsigned char r;	//Red
}RGB;


//BMP�摜�̍����ƕ�
typedef struct
{
	unsigned short ushType;	//�t�@�C���^�C�v(BM)�ɂȂ�Ηǂ��I�t�Z�b�g(0-1)
//	unsigned long dwOffBits;//�摜�f�[�^�܂ł̃I�t�Z�b�g	�I�t�Z�b�g(10-13)	54�ɂȂ�Ƃ킩���Ă��邩��s�v
	int nWidth;				//���s�N�Z����					�I�t�Z�b�g(18-21)
	int nHeight;			//�c�s�N�Z����					�I�t�Z�b�g(22-25)
	unsigned int wBitCount;	//�F�r�b�g��(1,4,8,16,24,32)24�̕��݂̂�����	�I�t�Z�b�g(28-29)
}BMP_INFO;


//===== �v���g�^�C�v�錾 =====

//////////////////////////////
//�֐����FReadBmp
//����	�Fchar *filename �ǂݍ��ރt�@�C����
//�߂�l�F�Ȃ�
//////////////////////////////
void ReadBmp(char *filename, DRAW_OBJECT *object);






#endif // !_BMP_H_
