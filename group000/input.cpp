//=======================================================
//
//2D�A�N�V�����Q�[������(input.cpp)
//Author:�匴���r
//
//=======================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "input.h"
#include "main.h"

//�}�N����`
#define NUM_KEY_MAX (256)							//�L�[�̍ő吔

//�O���[�o���ϐ�
LPDIRECTINPUT8	g_pInput = NULL;					//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;		//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
BYTE	g_aKeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̃v���X���
BYTE	g_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
XINPUT_STATE g_JoykeyState;							//�Q�[���p�b�h�̃v���X���
XINPUT_STATE g_JoykeyStateTrigger;					//�Q�[���p�b�h�̃g���K�[���

//===================================================================
//�L�[�{�[�h�̏���������
//===================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//Direct�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̍쐬
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//===================================================================
//�W���C�p�b�h�̏�����
//===================================================================
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_JoykeyState, 0, sizeof(XINPUT_STATE));

	//Xinput�̃X�e�[�g�̐ݒ�i�L�����p�j
	XInputEnable(true);

	return S_OK;
}

//===================================================================
//�L�[�{�[�h�I������
//===================================================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X�j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//===================================================================
//�W���C�p�b�h�I������
//===================================================================
void UninitJoypad(void)
{
	//Xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(false);
}

//===================================================================
//�L�[�{�[�h�X�V����
//===================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^�擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];//�L�[�{�[�h�̃g���K�[����ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();		//�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}

//===================================================================
//�W���C�p�b�h�X�V
//===================================================================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{
		g_JoykeyStateTrigger.Gamepad.wButtons = (g_JoykeyState.Gamepad.wButtons & joykeystate.Gamepad.wButtons) ^ joykeystate.Gamepad.wButtons;			//�g���K�[����	
		g_JoykeyState = joykeystate;
	}
}

//===================================================================
//�L�[�{�[�h�̃v���X���擾
//===================================================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;	//3�����Z�q(?A:B;)
}

//===================================================================
//�L�[�{�[�h�̃g���K�[�����擾
//===================================================================
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//===================================================================
//�W���C�p�b�h�̃v���X���擾
//===================================================================
bool GetJoypadPress(JOYkey key)
{
	return (g_JoykeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//===================================================================
//�W���C�p�b�h�g���K�[�����擾
//===================================================================
bool GetJoypadTrigger(JOYkey key)
{
	return (g_JoykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}