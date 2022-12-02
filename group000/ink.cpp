//============================================================
//
// 3D�C���N�̏��� [Ink.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "ink.h"
#include "main.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//============================================================
//�}�N����`
//============================================================
#define MAX_Ink		(256)	//�C���N�̍ő吔
#define Ink_SIZE	(60)	//�C���N�̃T�C�Y

//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureInk = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffInk = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Ink g_aInk[MAX_Ink];						//�C���N

//============================================================
// �C���N�̏�����
//============================================================
void lnitInk(void)
{
	int nCntInk;
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ink.png",					//shadow000.jpg"
		&g_pTextureInk);

	//�C���N�̏��̏�����
	for (nCntInk = 0; nCntInk< MAX_Ink; nCntInk++)
	{
		g_aInk[nCntInk].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aInk[nCntInk].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aInk[nCntInk].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aInk[nCntInk].move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aInk[nCntInk].bUse = false;
	}
	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_Ink,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffInk,
		NULL);

	//���_���փ|�C���^
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffInk->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntInk = 0; nCntInk < MAX_Ink; nCntInk++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-55.0f, 0.0f, 55.0f);
		pVtx[1].pos = D3DXVECTOR3(55.0f, 0.0f, 55.0f);
		pVtx[2].pos = D3DXVECTOR3(-55.0f, 0.0f, -55.0f);
		pVtx[3].pos = D3DXVECTOR3(55.0f, 0.0f, -55.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̕`��
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx += 4;
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffInk->Unlock();

	srand((unsigned int)time(NULL));

	//�v���C���[1�̃G���A
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 10 + -400.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 10 + -400.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 10 + -400.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));

	//�v���C���[2�̃G���A
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 400 + 100.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 400 + 100.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 400 + 100.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
}

//============================================================
// �C���N�̏I������
//============================================================
void UninitInk(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureInk != NULL)
	{
		g_pTextureInk->Release();
		g_pTextureInk = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffInk != NULL)
	{
		g_pVtxBuffInk->Release();
		g_pVtxBuffInk = NULL;
	}
}

//============================================================
// �C���N�̍X�V����
//============================================================
void UpdateInk(void)
{

}

//============================================================
// �C���N�̐ݒ�
//============================================================
int SetInk(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntInk;

	for (nCntInk = 0; nCntInk<MAX_Ink; nCntInk++)
	{
		//bUse��false�̏ꍇ�Apos,rot������bUse��true�ɂ���
		if (g_aInk[nCntInk].bUse == false)
		{
			g_aInk[nCntInk].pos = pos;
			g_aInk[nCntInk].rot = rot;
			g_aInk[nCntInk].bUse = true;

			g_aInk[nCntInk].size.x = (g_aInk[nCntInk].pos.x) / 2.0f;
			g_aInk[nCntInk].size.y = (g_aInk[nCntInk].pos.y);
			g_aInk[nCntInk].size.z = (g_aInk[nCntInk].pos.z) / 2.0f;
			break;
		}
	}
	return nCntInk;//�C���N�̔ԍ�(index��Ԃ��j
}
//============================================================
// �C���N�̈ʒu�̍X�V����
//============================================================
void SetPositionInk(int nldxInk, D3DXVECTOR3 pos)
{
	//�����Ŏw�肳�ꂽ�ԍ��̃C���N��pos��ݒ�
	g_aInk[nldxInk].pos = pos;
}
//============================================================
// �C���N�̕`�揈��
//============================================================
void DrawInk(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	for (int nCntInk = 0; nCntInk < MAX_Ink; nCntInk++)
	{
		if (g_aInk[nCntInk].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aInk[nCntInk].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aInk[nCntInk].rot.y, g_aInk[nCntInk].rot.x, g_aInk[nCntInk].rot.z);
			D3DXMatrixMultiply(&g_aInk[nCntInk].mtxWorld, &g_aInk[nCntInk].mtxWorld, &mtxRot);

			//�ʒu�𔽉f.
			D3DXMatrixTranslation(&mtxTrans, g_aInk[nCntInk].pos.x, g_aInk[nCntInk].pos.y, g_aInk[nCntInk].pos.z);
			D3DXMatrixMultiply(&g_aInk[nCntInk].mtxWorld, &g_aInk[nCntInk].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aInk[nCntInk].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffInk, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureInk);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntInk * 4, 2);
		}
	}
	
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}
//============================================================
// �G�l�~�[�̓����蔻��
//============================================================
bool CollisionInk(
	D3DXVECTOR3* pPos,				//���݂̈ʒu
	D3DXVECTOR3* pPosOld,			//�O��̍���
	D3DXVECTOR3* pMove,				//�ړ���
	D3DXVECTOR3* pSize)//�T�C�Y
{
	bool bIsLanding = false;		//���n���Ă��邩�ǂ���

	for (int nCntInk = 0; nCntInk<MAX_Ink; nCntInk++)
	{
		if (g_aInk[nCntInk].bUse == true)//�g�p���Ă���ꍇ
		{
			/*Player*pPlayer;
			pPlayer = GetPlayer();
			*/
			//�E�̓����蔻��
			if (pPos->z - pSize->z <g_aInk[nCntInk].pos.z + g_aInk[nCntInk].size.z &&
				pPos->z + pSize->z >g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z &&

				pPos->y - pSize->y <g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y &&
				pPos->y + pSize->y >g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y &&

				pPosOld->x >= g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x + pSize->x &&
				pPos->x < g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x + pSize->x)

				//�C���N�ɂ߂荞��
			{
				pPos->x = g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x + pSize->x;
				pMove->x = 0.0f;
			}

			//���̓����蔻��
			if (pPos->z - pSize->z < g_aInk[nCntInk].pos.z + g_aInk[nCntInk].size.z &&
				pPos->z + pSize->z > g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z &&

				pPos->y - pSize->y < g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y &&
				pPos->y + pSize->y > g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y &&

				pPosOld->x <= g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x - pSize->x &&
				pPos->x > g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x - pSize->x)

				//�C���N�ɂ߂荞��
			{
				pPos->x = g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x - pSize->x;
				pMove->x = 0.0f;
			}

			//���ʂ̓����蔻��
			if (pPos->x - pSize->x < g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x &&
				pPos->x + pSize->x > g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x &&

				pPos->z - pSize->z < g_aInk[nCntInk].pos.z + g_aInk[nCntInk].size.z &&
				pPos->z + pSize->z > g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z &&

				pPosOld->y <= g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y - pSize->y &&
				pPos->y > g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y - pSize->y)
				//�C���N�ɂ߂荞��
			{
				pPos->y = g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y - pSize->y;
				pMove->y = 0.0f;
			}
			//���ʓ����蔻��
			if (pPos->x - pSize->x < g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x &&
				pPos->x + pSize->x > g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x &&

				pPos->y - pSize->y < g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y &&
				pPos->y + pSize->y > g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y &&

				pPosOld->z <= g_aInk[nCntInk].pos.z + g_aInk[nCntInk].size.z - pSize->z &&
				pPos->z > g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z - pSize->z)

				//�C���N�ɂ߂荞��
			{
				pPos->z = g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z - pSize->z;
				pMove->z = 0.0f;
			}

			//��ʂ̓����蔻��
			if (pPos->x - pSize->x < g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x &&
				pPos->x + pSize->x > g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x &&

				pPos->z - pSize->z < g_aInk[nCntInk].pos.z + g_aInk[nCntInk].size.z &&
				pPos->z + pSize->z > g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z &&

				pPosOld->y >= g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y + pSize->y &&
				pPos->y < g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y + pSize->y)
				//�C���N�ɂ߂荞��
			{
				bIsLanding = true;
				pPos->y = g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y + pSize->y;
				pMove->y = 0.0f;
			}

		}
	}

	return bIsLanding;
}
