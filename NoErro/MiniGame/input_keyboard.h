//=============================================================================
//
// �L�[�{�[�h���� [input_keyboard.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#include "input.h"

//-----------------------------------------------------------------------------
// �L�[�{�[�h�N���X(�h���N���X)
//-----------------------------------------------------------------------------
class CInputKeyboard : public CInput
{
private:
	static const int MAX_KEY = 256;

public:
	// �L�[���͏��
	enum KEYINFO
	{
		KEYINFO_OK = 0,				// ����
		KEYINFO_UP,					// ��I��
		KEYINFO_DOWN,				// ���I��
		KEYINFO_RIGHT,				// �E�ړ�
		KEYINFO_LEFT,				// ���ړ�
		KEYINFO_PAUSE,				// �|�[�Y
		KEYINFO_ATTACK,				// �U��
		KEYINFO_1,					// 1
		KEYINFO_2,					// 2

		// �e�X�g�p
		KEYINFO_Q,
		KEYINFO_E,
		KEYINFO_Z,
		KEYINFO_C,
		KEYINFO_R,
		KEYINFO_F,
		KEYINFO_T,
		KEYINFO_G,
		KEYINFO_Y,
		KEYINFO_H,
		KEYINFO_MAX,
	};

	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetReleace(int nKey);

private:
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];
	BYTE m_aKeyStateReleace[MAX_KEY];

	int m_aKeyInfo[KEYINFO_MAX] =
	{
		DIK_RETURN,		// ����
		DIK_W,			// ��I��
		DIK_S,			// ���I�� 
		DIK_D,			// �E�ړ�
		DIK_A,			// ���ړ�
		DIK_P,			// �|�[�Y
		DIK_SPACE,		// �U��
		DIK_1,			// 1
		DIK_2,			// 2

		// �e�X�g�p
		DIK_Q,
		DIK_E,
		DIK_Z,
		DIK_C,
		DIK_R,
		DIK_F,
		DIK_T,
		DIK_G,
		DIK_Y,
		DIK_H
	};
};
#endif