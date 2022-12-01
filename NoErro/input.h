#ifndef _INPUT_H_
#define _INPUT_H_

//マクロ定義
#define NUM_KEY_MAX (256)

#include "main.h"

class CInputKeyboard
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	void UninitKeyboard(void);
	void UpdateKeyboard(void);
	static	bool GetKeyboardPress(int nKey);
	static bool GetKeyboardTrigger(int nKey);
private:
	//グローバル変数
	LPDIRECTINPUT8 g_pInput = NULL;
	LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
	static	BYTE g_aKeyState[NUM_KEY_MAX];
	static	BYTE g_aKeyStateTrigger[NUM_KEY_MAX]; //trigger
};

#endif