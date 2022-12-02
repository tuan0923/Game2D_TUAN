//========================================================
// fade.cpp
// 2DGame
//Author: �e���A��
//========================================================
#include "fade.h"
#include "main.h"
#include "game.h"
//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;		//���_�o�b�t�@�ւ̃|�C���^	
FADE g_fade;
MODE g_modeNext;
D3DXCOLOR g_colorFade;

//=============================
//�t�F�[�h�̏���������
//=============================
void InitFade(MODE modeNext)
{

	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_fade = FADE_IN;			//�t�F�[�h�C����Ԃ�
	g_modeNext = modeNext;		//���̉��(���[�h)��ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		//�����|���S��(�s����)�ɂ��Ă���

															//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL
	);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();

	//���[�h�̐ݒ�
	SetMode(g_modeNext);
}

//=============================
//�t�F�[�h�̍X�V����
//=============================
void UpdateFade(void)
{
	VERTEX_2D *pVtx;

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����
			g_colorFade.a -= 0.05f;
			if (g_colorFade.a <= 0.0f)	//�|���S���𓧖��ɂ��Ă���
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;		//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorFade.a += 0.065f;	//�|���S����s�����ɂ��Ă���
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;		//�������Ă��Ȃ���Ԃ�
				SetMode(g_modeNext);
			}
		}
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffFade->Unlock();
	}
}
//===========================
//�t�F�[�h�̕`�揈��
//===========================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}

//============================
//�t�F�[�h�̐ݒ菈��
//============================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;									//�t�F�[�h�A�E�g��Ԃ�
	g_modeNext = modeNext;								//���̉��(���[�h)��ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�����|���S��(����)�ɂ��Ă���
}

//==========================
//�t�F�[�h�̏I������
//==========================
void UninitFade(void)
{

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//==============================
//�t�F�[�h�̎擾����
//==============================
FADE GetFade(void)
{
	return g_fade;
}