//===================================================================
//
//3D�A�N�V����(main.h)
//Author:�匴���r
//
//===================================================================
#ifndef _MAIN_H_						//���̃}�N����`������ĂȂ�������
#define _MAIN_H_						//2�d�C���N���[�h�h�~�̃}�N����`
#define DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���΍��p�}�N��

//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include<windows.h>
#include"d3dx9.h"		//�`�揈���ɕK�v
#include"dinput.h"
#include"xaudio2.h"		//�T�E���h�����ɕK�v
#include"xinput.h"

//===================================================================
//���C�u���������N
//===================================================================
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//(d3d9.lib)�̊e�l���C�u����
#pragma comment(lib,"dxguid.lib")	//Direct�R���|�[�l���g�i���i�j�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	//�V�X�e���A�����擾�ɕK�v
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")

//===================================================================
//�}�N����`
//===================================================================
#define CLASS_NAME		"WindowClass"		//�E�B���h�E�N���X��
#define WINDOW_NAME		"Squid Disc"
#define SCREEN_WIDTH	(1280)				//�E�B���h�E��
#define SCREEN_HEIGHT	(720)				//�E�B���h�E����
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE |D3DFVF_TEX1)

//===================================================================
//���_���[3D]�̍\���̂��`
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//���_���W
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_3D;

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���\�ϊ��p�W���i1.0�Œ�j
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;

//===================================================================
//��ʁi���[�h�j�̎��
//===================================================================
typedef enum
{
	MODE_TITLE = 0,	//����������
	MODE_SCENE,		//�������
	MODE_TUTORIAL,	//�`���[�g���A�����
	MODE_GAME,		//�Q�[�����
	MODE_END,		//�I�����
	MODE_CLEAR,		//�N���A���
	MODE_SETUMEI,	//�Q�[������
	MODE_SOUSA,		//�������
	MODE_MAX
}MODE;

typedef enum
{
	PLAYER_P1 = 0,
	PLAYER_P2
}PLAYER_TYPE;

//===================================================================
//�v���g�^�C�v�錾
//===================================================================
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LPDIRECT3DDEVICE9 GetDevice(void);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);
void NextMode(MODE mode);

#endif 