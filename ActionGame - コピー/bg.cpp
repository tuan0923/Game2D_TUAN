//========================================================
// bg.cpp
// 2DGame
//Author: �e���A��
//========================================================
#include "main.h"
#include "bg.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBG = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;//���_�o�b�t�@�ւ̃|�C���^
int g_nCounterAnimBG;					//�A�j���[�V�����J�E���^�[
int g_nPatternAnimBG;					//�A�j���[�V�����p�^�[��No.
float g_fBG;
//================================================
//�w�i�̏���������
//================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg07.png",
		&g_pTextureBG);

	g_nCounterAnimBG = 0;		//�J�E���^�[��������
	g_nPatternAnimBG = 0;		//�p�^�[��No.��������
	g_fBG = 0.01f;
								//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.7f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.7f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBG->Unlock();
}
//================================================
//�w�i�̏I������
//================================================
void UninitBG(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBG != NULL)
	{
		g_pTextureBG->Release();
		g_pTextureBG = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}
//================================================
//�w�i�̍X�V����
//================================================
void UpdateBG(void)
{
	VERTEX_2D *pVtx2;		//���_���ւ̃|�C���^
	g_nCounterAnimBG++;		//�J�E���^�[�����Z
	g_fBG += 0.0001f;
				//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx2, 0);

		// �e�N�X�`�����W�̐ݒ�
		pVtx2[0].tex = D3DXVECTOR2(0.0f +g_fBG,0.0f);
		pVtx2[1].tex = D3DXVECTOR2(1.0f +g_fBG, 0.0f); 
		pVtx2[2].tex = D3DXVECTOR2 (0.0f+g_fBG, 1.0f);
		pVtx2[3].tex = D3DXVECTOR2(1.0f + g_fBG,1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffBG->Unlock();
	
}
//================================================
//�w�i�̕`�揈��
//================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,		//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);		//�v���~�e�B�u�i�|���S���j��

}