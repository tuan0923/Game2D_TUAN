//========================================================
// enemy.cpp
// 2DGame
//Author: �e���A��
//========================================================
#include "main.h"
#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "sound.h"
#include "game.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];

//================================================
//�G�̏���������
//================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//enemy004.png",
		&g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//enemy005.png",
		&g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//enemy006.png",
		&g_apTextureEnemy[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D *pVtx;  //���_���ւ̃|�C���^

	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		g_aEnemy[nCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCount].fHeight = ENEMY_HEIGHT;
		g_aEnemy[nCount].fWidth = ENEMY_WIDTH;
		g_aEnemy[nCount].nType = ENEMY_Q;
		g_aEnemy[nCount].bUse = false;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - ENEMY_WIDTH, g_aEnemy[nCount].pos.y - ENEMY_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + ENEMY_WIDTH, g_aEnemy[nCount].pos.y - ENEMY_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - ENEMY_WIDTH, g_aEnemy[nCount].pos.y + ENEMY_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + ENEMY_WIDTH, g_aEnemy[nCount].pos.y + ENEMY_HEIGHT, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.50f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;  //���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
	SetEnemy(D3DXVECTOR3(250.0f, 500.0f, 0.0f), ENEMY_Q, D3DXVECTOR3(-1.0f, 0.0f, 0.0f));

	SetEnemy(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), ENEMY_W, D3DXVECTOR3(1.0f, 0.0f, 0.0f));

	SetEnemy(D3DXVECTOR3(650.0f, 355.0f, 0.0f), ENEMY_E, D3DXVECTOR3(-1.0f, 0.0f, 0.0f));

}
//================================================
//�G�l�~�[�̏I������
//================================================

void UninitEnemy(void)
{
	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < NUM_ENEMY; nCount++)
	{
		if (g_apTextureEnemy[nCount] != NULL)
		{
			g_apTextureEnemy[nCount]->Release();
			g_apTextureEnemy[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//================================================
//
//================================================
void UpdateEnemy(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		if (g_aEnemy[nCount].bUse == true)
		{//�G���g�p����Ă���
			g_aEnemy[nCount].nCountAnimEnemy++;		//�J�E���^�[�����Z
			if (g_aEnemy[nCount].nCountAnimEnemy % 15 == 0)
			{
				g_aEnemy[nCount].nPatternAnimEnemy++;//�p�^�[��No.���X�V
			}

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2((0.0f + (0.5*g_aEnemy[nCount].nPatternAnimEnemy)), 0.0f);
			pVtx[1].tex = D3DXVECTOR2((0.5f + (0.5*g_aEnemy[nCount].nPatternAnimEnemy)), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((0.0f + (0.5*g_aEnemy[nCount].nPatternAnimEnemy)), 1.0f);
			pVtx[3].tex = D3DXVECTOR2((0.5f + (0.5*g_aEnemy[nCount].nPatternAnimEnemy)), 1.0f);

			//�ʒu���X�V
			g_aEnemy[nCount].pos.x += g_aEnemy[nCount].move.x;
			g_aEnemy[nCount].pos.y += g_aEnemy[nCount].move.y;
			if (g_aEnemy[nCount].nType == ENEMY_Q)
			{
				if (g_aEnemy[nCount].pos.x >= SCREEN_WIDTH - 870.0f)
				{
					g_aEnemy[nCount].move.x = -1;
				}
				if (g_aEnemy[nCount].pos.x <= 0.0f + 200.0f)
				{
					g_aEnemy[nCount].move.x = +1;
				}
			}
			if (g_aEnemy[nCount].nType == ENEMY_W)
			{
				if (g_aEnemy[nCount].pos.x >= SCREEN_WIDTH - 150.0f)
				{
					g_aEnemy[nCount].move.x = -1;
				}
				if (g_aEnemy[nCount].pos.x <= 0.0f + 850.0f)
				{
					g_aEnemy[nCount].move.x = +1;
				}
			}
			if (g_aEnemy[nCount].nType == ENEMY_E)
			{
				if (g_aEnemy[nCount].pos.x >= SCREEN_WIDTH - 570.0f)
				{
					g_aEnemy[nCount].move.x = -1;
				}
				if (g_aEnemy[nCount].pos.x <= 0.0f + 580.0f)
				{
					g_aEnemy[nCount].move.x = +1;
				}
			}
		
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - ENEMY_WIDTH, g_aEnemy[nCount].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + ENEMY_WIDTH, g_aEnemy[nCount].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - ENEMY_WIDTH, g_aEnemy[nCount].pos.y + ENEMY_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + ENEMY_WIDTH, g_aEnemy[nCount].pos.y + ENEMY_HEIGHT, 0.0f);
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();


}
//================================================
//�G�l�~�[�̕`�揈��
//================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�G�̕`��
	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		if (g_aEnemy[nCount].bUse == true)
		{//�G���g�p����Ă���
		 //�e�N�X�`���̐ݒ�

			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCount].nType]);
			//�G�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCount * 4,
				2);
		}
	}
}
//================================================
//
//================================================
void SetEnemy(D3DXVECTOR3 pos, ENEMY_TYPE nType, D3DXVECTOR3 move)
{

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		if (g_aEnemy[nCount].bUse == false)
		{
			g_aEnemy[nCount].pos = pos;
			g_aEnemy[nCount].move = move;
			g_aEnemy[nCount].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_aEnemy[nCount].nType = nType;

			break;

		}
		//pVtx += 4;  //���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
//================================================
//
//================================================
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		if (g_aEnemy[nCntEnemy].bUse == true)
		{   //�ォ��
			if ((g_aEnemy[nCntEnemy].pos.y - (g_aEnemy[nCntEnemy].fHeight / 2)) >= pPosOld->y
				&& (g_aEnemy[nCntEnemy].pos.y - (g_aEnemy[nCntEnemy].fHeight / 2)) <= pPos->y
				&& (g_aEnemy[nCntEnemy].pos.x + (g_aEnemy[nCntEnemy].fWidth / 2)) >= (pPos->x - fWidth)
				&& (g_aEnemy[nCntEnemy].pos.x - (g_aEnemy[nCntEnemy].fWidth / 2)) <= (pPos->x + fWidth))

			{
				pPos->y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight / 2 - 30.0f;
				pMove->y = 0.0f;
				
				SetExplosion(g_aEnemy[nCntEnemy].pos, 255, EXPLOSION_W);
				PlaySound(SOUND_LABEL_SE_DAMAGE);
				DeleteEnemy(nCntEnemy);
				AddScore(200);
				break;
			}
			//��

			if ((g_aEnemy[nCntEnemy].pos.y + (g_aEnemy[nCntEnemy].fHeight / 2)) <= (pPosOld->y - fHeight)
				&& (g_aEnemy[nCntEnemy].pos.y + (g_aEnemy[nCntEnemy].fHeight / 2)) >= (pPos->y - fHeight)
				&& (g_aEnemy[nCntEnemy].pos.x - (g_aEnemy[nCntEnemy].fWidth / 2)) <= pPos->x
				&& (g_aEnemy[nCntEnemy].pos.x + (g_aEnemy[nCntEnemy].fWidth / 2)) >= pPos->x)
			{

				pPos->y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight;
				pMove->y = 0.0f;
			}
			if ((g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight / 2) >= (pPosOld->y - fHeight)
				&& (g_aEnemy[nCntEnemy].pos.y - (g_aEnemy[nCntEnemy].fHeight / 2)) <= pPosOld->y)
			{
				if ((g_aEnemy[nCntEnemy].pos.x + (g_aEnemy[nCntEnemy].fWidth / 2)) <= (pPosOld->x - fWidth)
					&& ((g_aEnemy[nCntEnemy].pos.x + (g_aEnemy[nCntEnemy].fWidth / 2)) >= pPos->x - fWidth))
				{

					pPos->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth / 2 + (fWidth / 2) + 50.5f;
					pMove->x = +0.0f;
					HitPlayer();
					AddScore(-50);
					PlaySound(SOUND_LABEL_SE_HIT);
					break;
				}
				else if ((g_aEnemy[nCntEnemy].pos.x - (g_aEnemy[nCntEnemy].fWidth / 2)) >= pPosOld->x + fWidth
					&& ((g_aEnemy[nCntEnemy].pos.x - (g_aEnemy[nCntEnemy].fWidth / 2)) <= pPos->x + fWidth))
				{

					pPos->x = g_aEnemy[nCntEnemy].pos.x - (g_aEnemy[nCntEnemy].fWidth / 2) - (fWidth / 2) - 50.5f;
					pMove->x = -0.0f;
					HitPlayer();
					AddScore(-50);
					PlaySound(SOUND_LABEL_SE_HIT);
					break;
				}

			}

		}
	}
}
//===========================================
//
//===========================================
void DeleteEnemy(int nCntEnemy)
{
	g_aEnemy[nCntEnemy].bUse = false;
}
//-------------------------------------------
//
//-------------------------------------------
Enemy * GetEnemy(void)
{
	return g_aEnemy;

}


