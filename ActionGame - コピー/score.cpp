//========================================================
// score.cpp
// 2DGame
//Author: �e���A��
//========================================================
#include "score.h"
#include "Highscore.h"
#include "game.h"
#include "result.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore;							//�X�R�A�̈ʒu
int g_nScore;										//�X�R�A�̒l
//-------------------------------------------
//����������
//-------------------------------------------
void InitScore(void)
{
	int nCount;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//number000.png",
		&g_pTextureScore);

		g_posScore = D3DXVECTOR3(200.0f, 40.0f, 0.0f);
	
	g_nScore = 0;													

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	
	for (nCount = 0; nCount < SCORE_MAX; nCount++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - (SCORE_WIDTH / 2) + SCORE_WIDTH * nCount, g_posScore.y - (SCORE_HEIGHT / 2), 0);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + (SCORE_WIDTH / 2) + SCORE_WIDTH * nCount, g_posScore.y - (SCORE_HEIGHT / 2), 0);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - (SCORE_WIDTH / 2) + SCORE_WIDTH * nCount, g_posScore.y + (SCORE_HEIGHT / 2), 0);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + (SCORE_WIDTH / 2) + SCORE_WIDTH * nCount, g_posScore.y + (SCORE_HEIGHT / 2), 0);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
	SetScore(0, g_posScore, SCORE_WIDTH, SCORE_HEIGHT);
	SetScore(0, D3DXVECTOR3(500.0f, 40.0f, 0.0f), SCORE_WIDTH, SCORE_HEIGHT);

}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateScore(void)
{
	
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawScore(void)
{
	int nCntScore;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureScore);
	for (nCntScore = 0; nCntScore < SCORE_MAX; nCntScore++)
	{
		
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//-------------------------------------------
//�X�R�A�̐ݒ菈��
//-------------------------------------------
void SetScore(int nScore, D3DXVECTOR3 pos, float width, float height)
{//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	int aPosTexScore[SCORE_MAX];			//�e���̐������i�[
	int nCountScore;

	g_nScore = nScore;
	g_posScore = pos;
	aPosTexScore[0] = g_nScore % 100000000 / 10000000;
	aPosTexScore[1] = g_nScore % 10000000 / 1000000;
	aPosTexScore[2] = g_nScore % 1000000 / 100000;
	aPosTexScore[3] = g_nScore % 100000 / 10000;
	aPosTexScore[4] = g_nScore % 10000 / 1000;
	aPosTexScore[5] = g_nScore % 1000 / 100;
	aPosTexScore[6] = g_nScore % 100 / 10;
	aPosTexScore[7] = g_nScore % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (nCountScore = 0; nCountScore < SCORE_MAX; nCountScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - width / 2 + width * nCountScore, g_posScore.y - height / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + width / 2 + width * nCountScore, g_posScore.y - height / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - width / 2 + width * nCountScore, g_posScore.y + height / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + width / 2 + width * nCountScore, g_posScore.y + height / 2, 0.0f);

		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore] + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//-------------------------------------------
//�X�R�A�̉��Z����
//-------------------------------------------
void AddScore(int nValue)
{
	int aPosTexScore[SCORE_MAX];		//�e���̐������i�[
	int nCountScore;

	g_nScore += nValue;
	if (g_nScore <= 0)
	{
		g_nScore = 0;
	}
	aPosTexScore[0] = g_nScore % 100000000 / 10000000;
	aPosTexScore[1] = g_nScore % 10000000 / 1000000;
	aPosTexScore[2] = g_nScore % 1000000 / 100000;
	aPosTexScore[3] = g_nScore % 100000 / 10000;
	aPosTexScore[4] = g_nScore % 10000 / 1000;
	aPosTexScore[5] = g_nScore % 1000 / 100;
	aPosTexScore[6] = g_nScore % 100 / 10;
	aPosTexScore[7] = g_nScore % 10 / 1;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (nCountScore = 0; nCountScore < SCORE_MAX; nCountScore++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore] + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

int GetScore(void)
{
	return g_nScore;
}