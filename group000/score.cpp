//-------------------------------------------
//
//�X�R�A����[score.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "score.h"


//�}�N����`
#define SCORE_WIDTH		(20.0f)		//�X�R�A�̕�
#define SCORE_HEIGHT	(45.0f)		//�X�R�A�̍���
#define NUM_SCORE		(2)			//�X�R�A�̍ő包��
#define MAX_SCORE		(2)			//�X�R�A�̍ő吔

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScore[3] = {};			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore[3] = {};	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_PosScore[MAX_SCORE][NUM_SCORE];		//�X�R�A�̈ʒu
int g_nScore[MAX_SCORE];							//�X�R�A�̒l
int g_aPosTexU[MAX_SCORE][NUM_SCORE];				//�e���̐������i�[

//-------------------------------------------
//����������
//-------------------------------------------
void InitScore(void)
{
	//������
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		for (int nCntX = 0; nCntX < NUM_SCORE; nCntX++)
		{//�ʒu
			g_PosScore[nCntScore][nCntX] = D3DXVECTOR3((570.0f + (25.0f * nCntX)) + (110.0f * nCntScore), SCREEN_HEIGHT / 2.0f, 0.0f);
		}
		g_nScore[nCntScore] = 0;		//���_
	}

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//--------------------------------�w�i�̏���----------------------------------------------------

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/background000.jpg",
		&g_pTextureScore[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore[0],
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore[0]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (160.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) - (50.0f / 2.0f), 0);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (160.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) - (50.0f / 2.0f), 0);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (160.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) + (50.0f / 2.0f), 0);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (160.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) + (50.0f / 2.0f), 0);

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

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore[0]->Unlock();

	//--------------------------------�u�[�v(���_�Ɠ��_�̊Ԃɂ�����)�̏���---------------------------------------------------

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/score000.png",
		&g_pTextureScore[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore[1],
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore[1]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (50.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) - (10.0f / 2.0f), 0);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (50.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) - (10.0f / 2.0f), 0);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (50.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) + (10.0f / 2.0f), 0);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (50.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) + (10.0f / 2.0f), 0);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore[1]->Unlock();

	//--------------------------------���_(����)�̏���---------------------------------------------------

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureScore[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE * NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore[2],
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore[2]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		for (int nCntX = 0; nCntX < NUM_SCORE; nCntX++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_PosScore[nCntScore][nCntX].x - (SCORE_WIDTH / 2.0f), g_PosScore[nCntScore][nCntX].y - (SCORE_HEIGHT / 2.0f), 0);
			pVtx[1].pos = D3DXVECTOR3(g_PosScore[nCntScore][nCntX].x + (SCORE_WIDTH / 2.0f), g_PosScore[nCntScore][nCntX].y - (SCORE_HEIGHT / 2.0f), 0);
			pVtx[2].pos = D3DXVECTOR3(g_PosScore[nCntScore][nCntX].x - (SCORE_WIDTH / 2.0f), g_PosScore[nCntScore][nCntX].y + (SCORE_HEIGHT / 2.0f), 0);
			pVtx[3].pos = D3DXVECTOR3(g_PosScore[nCntScore][nCntX].x + (SCORE_WIDTH / 2.0f), g_PosScore[nCntScore][nCntX].y + (SCORE_HEIGHT / 2.0f), 0);

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;		//���_�f�[�^���S���i�߂�
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore[2]->Unlock();

	SetScore(0, 0);
	SetScore(1, 0);
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < 3; nCount++)
	{
		if (g_pTextureScore[nCount] != NULL)
		{
			g_pTextureScore[nCount]->Release();
			g_pTextureScore[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	for (int nCount = 0; nCount < 3; nCount++)
	{
		if (g_pVtxBuffScore[nCount] != NULL)
		{
			g_pVtxBuffScore[nCount]->Release();
			g_pVtxBuffScore[nCount] = NULL;
		}
	}
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateScore(void)
{
	//(���̂Ƃ���Ȃ�)
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawScore(void)
{
	for (int nCount = 0; nCount < 3; nCount++)
	{
		//�f�o�C�X�ւ̃|�C���^
		LPDIRECT3DDEVICE9 pDevice;

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffScore[nCount], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�A���t�@�e�X�g��L��
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//�|���S���`��̃J�E���^
		int nCntDraw = 0;

		switch (nCount)
		{
		case 0:			//0��������w�i�̕`��
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureScore[0]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			break;
		case 1:			//1��������u�[�v�̕`��
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureScore[1]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			break;
		case 2:			//1��������X�R�A�̕`��
			for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
			{
				for (int nCntX = 0; nCntX < NUM_SCORE; nCntX++, nCntDraw++)
				{
					//�e�N�X�`���ݒ�
					pDevice->SetTexture(0, g_pTextureScore[2]);

					//�|���S���̕`��
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDraw * 4, 2);
				}
			}
			break;
		default:
			//assert(false);
			break;
		}

		//�A���t�@�e�X�g�𖳌��ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//-------------------------------------------
//�X�R�A�̐ݒ菈��
//-------------------------------------------
void SetScore(int nOrder,int nScore)
{
	//���_��ǉ�
	g_nScore[nOrder] = nScore;

	//�e�N�X�`������
	g_aPosTexU[nOrder][0] = g_nScore[nOrder] % 100 / 10;
	g_aPosTexU[nOrder][1] = g_nScore[nOrder] % 10 / 1;
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore[2]->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		for (int nCntX = 0; nCntX < NUM_SCORE; nCntX++)
		{
			pVtx[0].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX] + 0.1f, 1.0f);

			pVtx += 4;		//�f�[�^��4���i�߂�
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore[2]->Unlock();
}

//-----------------------------------------------------------------
//
//�X�R�A�̉��Z����
//int order���|�C���g �͂���̂�1P�̏ꍇ0���w��A2P�̏ꍇ1���w��
//int nValue�����Z�����_�����w��
//
//----------------------------------------------------------------
void AddScore(int order, int nValue)
{
	//���_��ǉ�
	g_nScore[order] += nValue;

	//�e�N�X�`������
	g_aPosTexU[order][0] = g_nScore[order] % 100 / 10;
	g_aPosTexU[order][1] = g_nScore[order] % 10 / 1;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore[2]->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		for (int nCntX = 0; nCntX < NUM_SCORE; nCntX++)
		{
			pVtx[0].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX], 0.0f);
			pVtx[1].tex = D3DXVECTOR2((0.1f * g_aPosTexU[nCntScore][nCntX]) + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX], 1.0f);
			pVtx[3].tex = D3DXVECTOR2((0.1f * g_aPosTexU[nCntScore][nCntX]) + 0.1f, 1.0f);

			pVtx += 4;		//�f�[�^4���i�߂�
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore[2]->Unlock();
}

//-----------------------------------------------------------------
//
//�X�R�A�̎擾����
//int ���� = GetScore();�ŌĂяo���A
//����++;��2P�̃X�R�A���擾�ł���
//
//----------------------------------------------------------------
int GetScore(int order)
{
	return g_nScore[order];
}