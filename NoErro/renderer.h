#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "object2D.h"

#define SCREEN_WIDTH (1280)	// スクリーンの幅

#define SCREEN_HEIGHT (720) // スクリーンの高さ

//レンダリングクラス
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
	
	// Direct3Dオブジェクト
	LPDIRECT3D9 g_pD3D ;
	// Deviceオブジェクト
	LPDIRECT3DDEVICE9 g_pD3DDevice;
	// フォント
	LPD3DXFONT g_pFont;
	
};


#endif // !_RENDERER_H_
