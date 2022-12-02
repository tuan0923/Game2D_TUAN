//-------------------------------------------
//
//�R���g���[���[�̏��[controller.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "main.h"
#include "controller.h"

//�}�N����`
#define MAX_CONTROLLER		(2)		//�R���g���[���[�̍ő吔

//�O���[�o���錾
XINPUT_STATE g_JoyKeyState[2];				//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_JoyKeyStateTrigger[2];		//�W���C�p�b�h�̃g���K�[���

//-------------------------------------------
//�R���g���[���[�̏���������
//-------------------------------------------
HRESULT InitController(void)
{
	for (int nCount = 0; nCount < MAX_CONTROLLER; nCount++)
	{
		//�������̃N���A
		ZeroMemory(&g_JoyKeyState[nCount], sizeof(XINPUT_STATE));

		//�������̃N���A
		ZeroMemory(&g_JoyKeyStateTrigger[nCount], sizeof(XINPUT_STATE));
	}

	//XInput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//-------------------------------------------
//�R���g���[���[�̏I������
//-------------------------------------------
void UninitController(void)
{
	//XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

//-------------------------------------------
//�R���g���[���[�̍X�V����
//-------------------------------------------
void UpdateController(void)
{
	for (int nCount = 0; nCount < MAX_CONTROLLER; nCount++)
	{
		//�W���C�p�b�h�̓��͏��
		XINPUT_STATE JoyKeyState[2];

		//�W���C�p�b�h�̏����擾
		if (XInputGetState(nCount, &JoyKeyState[nCount]) == ERROR_SUCCESS)
		{
			g_JoyKeyStateTrigger[nCount].Gamepad.wButtons = (g_JoyKeyState[nCount].Gamepad.wButtons ^ JoyKeyState[nCount].Gamepad.wButtons) & JoyKeyState[nCount].Gamepad.wButtons;		//�{�^���̃g���K�[����ۑ�
			g_JoyKeyState[nCount] = JoyKeyState[nCount];	//�{�^���̃v���X����ۑ�
		}
	}
}

//-------------------------------------------------------------------
//
//�R���g���[���[�̃{�^���v���X�����擾
//int nPlayer ���R���g���[���[��1P�̏ꍇ0���w��A2P�̏ꍇ1���w��
//int nKey ���{�^�����w��Acontroller.h�Ƀ}�N���̋L�ڂ���
//
//--------------------------------------------------------------------
bool GetControllerPress(int nPlayer,int nKey)
{
	return (g_JoyKeyState[nPlayer].Gamepad.wButtons & nKey) ? true : false;
}

//---------------------------------------------------------------
//
//�R���g���[���[�̃{�^���g���K�[�����擾
//int nPlayer ���R���g���[���[��1P�̏ꍇ0���w��A2P�̏ꍇ1���w��
//int nKey ���{�^�����w��Acontroller.h�Ƀ}�N���̋L�ڂ���
//
//--------------------------------------------------------------
bool GetControllerPressTrigger(int nPlayer,int nKey)
{
	return (g_JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & nKey) ? true : false;
}

//-----------------------------------------------------------------
//
//�R���g���[���[�̃X�e�B�b�N�v���X�����擾
//int nPlayer ���R���g���[���[��1P�̏ꍇ0���w��A2P�̏ꍇ1���w��
//int nKey ���X�e�B�b�N�̌X����������w��A
//			 controller.h��enum�^�ŋL�ڂ���
//
//-----------------------------------------------------------------
bool GetControllerStickPress(int nPlayer, STICK nKey)
{
	//������
	bool Ret = false;	

	//�X�e�B�b�N�̃f�b�h�]�[���̏���
	if ((g_JoyKeyState[nPlayer].Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
		&& g_JoyKeyState[nPlayer].Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		&& (g_JoyKeyState[nPlayer].Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
			&& g_JoyKeyState[nPlayer].Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_JoyKeyState[nPlayer].Gamepad.sThumbLX = 0;		//�l��0�ɂ���
		g_JoyKeyState[nPlayer].Gamepad.sThumbLY = 0;		//�l��0�ɂ���
	}

	if (nKey == STICK_LEFT && g_JoyKeyState[nPlayer].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{// �X�e�B�b�N�̍��������ꂽ
		Ret = true;
	}

	if (nKey == STICK_RIGHT && g_JoyKeyState[nPlayer].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{// �X�e�B�b�N�̉E�������ꂽ
		Ret = true;
	}

	if (nKey == STICK_DOWN && g_JoyKeyState[nPlayer].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{// �X�e�B�b�N�̉��������ꂽ
		Ret = true;
	}

	if (nKey == STICK_UP && g_JoyKeyState[nPlayer].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{// �X�e�B�b�N�̏オ�����ꂽ
		Ret = true;
	}

	return Ret;		//bool�^��Ԃ�
}

//-----------------------------------------------------------------
//
//�R���g���[���[�̃X�e�B�b�N�̎΂ߓ��͂��擾
//int nPlayer ���R���g���[���[��1P�̏ꍇ0���w��A2P�̏ꍇ1���w��
//
//D3DXVECTOR3 ���� = GetControllerStickDir(int nPlayer)�@�ŌĂяo��
//g_player.pos.x += ����.x * �v���C���[�̑��x  �Ŏ΂ߑΉ���
//g_player.pos.z += ����.y * �v���C���[�̑��x  �Ŏ΂ߑΉ���
//
//-----------------------------------------------------------------
D3DXVECTOR3 GetControllerStickDir(int nPlayer)
{
	D3DXVECTOR3 StickAngle(g_JoyKeyState[nPlayer].Gamepad.sThumbLX, g_JoyKeyState[nPlayer].Gamepad.sThumbLY,0.0f);

	//�p�x��1�ɂ���
	D3DXVec3Normalize(&StickAngle,&StickAngle);

	return StickAngle;		//�l��Ԃ�
}