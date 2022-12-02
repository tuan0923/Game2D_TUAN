//========================================================
// result.cpp
// 2DGame
//Author: �e���A��
//========================================================
#include "main.h"
#include "result.h"
#include "game.h"
#include "score.h"
#include "highscore.h"

LPDIRECT3DTEXTURE9 g_pTextureResult = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//================================================
//�^�C�g����ʂ̏���������
//================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nScore = GetScore();
	pDevice = GetDevice();		//�f�o�C�X�̎擾

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//bg007.png",
		&g_pTextureResult);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D *pVtx;	//���_���̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();
	PlaySound(SOUND_LABEL_BGM002);
	InitHighScore();
	InitScore();
	SetScore(nScore, D3DXVECTOR3(650.0f, 180.0f, 0.0f), 60.0f, 80.0f);
	SaveHighScore();
	
}
//================================================
//�^�C�g����ʂ̏I������
//================================================
void UninitResult(void)
{
	//�T�E���h�̒�~
	StopSound();
	UninitScore();
	UninitHighScore();
	//�o�b�t�@�j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
}
//================================================
//�^�C�g����ʂ̍X�V����
//================================================
void UpdateResult(void)
{

	FADE pFade;
	pFade = GetFade();
	if (GetKeyboardTrigger(DIK_RETURN) == true && pFade == FADE_NONE)
	{
		//�Q�[����ʂɑJ��
		SetFade(MODE_TITLE);

	}
	UpdateScore();
	UpdateHighScore();
}
//================================================
//�^�C�g����ʂ̕`�揈��
//================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//�v���~�e�B�u�̎��
	DrawScore();
	DrawHighScore();
}
