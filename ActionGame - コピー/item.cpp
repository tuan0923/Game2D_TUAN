//========================================================
// item.cpp
// 2DGame
//Author: �e���A��
//========================================================
#include"main.h"
#include "item.h"
#include "time.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureItem[NUM_ITEM] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;
ITEM g_Item[MAX_ITEM];
int g_ItemTotalNum;

//================================================
//����������
//================================================
void InitItem(void)
{
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//coin000.png", &g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//Diamond.png", &g_pTextureItem[1]);
	//Item�̏�񏉊���
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_Item[nCntItem].nCountAnim = 0;
		g_Item[nCntItem].nPatternAnim = 0;
		g_Item[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntItem].fWidth = ITEM_WIDTH;
		g_Item[nCntItem].fHeight = ITEM_HEIGHT;
		g_Item[nCntItem].bUse = false;
		g_Item[nCntItem].ntype = ITEM_TYPE_COIN;

	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

		pVtx += 4;
	}
	//Item�o��
	SetItem(D3DXVECTOR3(200.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(250.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(300.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(350.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(400.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);

	SetItem(D3DXVECTOR3(1100.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(1000.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(1050.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(950.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(900.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);

	SetItem(D3DXVECTOR3(250.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(400.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(350.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(300.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);

	SetItem(D3DXVECTOR3(930.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(980.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(1030.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(1080.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);

	SetItem(D3DXVECTOR3(650.0f, 320.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(315.0f, 120.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(950.0f, 120.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(650.0f, 30.0f, 0.0f), ITEM_TYPE_MAX);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}
//================================================
//Item�̏I������
//================================================
void UninitItem(void)
{

	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
	//�e�N�X�`���j��
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem]->Release();
			g_pTextureItem[nCntItem] = NULL;
		}
	}
}
//================================================
//
//================================================
void UpdateItem(void)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	int nCntItem;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾									
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_Item[nCntItem].nCountAnim++;		//�J�E���^�[�����Z
		if (g_Item[nCntItem].nCountAnim % 15 == 0)
		{
			g_Item[nCntItem].nPatternAnim++;//�p�^�[��No.���X�V
		}
		
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((0.0f + (0.25*g_Item[nCntItem].nPatternAnim)), 0.0f );
		pVtx[1].tex = D3DXVECTOR2((0.25f + (0.25*g_Item[nCntItem].nPatternAnim)), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((0.0f + (0.25*g_Item[nCntItem].nPatternAnim)), 1.0f );
		pVtx[3].tex = D3DXVECTOR2((0.25f + (0.25*g_Item[nCntItem].nPatternAnim)), 1.0f );
		pVtx += 4;
	}
	
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}
//================================================
//
//================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{//�u���b�N���g�p����Ă���Ƃ�
		 //�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_Item[nCntItem].ntype]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nCntItem * 4, 2);
		}
	}
}
//================================================
//
//================================================
void SetItem(D3DXVECTOR3 pos, ITEM_TYPE type)
{
	VERTEX_2D *pVtx;
	
	//���_�o�b�t�@���b�N
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == false)
		{//item���g���Ă��Ȃ�
			g_Item[nCntItem].pos = pos;
			g_Item[nCntItem].ntype = type;
			g_Item[nCntItem].bUse = true;
			//���_���W�̍X�V									
			pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffItem->Unlock();
}
//================================================
//
//================================================
void CollisionItem(D3DXVECTOR3 *pPos, float fWidth, float fHeight)
 {
	 ITEM * pItem;
	 int nCntItem;
	 pItem = GetItem();
	
	 for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	 {
		 if (pItem->bUse == true)
		 {
			 if ((pItem->pos.x - (fWidth / 2)) <= (pPos->x + (fWidth / 2)) &&
				 (pItem->pos.x + (fWidth / 2)) >= (pPos->x - (fWidth / 2)) &&
				 (pItem->pos.y - (fHeight / 2)) <= (pPos->y) &&
				 (pItem->pos.y + (fHeight / 2) >= pPos->y - (fHeight)))
			 {
				 DeleteItem(nCntItem);
			 }			
		 }
		 pItem++;
	 }
 }
//================================================
//
//================================================
void DeleteItem(int nCntItem)
{
	if (g_Item[nCntItem].ntype == ITEM_TYPE_COIN)
	{
		g_Item[nCntItem].bUse = false;
		SetExplosion(g_Item[nCntItem].pos, 255, EXPLOSION_Q);
		AddScore(100);
		PlaySound(SOUND_LABEL_SE_COIN);
	} 
	if (g_Item[nCntItem].ntype == ITEM_TYPE_MAX)
	{
		AddScore(1000);
		g_Item[nCntItem].bUse = false;

		PlaySound(SOUND_LABEL_SE_ITEM);
		SetExplosion(g_Item[nCntItem].pos, 255, EXPLOSION_Q);
		SetFade(MODE_RESULT);
	}
}
//================================================
//
//================================================
 ITEM*GetItem(void)
 {
	 return g_Item;

 }
