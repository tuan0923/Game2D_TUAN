#ifndef _MAIN_H_
#define _MAIN_H_
//*****************************************************************************
// インクルード
//*****************************************************************************
#include <Windows.h>
#include <tchar.h> // _T
#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"

//*****************************************************************************
// ライブラリーリンク
//*****************************************************************************

#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//(d3d9.lib)の各様ライブラリ
#pragma comment(lib,"dxguid.lib")	
#pragma comment(lib,"winmm.lib")	
#pragma comment(lib,"dinput8.lib")


#define MAX_OBJECT (64)
#define OBJECT2D_SIZE_X (40.0f)
#define OBJECT2D_SIZE_Y (40.0f)
#define PLAYER_SIZE_X (40.0f)
#define PLAYER_SIZE_Y (40.0f)
#endif // !_MAIN_H_

//前方宣言
class CRenderer;
class CObject;
class CInputKeyboard;
//グローバル変数
int GetFPS();

