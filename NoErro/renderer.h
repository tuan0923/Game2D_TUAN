#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "object2D.h"

#define SCREEN_WIDTH (1280)	// �X�N���[���̕�

#define SCREEN_HEIGHT (720) // �X�N���[���̍���

//�����_�����O�N���X
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	LPDIRECT3DDEVICE9 GetDevice() { return g_pD3DDevice; }
	HRESULT Init( HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	
	
private:

	void DrawFPS();
	
	// Direct3D�I�u�W�F�N�g
	LPDIRECT3D9 g_pD3D ;
	// Device�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 g_pD3DDevice;
	// �t�H���g
	LPD3DXFONT g_pFont;
	
};


#endif // !_RENDERER_H_
