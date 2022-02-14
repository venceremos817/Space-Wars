/**
 * @file	Sound.h
 * @brief	XAudio2 サウンド ライブラリ
 *
 * @author	HAL名古屋 教務部　佐々木遼太
 * @date	2020/01/08 (水)
 *
 * @detail
 *	サウンドを利用するためには、初めにInitSoundを呼び出す必要があります。
 *	また、プログラム終了時にはUninitSoundの呼び出しが必要です。
 *
 *	対応フォーマットはwavとmp3です。
 *	CreateSoundの読み込みが成功すると、ハンドルを返します。
 *	各サウンドの再生、停止、音量の調整はこのハンドルを利用して行います。
 *	読み込みが失敗した場合、INVALID_HANDLEを返します。
 *
 *	【例】
 *	int nSE, nBGM;
 *
 *	nSE = CreateSound("se.wav");
 *	if(nSE == INVALID_HANDLE)
 *		printf("failed create sound.");
 *
 *	nBGM = CreateSound("bgm.mp3");
 *	if(nBGM == INVALID_HANDLE)
 *		printf("failed create sound.");
 *
 *	PlaySound(nSE, false);
 *	SetVolume(nBGM, 0.7f);
 *	PlaySound(nBGM, true);
 *
 */
#ifndef __SOUND_H__
#define __SOUND_H__

//----------
// ライブラリ
//----------
#ifndef _SOUND_DEV
#ifdef _DEBUG
#pragma comment(lib, "SoundD.lib")
#else
#pragma comment(lib, "Sound.lib")
#endif // _DEBUG
#endif // _SOUND_DEV

//----------
// 定数
//----------
#define INVALID_HANDLE (-1)

//----------
// プロトタイプ宣言
//----------
bool InitSound(void);
void UninitSound(void);

/**
 * @brief サウンドファイル読み込み
 * @param[in] pszFile ファイル名
 * @return 読み込みハンドル
 */
int CreateSound(const char *pszFile);
/**
 * @brief サウンド再生
 * @param[in] nHandle サウンドハンドル
 * @param[in] bRepeat 繰り返しフラグ
 */
void PlaySound(int nHandle, bool bRepeat);
/**
 * @brief サウンド停止
 * @param[in] nHandle サウンドハンドル
 */
void StopSound(int nHandle);
/**
 * @brief ボリューム調整
 * @param[in] nHandle サウンドハンドル
 * @param[in] fVolume 音量[0.0f～1.0fの範囲]
 */
void SetVolume(int nHandle, float fVolume);

#endif // __SOUND_H__