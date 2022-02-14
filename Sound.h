/**
 * @file	Sound.h
 * @brief	XAudio2 �T�E���h ���C�u����
 *
 * @author	HAL���É� �������@���X�ؗɑ�
 * @date	2020/01/08 (��)
 *
 * @detail
 *	�T�E���h�𗘗p���邽�߂ɂ́A���߂�InitSound���Ăяo���K�v������܂��B
 *	�܂��A�v���O�����I�����ɂ�UninitSound�̌Ăяo�����K�v�ł��B
 *
 *	�Ή��t�H�[�}�b�g��wav��mp3�ł��B
 *	CreateSound�̓ǂݍ��݂���������ƁA�n���h����Ԃ��܂��B
 *	�e�T�E���h�̍Đ��A��~�A���ʂ̒����͂��̃n���h���𗘗p���čs���܂��B
 *	�ǂݍ��݂����s�����ꍇ�AINVALID_HANDLE��Ԃ��܂��B
 *
 *	�y��z
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
// ���C�u����
//----------
#ifndef _SOUND_DEV
#ifdef _DEBUG
#pragma comment(lib, "SoundD.lib")
#else
#pragma comment(lib, "Sound.lib")
#endif // _DEBUG
#endif // _SOUND_DEV

//----------
// �萔
//----------
#define INVALID_HANDLE (-1)

//----------
// �v���g�^�C�v�錾
//----------
bool InitSound(void);
void UninitSound(void);

/**
 * @brief �T�E���h�t�@�C���ǂݍ���
 * @param[in] pszFile �t�@�C����
 * @return �ǂݍ��݃n���h��
 */
int CreateSound(const char *pszFile);
/**
 * @brief �T�E���h�Đ�
 * @param[in] nHandle �T�E���h�n���h��
 * @param[in] bRepeat �J��Ԃ��t���O
 */
void PlaySound(int nHandle, bool bRepeat);
/**
 * @brief �T�E���h��~
 * @param[in] nHandle �T�E���h�n���h��
 */
void StopSound(int nHandle);
/**
 * @brief �{�����[������
 * @param[in] nHandle �T�E���h�n���h��
 * @param[in] fVolume ����[0.0f�`1.0f�͈̔�]
 */
void SetVolume(int nHandle, float fVolume);

#endif // __SOUND_H__