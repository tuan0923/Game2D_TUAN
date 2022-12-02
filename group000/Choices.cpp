//============================================================
//
//�I��������(Choices.cpp)
//AUTHOR:���X�ؗ��l
//
//=============================================================
#include "main.h"

//==============================================================
//�O���[�o���ϐ�
//==============================================================
LPDIRECT3DTEXTURE9 g_pTextureChoices = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffChoices = NULL;//���_�o�b�t�@�ւ̂ۂ���
D3DXVECTOR3 g_ChoicesPos;

//==============================================================
//�I�����̏���������
//==============================================================
void lnitChoices(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Choices.png",
		&g_pTextureChoices);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffChoices,
		NULL);

	VERTEX_2D*pVtx;		//���_���փ|�C���^

	g_ChoicesPos = D3DXVECTOR3(800.0f, 550.0f, 0.0f);

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffChoices->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffChoices->Unlock();
}

//==============================================================
//��������̏I��
//==============================================================
void UninitChoices(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureChoices != NULL)
	{
		g_pTextureChoices->Release();
		g_pTextureChoices = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffChoices != NULL)
	{
		g_pVtxBuffChoices->Release();
		g_pVtxBuffChoices = NULL;
	}
}

//==============================================================
//��������̍X�V����
//==============================================================
void UpdateChoices(void)
{

}

//==============================================================
//��������̕`�揈��
//==============================================================
void DrawChoices(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffChoices, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureChoices);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//�I�����̐ݒ菈��
void SetChoices(D3DXVECTOR3 pos)
{

	VERTEX_2D*pVtx;
	g_pVtxBuffChoices->Lock(0, 0, (void**)&pVtx, 0);


	g_ChoicesPos = pos;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(420.0f, 400.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(860.0f, 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(420.0f, 600.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(860.0f, 600.0f, 0.0f);

	pVtx += 4;//�|�C���^���S���i�߂�

	g_pVtxBuffChoices->Unlock();
}