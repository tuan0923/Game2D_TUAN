//========================================================
// block.cpp
// 2DGame
//Author: �e���A��
//========================================================
#include "block.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBlock[NUM_BLOCK] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;
BLOCK g_aBlock[MAX_BLOCK];

//================================================
//Block�̏�������
//================================================
void InitBlock(void)
{
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//block081.png", &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//blocknew1.jpg", &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//Block002.jpg", &g_pTextureBlock[2]);
	//�u���b�N�̏�񏉊���
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].nType = BLOCK_TYPE_S;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBlock = 0; nCntBlock<MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - (BLOCK_W / 2), g_aBlock[nCntBlock].pos.y - (BLOCK_H / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_W / 2), g_aBlock[nCntBlock].pos.y - (BLOCK_H / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - (BLOCK_W / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_H / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_W / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_H / 2), 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//�u���b�N�o��
	SetBlock(D3DXVECTOR3(300.0f, 700.0f, 0.0f), BLOCK_W*10, BLOCK_H, BLOCK_TYPE_S);
	SetBlock(D3DXVECTOR3(300.0f, 550.0f, 0.0f), BLOCK_W*1.5, BLOCK_H, BLOCK_TYPE_S);
	SetBlock(D3DXVECTOR3(1000.0f, 550.0f, 0.0f), BLOCK_W*1.5, BLOCK_H, BLOCK_TYPE_S);
	SetBlock(D3DXVECTOR3(650.0f, 400.0f, 0.0f), BLOCK_W/2, BLOCK_H, BLOCK_TYPE_MEDIUM);
	SetBlock(D3DXVECTOR3(300.0f, 320.0f, 0.0f), BLOCK_W , BLOCK_H, BLOCK_TYPE_MEDIUM);
	SetBlock(D3DXVECTOR3(1000.0f, 320.0f, 0.0f), BLOCK_W , BLOCK_H, BLOCK_TYPE_MEDIUM);
	SetBlock(D3DXVECTOR3(320.0f, 180.0f, 0.0f), BLOCK_W / 3, BLOCK_H, BLOCK_TYPE_MEDIUM);
	SetBlock(D3DXVECTOR3(950.0f, 180.0f, 0.0f), BLOCK_W / 3, BLOCK_H, BLOCK_TYPE_MEDIUM);
	SetBlock(D3DXVECTOR3(650.0f, 100.0f, 0.0f), BLOCK_W / 4, BLOCK_H, BLOCK_TYPE_MEDIUM);
	SetBlock(D3DXVECTOR3(650.0f, 650.0f, 0.0f), BLOCK_W / 3, BLOCK_H, BLOCK_TYPE_S);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();


}
//================================================
//Block�̏I������
//================================================
void UninitBlock(void)
{

	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
	//�e�N�X�`���j��
	for (int nCntBlock = 0; nCntBlock < NUM_BLOCK; nCntBlock++)
	{
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}

}
//================================================
//Block�̍X�V����
//================================================
void UpdateBlock(void)
{


}
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();	//�f�o�C�X�̎擾
	int nCntBlock;

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);



	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă���Ƃ�
		 //�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nCntBlock * 4, 2);
		}
	}
}
//================================================
//Block�̐ݒ菈��
//================================================
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, BLOCK_TYPE nType)
{
	VERTEX_2D *pVtx;
	int nCntBlock;
	
	//���_�o�b�t�@���b�N
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{//�e���g���Ă��Ȃ�
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bUse = true;
			//���_���W�̍X�V									
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - (fWidth / 2), g_aBlock[nCntBlock].pos.y - (fHeight / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (fWidth / 2), g_aBlock[nCntBlock].pos.y - (fHeight / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - (fWidth / 2), g_aBlock[nCntBlock].pos.y + (fHeight / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (fWidth / 2), g_aBlock[nCntBlock].pos.y + (fHeight / 2), 0.0f);

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffBlock->Unlock();

}
//================================================
//
//================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	bool bIsLanding = false; //���n���Ă��邩�ǂ���

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{

		if (g_aBlock[nCntBlock].bUse == true)
		{   //�ォ��
			if ((g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHeight / 2)) >= pPosOld->y
				&& (g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHeight / 2)) <= pPos->y
				&& (g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth / 2)) >= (pPos->x - fWidth)
				&& (g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth / 2)) <= (pPos->x + fWidth))

			{
				bIsLanding = true;	//���n���Ă���
				pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2;
				pMove->y = 0.0f;
			}
			//��

			if ((g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHeight / 2)) <= (pPosOld->y - fHeight)
				&& (g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHeight / 2)) >= (pPos->y - fHeight)
				&& (g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth / 2)) <= pPos->x
				&& (g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth / 2)) >= pPos->x)
			{
				bIsLanding = true;	//���n���Ă���
				pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + 70.0f;
				pMove->y = 0.0f;
			}
			if ((g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2) >= (pPosOld->y - fHeight)
				&& (g_aBlock[nCntBlock].pos.y - (g_aBlock[nCntBlock].fHeight / 2)) <= pPosOld->y)
			{
				if ((g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth / 2)) <= (pPosOld->x - fWidth)
					&& ((g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth / 2)) >= pPos->x - fWidth))
				{
					bIsLanding = true;
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2 + (fWidth / 2) + 12.5f;
					pMove->x = +0.0f;
					break;
				}
				else if ((g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth / 2)) >= pPosOld->x + fWidth
					&& ((g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth / 2)) <= pPos->x + fWidth))
				{
					bIsLanding = true;
					pPos->x = g_aBlock[nCntBlock].pos.x - (g_aBlock[nCntBlock].fWidth / 2) - (fWidth / 2) - 12.5f;
					pMove->x = -0.0f;
					break;
				}

			}

		}
	}
	return bIsLanding;

}