//=======================================================
//
//3D�A�N�V�����Q�[������(input.h)
//Author:�匴���r
//
//=======================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "main.h"

//===================================================================
//�L�[�̎��
//===================================================================
typedef enum
{
	JOYKEY_UP = 0,			//�\���L�[��
	JOYKEY_DOWN,			//�\���L�[��
	JOYKEY_LEFT,			//�\���L�[��
	JOYKEY_RIGHT,			//�\���L�[��
	JOYKEY_START,			//�X�^-�g�{�^��
	JOYKEY_BACK,			//BACK�{�^��
	JOYKEY_LPUSH,			//L�g���K�[
	JOYKEY_RPUSH,			//R�g���K�[
	JOYKEY_L1,				//L1
	JOYKEY_R1,				//R1
	JOYKEY_L2,				//L2
	JOYKEY_R2,				//R2
	JOYKEY_A,				//A�{�^��
	JOYKEY_B,				//B�{�^��
	JOYKEY_X,				//X�{�^��
	JOYKEY_Y,				//Y�{�^��
	MAX_JOYKEY
}JOYkey;

//===================================================================
//�v���g�^�C�v�錾
//===================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYkey key);
bool GetJoypadTrigger(JOYkey key);
#endif
