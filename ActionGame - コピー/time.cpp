//========================================================
// time.cpp
// 2DGame
//Author: �e���A��
//========================================================

//�C���N���[�h�t�@�C��
#include "time.h"
#include "result.h"
#include "fade.h"

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTime[3];							//�X�R�A�̈ʒu
int g_nTime;										//�X�R�A�̒l
int g_nCntTime;
int g_nCount;

//-------------------------------------------
//�^�C�}�[�̏���������
//-------------------------------------------
void InitTime(void)
{
	int nCount;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureTime);

	for (nCount = 0; nCount < TIME_MAX; nCount++)
	{
		g_posTime[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	g_nTime =60;
	int g_nCntTime = 60;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIME_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	g_posTime[0] = D3DXVECTOR3(1100.0f, 50.0f, 0.0f);
	g_posTime[1] = D3DXVECTOR3(1125.0f, 50.0f, 0.0f);
	g_posTime[2] = D3DXVECTOR3(1150.0f, 50.0f, 0.0f);

	for (nCount = 0; nCount < TIME_MAX; nCount++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTime[nCount].x - (TIME_WIDTH / 2), g_posTime[nCount].y - (TIME_HEIGHT / 2), 0);
		pVtx[1].pos = D3DXVECTOR3(g_posTime[nCount].x + (TIME_WIDTH / 2), g_posTime[nCount].y - (TIME_HEIGHT / 2), 0);
		pVtx[2].pos = D3DXVECTOR3(g_posTime[nCount].x - (TIME_WIDTH / 2), g_posTime[nCount].y + (TIME_HEIGHT / 2), 0);
		pVtx[3].pos = D3DXVECTOR3(g_posTime[nCount].x + (TIME_WIDTH / 2), g_posTime[nCount].y + (TIME_HEIGHT / 2), 0);

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

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//-------------------------------------------
//�^�C�}�[�̏I������
//-------------------------------------------
void UninitTime(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//-------------------------------------------
//�^�C�}�[�̍X�V����
//-------------------------------------------
void UpdateTime(void)
{
	int nCntTime;

	int nTimePos[3];

	if (g_nTime != 0)
	{
		g_nCntTime--;
	}

	if (g_nCntTime <= 0)
	{
		g_nTime--;

		g_nCntTime = 60;
	}

	nTimePos[0] = g_nTime % 1000 / 100;
	nTimePos[1] = g_nTime % 100 / 10;
	nTimePos[2] = g_nTime % 10;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime] + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();

	if (g_nTime == 0)
	{
		
		SetMode(MODE_RESULT);
		
		
	}
}

//-------------------------------------------
//�^�C�}�[�̕`�揈��
//-------------------------------------------
void DrawTime(void)
{
	int nCntTime;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureTime);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}