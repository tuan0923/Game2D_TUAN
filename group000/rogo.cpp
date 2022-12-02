//============================================================
//
// 3D����@���s���S[Rogo.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"score.h"
#include"result.h"
#include"rogo.h"
//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_apTextureRogo[NUM_Rogo] = { NULL };	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRogo = NULL;			//���_�o�b�t�@�|�C���^
Rogo g_aRogo[MAX_Rogo];								//�G�̏��
int WinScore[2];
//���S�̎擾
Rogo*GetRogo(void)
{
	return &g_aRogo[0];
}

//============================================================
//���s���S�̏���������
//============================================================
void lnitRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRogo;


	//�J�E���^�[�̏�����
	nCntRogo = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WIN.png",
		&g_apTextureRogo[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/LOSE.png",
		&g_apTextureRogo[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Drow.png",
		&g_apTextureRogo[2]);

	//���̏�����
	for (nCntRogo = 0; nCntRogo < MAX_Rogo; nCntRogo++)
	{
		g_aRogo[nCntRogo].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRogo[nCntRogo].nType = 0;
		g_aRogo[nCntRogo].bUse = false;
	}

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Rogo * NUM_Rogo,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRogo,
		NULL);


	VERTEX_2D*pVtx;		//���_���փ|�C���^

						//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffRogo->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRogo = 0; nCntRogo < MAX_Rogo; nCntRogo++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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


		pVtx += 4;
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffRogo->Unlock();

	WinScore[0] = GetScore(0);
	WinScore[1] = GetScore(1);
	InitScore();

}

//============================================================
//���s���S�̏�������
//============================================================
void UninitRogo(void)
{
	UninitScore();

	int nCntRogo;

	for (nCntRogo = 0; nCntRogo < NUM_Rogo; nCntRogo++)
	{ //�e�N�X�`���̔j��
		if (g_apTextureRogo[nCntRogo] != NULL)
		{
			g_apTextureRogo[nCntRogo]->Release();
			g_apTextureRogo[nCntRogo] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRogo != NULL)
	{
		g_pVtxBuffRogo->Release();
		g_pVtxBuffRogo = NULL;
	}

}
//============================================================
//���s���S�̍X�V����
//============================================================
void UpdateRogo(void)
{
	UpdateScore();

	int nCntRogo;
	VERTEX_2D*pVtx;
	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffRogo->Lock(0, 0, (void**)&pVtx, 0);



	//���s���m�F���\������
	if (WinScore[0] > WinScore[1])
	{//1P������
		SetRogo(D3DXVECTOR3(100, 70.0f, 0.0f), 0);
		SetRogo(D3DXVECTOR3(800, 70.0f, 0.0f), 1);
	}

	 if (WinScore[0]<WinScore[1])
	{//2P������
		SetRogo(D3DXVECTOR3(100, 70.0f, 0.0f), 1);
		SetRogo(D3DXVECTOR3(800, 70.0f, 0.0f), 0);
	}

	if (WinScore[0] == WinScore[1])
	{//��������
		SetRogo(D3DXVECTOR3(640, 440.0f, 0.0f), 2);
	}

	for (nCntRogo = 0; nCntRogo < MAX_Rogo; nCntRogo++)
	{
		if (g_aRogo[nCntRogo].bUse == true)
		{

			//���_���W�̍X�V(���S�̑傫��)
			pVtx[0].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x - Rogo_SIZE / 2, g_aRogo[nCntRogo].pos.y - Rogo_SIZE / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x + Rogo_SIZE / 2, g_aRogo[nCntRogo].pos.y - Rogo_SIZE / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x - Rogo_SIZE / 2, g_aRogo[nCntRogo].pos.y + Rogo_SIZE / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x + Rogo_SIZE / 2, g_aRogo[nCntRogo].pos.y + Rogo_SIZE / 2, 0.0f);

		}
		pVtx += 4;//�|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffRogo->Unlock();
}

//============================================================
//���s���S�`�揈��
//============================================================
void DrawRogo(void)
{
	DrawScore();

	LPDIRECT3DDEVICE9 pDevice;
	int nCntRogo;
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRogo, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntRogo = 0; nCntRogo < MAX_Rogo; nCntRogo++)
	{
		if (g_aRogo[nCntRogo].bUse == true)
		{//�G���g�p����Ă���

		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureRogo[g_aRogo[nCntRogo].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRogo * 4, 2);
		}
	}
}

//============================================================
//���s���S�̐ݒ菈��
//============================================================
void SetRogo(D3DXVECTOR3 pos, int nType)
{
	int nCntRogo;

	VERTEX_2D*pVtx;

	//���_�o�b�t�@���b�N���A���_���փ|�C���^�擾
	g_pVtxBuffRogo->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRogo = 0; nCntRogo < MAX_Rogo; nCntRogo++)
	{
		if (g_aRogo[nCntRogo].bUse == false)
		{//�G���g�p����ĂȂ��ꍇ

		 //�G�̏��̐ݒ�
			g_aRogo[nCntRogo].pos = pos;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x - 6.0f, g_aRogo[nCntRogo].pos.y - 6.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x + 6.0f, g_aRogo[nCntRogo].pos.y - 6.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x - 6.0f, g_aRogo[nCntRogo].pos.y + 6.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x + 6.0f, g_aRogo[nCntRogo].pos.y + 6.0f, 0.0f);


			//���_�J���[�̕`��
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aRogo[nCntRogo].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_aRogo[nCntRogo].nType = nType;

			break;
		}
		pVtx += 4;//�|�C���^���S���i�߂�
	}
	g_pVtxBuffRogo->Unlock();
}
