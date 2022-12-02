//-------------------------------------------
//
//�R���g���[���[���[controller.h]
//Author:���앑
//
//-------------------------------------------
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�X�e�B�b�N�̏��
typedef enum
{
	STICK_LEFT = 0,		//�X�e�B�b�N�����ɌX������
	STICK_RIGHT,		//�X�e�B�b�N���E�ɌX������
	STICK_UP,			//�X�e�B�b�N����ɌX������
	STICK_DOWN,			//�X�e�B�b�N�����ɌX������
	STICK_MAX
}STICK;

//�v���g�^�C�v�錾
HRESULT InitController(void);				//����������
void UninitController(void);				//�I������
void UpdateController(void);				//�X�V����
bool GetControllerPress(int nPlayer,int nKey);			//�v���X���̎擾
bool GetControllerPressTrigger(int nPlayer,int nKey);	//�g���K�[���̎擾
bool GetControllerStickPress(int nPlayer, STICK nKey);	//�X�e�B�b�N�v���X���̎擾
D3DXVECTOR3 GetControllerStickDir(int nPlayer);			//�X�e�B�b�N�΂ߓ��͂̏����擾

#endif

//Key�{�^���̃}�N��----------------------------------------------------------
	// XINPUT_GAMEPAD_DPAD_UP		�� �\���L�[�̏�{�^��
	// XINPUT_GAMEPAD_DPAD_DOWN		�� �\���L�[�̉��{�^��
	// XINPUT_GAMEPAD_DPAD_LEFT		�� �\���L�[�̍��{�^��
	// XINPUT_GAMEPAD_DPAD_RIGHT	�� �\���L�[�̉E�{�^��
	// XINPUT_GAMEPAD_A				�� A�{�^��
	// XINPUT_GAMEPAD_B				�� B�{�^��
	// XINPUT_GAMEPAD_X				�� X�{�^��
	// XINPUT_GAMEPAD_Y				�� Y�{�^��
	// XINPUT_GAMEPAD_START			�� START�{�^��
	// XINPUT_GAMEPAD_BACK			�� BACK�{�^��