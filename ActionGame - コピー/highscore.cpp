//========================================================
// highscore.cpp
// 2DGame
//Author: �e���A��
//========================================================
#include<stdio.h>
#include <string.h>
#include "main.h"
#include "item.h"
#include "game.h"
#include "result.h"
#include "highscore.h"
#include "score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureHighScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHighScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posHighScore;								//�X�R�A�̈ʒu
int g_HighScore;


//�X�R�A�̏���������
void InitHighScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntHighScore;


	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_pTextureHighScore);

	g_posHighScore = D3DXVECTOR3(800.0f, 420, 0.0f);		//�ʒu�̏�����
	g_HighScore = 0;											//�l��������

	LoadHighScore();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHighScore,
		NULL);

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHighScore = 0; nCntHighScore < MAX_HIGHSCORE; nCntHighScore++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_posHighScore.x - 20 + 40 * nCntHighScore, g_posHighScore.y - 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posHighScore.x + 20 + 40 * nCntHighScore, g_posHighScore.y - 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posHighScore.x - 20 + 40 * nCntHighScore, g_posHighScore.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posHighScore.x + 20 + 40 * nCntHighScore, g_posHighScore.y + 30.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;				//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffHighScore->Unlock();

	SetHighScore(g_HighScore);
}


//�X�R�A�̏I������
void UninitHighScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureHighScore != NULL)
	{
		g_pTextureHighScore->Release();
		g_pTextureHighScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffHighScore != NULL)
	{
		g_pVtxBuffHighScore->Release();
		g_pVtxBuffHighScore = NULL;
	}
}


//�X�R�A�̍X�V����
void UpdateHighScore(void)
{

}


//�X�R�A�̕`�揈��
void DrawHighScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�ւ̃|�C���^
	int nCntHighScore;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHighScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureHighScore);

	for (nCntHighScore = 0; nCntHighScore < MAX_HIGHSCORE; nCntHighScore++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
			nCntHighScore * 4, 2);									//�v���~�e�B�u�i�|���S���j��
	}
}


//�X�R�A�̐ݒ菈��
void SetHighScore(int nHighScore)
{
	VERTEX_2D *pVtx;				//���_���ւ̃|�C���^
	int aPosTexU[MAX_HIGHSCORE];				//�e���̐������i�[
	int nCntHighScore;

	g_HighScore = nHighScore;

	aPosTexU[0] = g_HighScore % 100000000 / 10000000;
	aPosTexU[1] = g_HighScore % 10000000 / 1000000;
	aPosTexU[2] = g_HighScore % 1000000 / 100000;
	aPosTexU[3] = g_HighScore % 100000 / 10000;
	aPosTexU[4] = g_HighScore % 10000 / 1000;
	aPosTexU[5] = g_HighScore % 1000 / 100;
	aPosTexU[6] = g_HighScore % 100 / 10;
	aPosTexU[7] = g_HighScore % 10 / 1;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHighScore = 0; nCntHighScore < MAX_HIGHSCORE; nCntHighScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntHighScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntHighScore] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntHighScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntHighScore] + 1), 1.0f);

		pVtx += 4;  //���_�f�[�^�̃|�C���^���S���i�߂�

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffHighScore->Unlock();
}


//���Z����
void AddHighScore(int nValue)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	int aPosTexU[MAX_HIGHSCORE];		//�e���̐������i�[
	int nCntHighScore;
	g_HighScore += nValue;

	if (g_HighScore <= 0)
	{
		g_HighScore = 0;
	}

	aPosTexU[0] = g_HighScore % 100000000 / 10000000;
	aPosTexU[1] = g_HighScore % 10000000 / 1000000;
	aPosTexU[2] = g_HighScore % 1000000 / 100000;
	aPosTexU[3] = g_HighScore % 100000 / 10000;
	aPosTexU[4] = g_HighScore % 10000 / 1000;
	aPosTexU[5] = g_HighScore % 1000 / 100;
	aPosTexU[6] = g_HighScore % 100 / 10;
	aPosTexU[7] = g_HighScore % 10 / 1;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHighScore = 0; nCntHighScore < MAX_HIGHSCORE; nCntHighScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntHighScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntHighScore] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntHighScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntHighScore] + 1), 1.0f);

		pVtx += 4;  //���_�f�[�^�̃|�C���^���S���i�߂�

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffHighScore->Unlock();
}

int GetHighScore(void)
{
	return g_HighScore;
}


//�t�@�C���ɏ������ޏ���
void SaveHighScore(void)
{
	FILE *pFile;		//�t�@�C���|�C���^��錾
	int nScore;

	nScore = GetScore();


	if (nScore > g_HighScore)
	{
		g_HighScore = nScore;
	}

	//�t�@�C�����J��
	pFile = fopen("HighScore.txt", "w");
	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�t�@�C�����當�����ǂݍ���
		fprintf(pFile, "%d", g_HighScore);

	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***?n");
	}

	//�t�@�C�������
	fclose(pFile);
}

//�t�@�C������ǂݍ��ޏ���
void LoadHighScore(void)
{
	FILE *pFile;		//�t�@�C���|�C���^��錾

	pFile = fopen("HighScore.txt", "r");
	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
	 //�t�@�C���ɕ�����������o��
		fscanf(pFile, "%d", &g_HighScore);
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***?n");
	}
}