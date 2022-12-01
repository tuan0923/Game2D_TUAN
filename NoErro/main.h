#ifndef _MAIN_H_
#define _MAIN_H_
//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <Windows.h>
#include <tchar.h> // _T
#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"

//*****************************************************************************
// ���C�u�����[�����N
//*****************************************************************************

#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//(d3d9.lib)�̊e�l���C�u����
#pragma comment(lib,"dxguid.lib")	
#pragma comment(lib,"winmm.lib")	
#pragma comment(lib,"dinput8.lib")


#define MAX_OBJECT (64)
#define OBJECT2D_SIZE_X (40.0f)
#define OBJECT2D_SIZE_Y (40.0f)
#define PLAYER_SIZE_X (40.0f)
#define PLAYER_SIZE_Y (40.0f)
#endif // !_MAIN_H_

//�O���錾
class CRenderer;
class CObject;
class CInputKeyboard;
//�O���[�o���ϐ�
int GetFPS();

