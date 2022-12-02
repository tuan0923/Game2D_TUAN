//-------------------------------------------
//
//�^�C�}�[����[time.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "time.h"
#include "fade.h"
//�}�N����`
#define TIME_WIDTH		(20.0f)		//�^�C���̕�
#define TIME_HEIGHT		(45.0f)		//�^�C���̍���
#define NUM_TIME		(3)			//�^�C���̍ő包��

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureTime[2] = {};			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime[2] = {};		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTime[NUM_TIME];					//�^�C���̈ʒu
int g_nTime;										//�^�C���̒l
int g_nCntTime;										//���t���[����

//-------------------------------------------
//�^�C�}�[�̏���������
//-------------------------------------------
void InitTime(void)
{
	for (int nCount = 0; nCount < NUM_TIME; nCount++)
	{//�ʒu�̏�����
		g_posTime[nCount] = D3DXVECTOR3(615.0f + (25.0f * nCount), 30.0f, 0.0f);
	}
	g_nTime = 90;						//���b�Ԃ�
	g_nCntTime = 60;					//60�t���[��

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
		&g_pTextureTime[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime[0],
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime[0]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (80.0f / 2.0f), 30.0f - (50.0f / 2.0f), 0);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (80.0f / 2.0f), 30.0f - (50.0f / 2.0f), 0);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (80.0f / 2.0f), 30.0f + (50.0f / 2.0f), 0);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (80.0f / 2.0f), 30.0f + (50.0f / 2.0f), 0);

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
	g_pVtxBuffTime[0]->Unlock();

	//--------------------------------�����̏���----------------------------------------------------

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureTime[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime[1],
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_TIME; nCount++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTime[nCount].x - (TIME_WIDTH / 2.0f), g_posTime[nCount].y - (TIME_HEIGHT / 2.0f), 0);
		pVtx[1].pos = D3DXVECTOR3(g_posTime[nCount].x + (TIME_WIDTH / 2.0f), g_posTime[nCount].y - (TIME_HEIGHT / 2.0f), 0);
		pVtx[2].pos = D3DXVECTOR3(g_posTime[nCount].x - (TIME_WIDTH / 2.0f), g_posTime[nCount].y + (TIME_HEIGHT / 2.0f), 0);
		pVtx[3].pos = D3DXVECTOR3(g_posTime[nCount].x + (TIME_WIDTH / 2.0f), g_posTime[nCount].y + (TIME_HEIGHT / 2.0f), 0);

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

		pVtx += 4;		//���_����4���i�߂�
	}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTime[1]->Unlock();
}

//-------------------------------------------
//�^�C�}�[�̏I������
//-------------------------------------------
void UninitTime(void)
{
	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (g_pTextureTime[nCount] != NULL)
		{
			g_pTextureTime[nCount]->Release();
			g_pTextureTime[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (g_pVtxBuffTime[nCount] != NULL)
		{
			g_pVtxBuffTime[nCount]->Release();
			g_pVtxBuffTime[nCount] = NULL;
		}
	}
}

//-------------------------------------------
//�^�C�}�[�̍X�V����
//-------------------------------------------
void UpdateTime(void)
{
	// �t�F�[�h���̎擾
	FADE fade = GetFade();

	int nTimePos[3];		//�^�C���̃e�N�X�`���ʒu

	if (g_nTime != 0)
	{//�^�C�}�[��0�ł͂Ȃ�������
		g_nCntTime--;		//�t���[���������炷
	}

	if (g_nCntTime <= 0)
	{//�t���[������0��菬�����Ȃ�����
		g_nTime--;					//�^�C�}�[��1���炷
									
		g_nCntTime = 90;			//�t���[������90�ɖ߂�
	}

	if (g_nTime <= 0 && fade == FADE_NONE)
	{
		SetFade(MODE_END);
		return;
	}

	//�����̃e�N�X�`�����i�[
	nTimePos[0] = g_nTime % 1000 / 100;
	nTimePos[1] = g_nTime % 100 / 10;
	nTimePos[2] = g_nTime % 10;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	{//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime] + 0.1f, 1.0f);

		pVtx += 4;		//�f�[�^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime[1]->Unlock();
}

//-------------------------------------------
//�^�C�}�[�̕`�揈��
//-------------------------------------------
void DrawTime(void)
{
	for (int nCntTime = 0; nCntTime < 2; nCntTime++)
	{
		//�f�o�C�X�ւ̃|�C���^
		LPDIRECT3DDEVICE9 pDevice;

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffTime[nCntTime], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�A���t�@�e�X�g��L��
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		switch (nCntTime)
		{
		case 0:			//0��������w�i��`��
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureTime[0]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			break;
		case 1:			//1�������琔����`��
		for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureTime[1]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
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