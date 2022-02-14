

#ifndef _BMP_H_
#define _BMP_H_

//===== インクルード部 =====
#include"Console.h"

//===== 定数定義 =====
#define FILEHEADERSIZE	(14)	//ファイルヘッダのサイズ
#define INFOHEADERSIZE	(40)	//情報ヘッダのサイズ
#define HEADERSIZE		(FILEHEADERSIZE + INFOHEADERSIZE)	//ファイルのヘッダのサイズ
#define FILETYPE_BM		(0x4D42)	//リトルエンディアンでのファイルタイプBM
#define COLOUR_HI  170
#define COLOUR_LOW 85

//===== マクロ定義 =====
#define test(a)		printf("%d\n",a);	getchar();

//===== 構造体宣言 =====

//BMPファイルのヘッダ
//typedef struct
//{
//	//--- ファイルヘッダ
//	unsigned short bfType;		//オフセット(0-1)ファイルタイプ
//	unsigned long bfSize;		//オフセット(2-5)ファイルサイズByte
//	unsigned short bfReserved1;	//オフセット(6-7)予約領域1
//	unsigned short bfReserved2;	//オフセット(8-9)予約領域2
//	unsigned long bfOffBits;	//オフセット(10-13)画像データまでのオフセット
//	//--- 情報ヘッダ
//	unsigned int bitSize;		//オフセット(14-17)情報ヘッダのサイズ
//	int biWidth;				//オフセット(18-21)画像の幅(ピクセル単位)
//	int biHeight;				//オフセット(22-25)画像の高さ(ピクセル単位)
//	unsigned short biPlanes;	//オフセット(26-27)プレーン数
//	unsigned short biBitCount;	//オフセット(28-29)何ビットカラー画像か
//	unsigned int bitCompression;//オフセット(30-33)圧縮形式
//	unsigned int biSizeImage;	//オフセット(34-37)ヘッダ部分を含まない画像データのサイズ
//	int biXPixPerMeter;			//オフセット(38-41)水平解像度
//	int biYPixPerMeter;			//オフセット(42-45)水平解像度
//	unsigned int biClrUsed;		//オフセット(46-49)パレットの色数
//	unsigned int biClrImportant;//オフセット(50-53)重要なパレットのインデックス
//}BMP_HEADER;


//RGB情報
typedef struct
{
	unsigned char b;	//Blue
	unsigned char g;	//Green
	unsigned char r;	//Red
}RGB;


//BMP画像の高さと幅
typedef struct
{
	unsigned short ushType;	//ファイルタイプ(BM)になれば良いオフセット(0-1)
//	unsigned long dwOffBits;//画像データまでのオフセット	オフセット(10-13)	54になるとわかっているから不要
	int nWidth;				//横ピクセル数					オフセット(18-21)
	int nHeight;			//縦ピクセル数					オフセット(22-25)
	unsigned int wBitCount;	//色ビット数(1,4,8,16,24,32)24の物のみを扱う	オフセット(28-29)
}BMP_INFO;


//===== プロトタイプ宣言 =====

//////////////////////////////
//関数名：ReadBmp
//引数	：char *filename 読み込むファイル名
//戻り値：なし
//////////////////////////////
void ReadBmp(char *filename, DRAW_OBJECT *object);






#endif // !_BMP_H_
