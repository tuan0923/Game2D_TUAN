//============================================================
//
//�Q�[�������̏���(Setumei.cpp)
//AUTHOR:���X�ؗ��l
//
//=============================================================
#include "main.h"
#include "input.h"
#include "SETUMEI.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "Choices.h"
#include"Frame.h"
#include"controller.h"

//==============================================================
//�O���[�o���ϐ�
//==============================================================

LPDIRECT3DTEXTURE9 g_pTextureSetumei = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSetumei = NULL;//���_�o�b�t�@�ւ̂ۂ���

//==============================================================
//�Q�[�������̏���������
//==============================================================
void lnitSetumei(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_TITLE);

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/SETUMEI.jpg",
		&g_pTextureSetumei);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSetumei,
		NULL);

	VERTEX_2D*pVtx;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffSetumei->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̕`��
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffSetumei->Unlock();
}

//==============================================================
//�Q�[�������̏I��
//==============================================================
void UninitSetumei(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTextureSetumei != NULL)
	{
		g_pTextureSetumei->Release();
		g_pTextureSetumei = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSetumei != NULL)
	{
		g_pVtxBuffSetumei->Release();
		g_pVtxBuffSetumei = NULL;
	}
}

//==============================================================
//�Q�[�������̍X�V����
//==============================================================
void UpdateSetumei(void)
{
	// �t�F�[�h���̎擾
	FADE fade = GetFade();
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A) == true && fade == FADE_NONE)
	{
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_Score);
		//���[�h�ݒ�
		SetFade(MODE_TITLE);
	}
}

//==============================================================
//�Q�[�������̕`�揈��
//==============================================================
void DrawSetumei(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSetumei, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSetumei);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

