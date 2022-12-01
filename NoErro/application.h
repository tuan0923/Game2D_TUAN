
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
class CBullet;
class CPlayer;
class CEnemy;

class CApplication
{
public:
	CApplication();
	~CApplication();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Draw(void);
	void Update(void);
	void LoadAll(void);
	void UnLoadAll(void);
	static CRenderer *GetRenderer();
	static CInputKeyboard *GetInputKeyboard();


private:
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;

};

#endif