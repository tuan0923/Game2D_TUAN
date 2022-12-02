//----------------------------------------
//�@�S�[������
//�@Author�F���슲��
//----------------------------------------
#include "goal.h"
#include "mob.h"
#include "player.h"
#include "score.h"
#include "disc.h"
#include"sound.h"
//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;			//�e�N�X�`���ւ̃|�C���^
Goal g_aGoal;

//----------------------------------------
//	�S�[���̏���������
//
//	X �� �����̔��a		Y �� �c���̔��a
//----------------------------------------
void InitGoal(float X, float Z)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\goal_000.png",	//�e�N�X�`�������
		&g_pTextureGoal);

	//�e�l������
	g_aGoal.pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);	//�ʒu
	g_aGoal.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�p�x
	g_aGoal.fWidth = X;		//����
	g_aGoal.fHeight = Z;	//�c��

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aGoal.pos.x - g_aGoal.fWidth, g_aGoal.pos.y, g_aGoal.pos.z + g_aGoal.fHeight);
	pVtx[1].pos = D3DXVECTOR3(g_aGoal.pos.x + g_aGoal.fWidth, g_aGoal.pos.y, g_aGoal.pos.z + g_aGoal.fHeight);
	pVtx[2].pos = D3DXVECTOR3(g_aGoal.pos.x - g_aGoal.fWidth, g_aGoal.pos.y, g_aGoal.pos.z - g_aGoal.fHeight);
	pVtx[3].pos = D3DXVECTOR3(g_aGoal.pos.x + g_aGoal.fWidth, g_aGoal.pos.y, g_aGoal.pos.z - g_aGoal.fHeight);

	//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�a
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffGoal->Unlock();
}

//----------------------------------------
//	�S�[���̏I������
//----------------------------------------
void UninitGoal(void)
{
	//�T�E���h�̒�~
	StopSound();
	//���_�o�b�t�@�j��
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}
}

//----------------------------------------
//	�S�[���̍X�V����
//----------------------------------------
void UpdateGoal(void)
{
	//�����Ȃ�
}

//----------------------------------------
//	�S�[���̕`�揈��
//----------------------------------------
void DrawGoal(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureGoal);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aGoal.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGoal.rot.y, g_aGoal.rot.x, g_aGoal.rot.z);
	D3DXMatrixMultiply(&g_aGoal.mtxWorld, &g_aGoal.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_aGoal.pos.x, g_aGoal.pos.y, g_aGoal.pos.z);
	D3DXMatrixMultiply(&g_aGoal.mtxWorld, &g_aGoal.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_aGoal.mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//�v���~�e�B�u�̎��

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureGoal);
}

//----------------------------------------
//	�S�[���̓����蔻�菈��
//----------------------------------------
void CollisionGoal(D3DXVECTOR3 pos, bool *bUse, int type)
{
	Player *pPlayer = GetPlayer();
	MOB *pMob = GetMob();

	float fPosZ = 0.0f;

	switch (type)
	{
	case 0:
		if (g_aGoal.pos.z + g_aGoal.fHeight >= pos.z &&
			g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f) <= pos.z)
		{//2P��(����)
			if (g_aGoal.pos.x - g_aGoal.fWidth < pos.x &&
				g_aGoal.pos.x - g_aGoal.fWidth + (g_aGoal.fWidth / 1.5f) > pos.x)
			{//1P��3�_�l��
				*bUse = false;		//false�ɂ���

				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(0, 3);//1P��3�_�ǉ�

				if (pMob->pos.z > g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f))
				{//�����v���C���[���S�[�����ɋ�����
					fPosZ = g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f);	//�S�[���̊O���ɂ���ݒ�
				}
				else
				{
					fPosZ = pMob->pos.z - 30.0f;	//���̂܂܂̒l
				}

				SetPosDisc(D3DXVECTOR3(pMob->pos.x, pMob->pos.y + 30.0f, fPosZ), 1);
			}
			if (g_aGoal.pos.x + g_aGoal.fWidth > pos.x &&
				g_aGoal.pos.x + g_aGoal.fWidth - (g_aGoal.fWidth / 1.5f) < pos.x)
			{//1P��3�_�l��
				*bUse = false;		//false�ɂ���

				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(0, 3);		//1P��3�_�ǉ�

				if (pMob->pos.z > g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f))
				{//�����v���C���[���S�[�����ɋ�����
					fPosZ = g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f);	//�S�[���̊O���ɂ���ݒ�
				}
				else
				{
					fPosZ = pMob->pos.z - 30.0f;	//���̂܂܂̒l
				}

				SetPosDisc(D3DXVECTOR3(pMob->pos.x, pMob->pos.y + 30.0f, fPosZ), 1);
			}
			if (g_aGoal.pos.x - ((g_aGoal.fWidth / 1.5f) / 2.0f) < pos.x &&
				g_aGoal.pos.x + ((g_aGoal.fWidth / 1.5f) / 2.0f) > pos.x)
			{//1P��5�_�l��
				*bUse = false;		//false�ɂ���

				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(0, 5);		//1P��5�_�ǉ�

				if (pMob->pos.z > g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f))
				{//�����v���C���[���S�[�����ɋ�����
					fPosZ = g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f);	//�S�[���̊O���ɂ���ݒ�
				}
				else
				{
					fPosZ = pMob->pos.z - 30.0f;	//���̂܂܂̒l
				}

				SetPosDisc(D3DXVECTOR3(pMob->pos.x, pMob->pos.y + 30.0f, fPosZ), 1);
			}
		}

		if (pos.y <= g_aGoal.pos.y)
		{//���ɗ������Ƃ�
			if (g_aGoal.pos.x - g_aGoal.fWidth < pos.x &&
				g_aGoal.pos.x + g_aGoal.fWidth > pos.x)
			{
				if (g_aGoal.pos.z >= pos.z &&
					g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f) <= pos.z)
				{//1P�ɓ_�l��
					*bUse = false;		//false�ɂ���

					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_Score);

					AddScore(0, 2);		//1P��2�_�ǉ�

					if (pMob->pos.z > g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f))
					{//�����v���C���[���S�[�����ɋ�����
						fPosZ = g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f);	//�S�[���̊O���ɂ���ݒ�
					}
					else
					{
						fPosZ = pMob->pos.z - 30.0f;	//���̂܂܂̒l
					}

					SetPosDisc(D3DXVECTOR3(pMob->pos.x, pMob->pos.y + 30.0f, fPosZ), 1);
				}
			}
		}

		break;

	case 1:
		if (g_aGoal.pos.z - g_aGoal.fHeight < pos.z &&
			g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f) > pos.z)
		{//1P��(��O��)
			if (g_aGoal.pos.x - g_aGoal.fWidth < pos.x &&
				g_aGoal.pos.x - g_aGoal.fWidth + (g_aGoal.fWidth / 1.5f) > pos.x)
			{//2P��3�_�l��
				*bUse = false;		//false�ɂ���

				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(1, 3);		//2P��3�_�ǉ�

				if (pPlayer->pos.z < g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f))
				{//�����v���C���[���S�[�����ɋ�����
					fPosZ = g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f);	//�S�[���̊O���ɂ���ݒ�
				}
				else
				{
					fPosZ = pPlayer->pos.z + 30.0f;	//���̂܂܂̒l
				}

				SetPosDisc(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 30.0f, fPosZ), 0);
			}
			if (g_aGoal.pos.x + g_aGoal.fWidth > pos.x &&
				g_aGoal.pos.x + g_aGoal.fWidth - (g_aGoal.fWidth / 1.5f) < pos.x)
			{//2P��3�_�l��
				*bUse = false;		//false�ɂ���
				
				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(1, 3);		//2P��3�_�ǉ�

				if (pPlayer->pos.z < g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f))
				{//�����v���C���[���S�[�����ɋ�����
					fPosZ = g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f);	//�S�[���̊O���ɂ���ݒ�
				}
				else
				{
					fPosZ = pPlayer->pos.z + 30.0f;	//���̂܂܂̒l
				}

				SetPosDisc(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 30.0f, fPosZ), 0);
			}
			if (g_aGoal.pos.x - ((g_aGoal.fWidth / 1.5f) / 2.0f) < pos.x &&
				g_aGoal.pos.x + ((g_aGoal.fWidth / 1.5f) / 2.0f) > pos.x)
			{//2P��5�_�l��
				*bUse = false;		//false�ɂ���

				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(1, 5);		//2P��5�_�ǉ�

				if (pPlayer->pos.z < g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f))
				{//�����v���C���[���S�[�����ɋ�����
					fPosZ = g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f);	//�S�[���̊O���ɂ���ݒ�
				}
				else
				{
					fPosZ = pPlayer->pos.z + 30.0f;	//���̂܂܂̒l
				}

				SetPosDisc(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 30.0f, fPosZ), 0);
			}
		}

		if (pos.y <= g_aGoal.pos.y)
		{//���ɗ������Ƃ�
			if (g_aGoal.pos.x - g_aGoal.fWidth < pos.x &&
				g_aGoal.pos.x + g_aGoal.fWidth > pos.x)
			{
				if (g_aGoal.pos.z <= pos.z &&
					g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f) >= pos.z)
				{//2P�ɓ_�l��
					*bUse = false;		//false�ɂ���

					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_Score);

					AddScore(1, 2);		//2P��2�_�ǉ�

					if (pPlayer->pos.z > g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f))
					{//�����v���C���[���S�[�����ɋ�����
						fPosZ = g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f);	//�S�[���̊O���ɂ���ݒ�
					}
					else
					{
						fPosZ = pPlayer->pos.z + 30.0f;	//���̂܂܂̒l
					}

					SetPosDisc(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 30.0f, fPosZ), 0);
				}
			}
		}
		break;

	default:
		break;
	}
}