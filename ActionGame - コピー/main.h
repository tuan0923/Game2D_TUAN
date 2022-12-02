//===================================================================
//�t�@�C���w�b�_
//===================================================================

#ifndef _MAIN_H_

#define _MAIN_H_	

#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"						//���͏����ɕK�v
#include "xinput.h"						//�W���C�p�b�h�����ɕK�v
#include "xaudio2.h"					//�T�E���h�����ɕK�v


//���C�u���������N
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//(d3d9.lib)�̊e�l���C�u����
#pragma comment(lib,"dxguid.lib")	
#pragma comment(lib,"winmm.lib")	
#pragma comment(lib,"dinput8.lib")

//�}�N����`
#define SCREEN_WIDTH	(1280)		//�E�B���h�E��
#define SCREEN_HEIGHT	(720)		//�E�B���h�E����
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;
//��ʁi���[�h�j
typedef enum
{
	MODE_TITLE = 0,
	MODE_HOWTO,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;
//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
#endif 
