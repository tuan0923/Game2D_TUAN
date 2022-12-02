//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	//BGM
	SOUND_LABEL_A = 0,			// BGM0
	SOUND_LABEL_GAME,			// BGM:�Q�[���p�T�E���h
	SOUND_LABEL_TITLE,			// BGM:��������p�T�E���h
	//SE
	SOUND_LABEL_SE_Catch,		//�L���b�`
	SOUND_LABEL_SE_Count,		//�J�E���g�_�E��
	SOUND_LABEL_SE_END,			//�Q�[���I��
	SOUND_LABEL_SE_Score,		//�_��
	SOUND_LABEL_SE_Throw,		//������
	SOUND_LABEL_SE_VS,			//
	SOUND_LABEL_SE_Frame,		//�t���[���̑I����
	SOUND_LABEL_MAX,
} SOUND_LABEL;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
