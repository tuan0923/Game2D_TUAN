//========================================================
// explosion.cpp
// 2DGame
//Author: �e���A��
//========================================================
#include "main.h"
#include "explosion.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExplosion[NUM_EXPLOSION] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
Explosion g_aExplosion[MAX_EXPLOSION];

//================================================
//�����̏���������
//================================================
void InitExplosion(void)
{
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//effect001.png",
		&g_pTextureExplosion[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//explosion000.png",
		&g_pTextureExplosion[1]);
	//�����̏��̏���������
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].ntype = EXPLOSION_Q;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE_Y, 0.0f);

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
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
//================================================
//
//================================================
void UninitExplosion(void)
{
	//�e�N�X�`���j��
	for (int nCntExplosion = 0; nCntExplosion < NUM_EXPLOSION; nCntExplosion++)
	{
		if (g_pTextureExplosion[nCntExplosion] != NULL)
		{
			g_pTextureExplosion[nCntExplosion]->Release();
			g_pTextureExplosion[nCntExplosion] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//================================================
//
//================================================
void UpdateExplosion(void)
{
	VERTEX_2D *pVtx;
	int nCntExplosion;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//�e�N�X�`���̃A�j���[�V����
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if (g_aExplosion[nCntExplosion].nCounterAnim % 8 == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnim++;
				if (g_aExplosion[nCntExplosion].nPatternAnim > 5)
				{
					g_aExplosion[nCntExplosion].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
				}
			}
				//�e�N�X�`���̍��W�ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.25f * g_aExplosion[nCntExplosion].nPatternAnim), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + (0.25f * g_aExplosion[nCntExplosion].nPatternAnim), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.25f * g_aExplosion[nCntExplosion].nPatternAnim), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + (0.25f * g_aExplosion[nCntExplosion].nPatternAnim), 1.0f);
				pVtx += 4;

			}			
		}
	//���_���W���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}
//================================================
//
//================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, EXPLOSION_TYPE ntype)
{
	VERTEX_2D *pVtx;
	int nCntExplosion;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//�������g�p����Ă��Ȃ�
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].ntype = ntype;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].bUse = true;
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE_Y, 0.0f);
			////�e�N�X�`��
			//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	//���_���W���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}
//================================================
//
//================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();	//�f�o�C�X�̎擾
	int nCntExplosion;

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//�e���g�p����Ă���Ƃ�
		 //�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion[g_aExplosion[nCntExplosion].ntype]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);

		}
	}
}