//============================================================
//
// 3D����@�G�l�~�[�i�C�J�j����[Enemy.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "enemy.h"
#include"score.h"
//============================================================
//�}�N����`
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);//�����W��
#define MAX_Enemy	(1280)				//���f���̍ő吔
#define NUM_Enemy	(2)				//���f����
#define ENEMY_G		(1.0f)
//============================================================
//�O���[�o���ϐ�
//============================================================
int g_nEnemyCounter;//�G�̃J�E���g

//��Enemyinfo�\���̂ɂ���
typedef struct
{
	//���\���̂ɂ�����,MAX_Enemy �� MAX_Enemy_TYPE 2
	LPD3DXMESH			 MeshEnemy;
	LPD3DXBUFFER		 pBuffMatEnemy;
	DWORD				nNumMatEnemy;
	D3DXVECTOR3			VtxMinEnemy;		//�ŏ��l�@min[MAX_Enemy_TYPE]
	D3DXVECTOR3			VtxMaxEnemy;		//�ő�l�@max[MAX_Enemy_TYPE]

}EnemyLinfo;

D3DXMATRIX g_mtxWorldEnemy;
Enemy g_Enemy[MAX_Enemy];
EnemyLinfo g_EnemyInfo[NUM_Enemy];
int GetCount;
int DetCount;

//============================================================
//�@�G�l�~�[�̏���������
//============================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEnemy;
	g_nEnemyCounter = 0;

	//�m�[�}���ȃC�J
	D3DXLoadMeshFromX("data//MODEL//ika.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_EnemyInfo[0].pBuffMatEnemy,
		NULL,
		&g_EnemyInfo[0].nNumMatEnemy,
		&g_EnemyInfo[0].MeshEnemy);

	//�S�[���h�̃C�J
	D3DXLoadMeshFromX("data//MODEL//ika2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_EnemyInfo[1].pBuffMatEnemy,
		NULL,
		&g_EnemyInfo[1].nNumMatEnemy,
		&g_EnemyInfo[1].MeshEnemy);

	int nNumVtx;									//���_��
	DWORD sizeFVF;									//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff;									//���_�o�b�t�@�̃|�C���^

	for (nCntEnemy = 0; nCntEnemy < MAX_Enemy; nCntEnemy++)
	{
		g_Enemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu�̏�����
		g_Enemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
		g_Enemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�p�x�̏�����

		g_Enemy[nCntEnemy].bUse = false;
	}

	for (int CntEnemy = 0; CntEnemy < NUM_Enemy; CntEnemy++)
	{
		g_EnemyInfo[nCntEnemy].VtxMinEnemy = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	//�ŏ��l
		g_EnemyInfo[nCntEnemy].VtxMaxEnemy = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//�ő�l
	}

	//���^�C�v�����J��Ԃ�
	for (nCntEnemy = 0; nCntEnemy < NUM_Enemy; nCntEnemy++)
	{
		//���_���̎擾
		nNumVtx = g_EnemyInfo[nCntEnemy].MeshEnemy->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_EnemyInfo[nCntEnemy].MeshEnemy->GetFVF());

		//���_�o�b�t�@�����b�N
		g_EnemyInfo[nCntEnemy].MeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ő�l���擾
			if (Vtx.x >g_EnemyInfo[nCntEnemy].VtxMaxEnemy.x)
			{
				//���O���[�o���ϐ���min,max�ɂ�����
				g_EnemyInfo[nCntEnemy].VtxMaxEnemy.x = Vtx.x;
			}

			if (Vtx.y > g_EnemyInfo[nCntEnemy].VtxMaxEnemy.y)
			{
				g_EnemyInfo[nCntEnemy].VtxMaxEnemy.y = Vtx.y;
			}

			if (Vtx.z > g_EnemyInfo[nCntEnemy].VtxMaxEnemy.z)
			{
				g_EnemyInfo[nCntEnemy].VtxMaxEnemy.z = Vtx.z;
			}

			//���_���W���r���ă��f���̍ŏ��l���擾

			if (Vtx.x <g_EnemyInfo[nCntEnemy].VtxMinEnemy.x)
			{
				g_EnemyInfo[nCntEnemy].VtxMinEnemy.x = Vtx.x;
			}

			if (Vtx.y < g_EnemyInfo[nCntEnemy].VtxMinEnemy.y)
			{
				g_EnemyInfo[nCntEnemy].VtxMinEnemy.y = Vtx.y;
			}

			if (Vtx.z <g_EnemyInfo[nCntEnemy].VtxMinEnemy.z)
			{
				g_EnemyInfo[nCntEnemy].VtxMinEnemy.z = Vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�ccc
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_EnemyInfo[nCntEnemy].MeshEnemy->UnlockVertexBuffer();
	}
}

//============================================================
//�G�l�~�[�̏I������
//============================================================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < NUM_Enemy; nCntEnemy++)
	{ //�e�N�X�`���̔j��
	  //���b�V���̔j��
		if (g_EnemyInfo[nCntEnemy].pBuffMatEnemy != NULL)
		{
			g_EnemyInfo[nCntEnemy].pBuffMatEnemy->Release();
			g_EnemyInfo[nCntEnemy].pBuffMatEnemy = NULL;
		}
	}
}

//============================================================
// �G�l�~�[�̃A�b�v�f�[�g����
//============================================================
void UpdateEnemy(void)
{
	g_nEnemyCounter++; //�G�̊Ԋu

	if (g_nEnemyCounter % 600 == 0)
	{
		SetEnemy(D3DXVECTOR3(-300.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 0.0f, 0.0f), 0); //�m�[�}���C�J
	}

	 if (g_nEnemyCounter % 600 == 0)
	{
		SetEnemy(D3DXVECTOR3(-300.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 0.0f, 0.0f), 0); //�m�[�}���C�J
	}

	 if (g_nEnemyCounter % 750 == 0)
	 {
		 SetEnemy(D3DXVECTOR3(300.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-3.0f, 0.0f, 0.0f), 1); //�m�[�}���C�J
	 }

	 if (g_nEnemyCounter % 750 == 0)
	 {
		 SetEnemy(D3DXVECTOR3(300.0f, 0.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-3.0f, 0.0f, 0.0f), 1); //�m�[�}���C�J
	 }



	for (int nCntEnemy = 0; nCntEnemy < MAX_Enemy; nCntEnemy++)
	{
			//�ړ��l
			g_Enemy[nCntEnemy].pos.x += g_Enemy[nCntEnemy].move.x / 2;
			g_Enemy[nCntEnemy].pos.y += g_Enemy[nCntEnemy].move.y / 2;
			g_Enemy[nCntEnemy].pos.z += g_Enemy[nCntEnemy].move.z / 2;

			if (g_Enemy[nCntEnemy].pos.x<= -700.0f)

			{//��ʊO�ɏo����
				g_Enemy[nCntEnemy].bUse = false;
			}
	}
}

//============================================================
// �G�l�~�[�̕`�揈��
//============================================================
void DrawEnemy(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p
	D3DMATERIAL9 matDef;//�}�e���A���̕ۑ�
	D3DXMATERIAL *pMat;//�}�e���A���̕ۊ�

	//���݂̃}�e���A��
	pDevice->GetMaterial(&matDef);

	for (int nCntEnemy = 0; nCntEnemy < MAX_Enemy; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldEnemy);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEnemy);

			EnemyLinfo* EnemyInfo = &g_EnemyInfo[g_Enemy[nCntEnemy].nType];

			//�}�e���A���f�[�^�ւ̃|�C���g�擾
			pMat = (D3DXMATERIAL*)EnemyInfo->pBuffMatEnemy->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)EnemyInfo->nNumMatEnemy; nCntMat++)
			{
				//�}�e���A���ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//���f���p�[�c�̕`��
				EnemyInfo->MeshEnemy->DrawSubset(nCntMat);
			}
		
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}
	}

	//�ۑ������}�e���A��
	pDevice->SetMaterial(&matDef);
}
//============================================================
// �G�l�~�[�̓����蔻��
//============================================================
bool CollisionEnemy(
	D3DXVECTOR3* pPos,				//���݂̈ʒu
	D3DXVECTOR3* pPosOld,			//�O��̍���
	D3DXVECTOR3* pMove,				//�ړ���
	D3DXVECTOR3* pSize)//�T�C�Y
{
	bool bIsLanding = false;		//���n���Ă��邩�ǂ���
	
	for (int nCntEnemy = 0; nCntEnemy<MAX_Enemy; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)//�g�p���Ă���ꍇ
		{
			/*Player*pPlayer;
			pPlayer = GetPlayer();
*/
			//�E�̓����蔻��
			if (pPos->z - pSize->z <g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].size.z &&
				pPos->z + pSize->z >g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z &&

				pPos->y - pSize->y <g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y &&
				pPos->y + pSize->y >g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y &&

				pPosOld->x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x + pSize->x &&
				pPos->x < g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x + pSize->x)

				//�u���b�N�ɂ߂荞��
			{
				pPos->x = g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x + pSize->x;
				pMove->x = 0.0f;
				
			}

			//���̓����蔻��
			if (pPos->z - pSize->z < g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].size.z &&
				pPos->z + pSize->z > g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z &&

				pPos->y - pSize->y < g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y &&
				pPos->y + pSize->y > g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y &&

				pPosOld->x <= g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x - pSize->x &&
				pPos->x > g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x - pSize->x)

				//�u���b�N�ɂ߂荞��
			{
				pPos->x = g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x - pSize->x;
				pMove->x = 0.0f;
				
			}
			
			//���ʂ̓����蔻��
			if (pPos->x - pSize->x < g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x &&
				pPos->x + pSize->x > g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x &&

				pPos->z - pSize->z < g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].size.z &&
				pPos->z + pSize->z > g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z &&

				pPosOld->y <= g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y - pSize->y &&
				pPos->y > g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y - pSize->y)
				//�u���b�N�ɂ߂荞��
			{
				pPos->y = g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y - pSize->y;
				pMove->y = 0.0f;
				
			}
			//���ʓ����蔻��
			if (pPos->x - pSize->x < g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x &&
				pPos->x + pSize->x > g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x &&

				pPos->y - pSize->y < g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y &&
				pPos->y + pSize->y > g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y &&

				pPosOld->z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].size.z - pSize->z &&
				pPos->z > g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z - pSize->z)

				//�u���b�N�ɂ߂荞��
			{
				pPos->z = g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z - pSize->z;
				pMove->z = 0.0f;
				
			}

			//��ʂ̓����蔻��
			if (pPos->x - pSize->x < g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x &&
				pPos->x + pSize->x > g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x &&

				pPos->z - pSize->z < g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].size.z &&
				pPos->z + pSize->z > g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z &&

				pPosOld->y >= g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y + pSize->y &&
				pPos->y < g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y + pSize->y)
				//�u���b�N�ɂ߂荞��
			{
				bIsLanding = true;
				pPos->y = g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y + pSize->y;
				pMove->y = 0.0f;
				
			}
			
		}
	}

	return bIsLanding;
}
//============================================================
// �G�l�~�[�̐ݒ菈��
//============================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nType)	//type�ǉ�
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_Enemy; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == false)
		{//�u���b�N���g�p����ĂȂ��ꍇ
			g_Enemy[nCntEnemy].pos = pos;
			g_Enemy[nCntEnemy].rot = rot;
			g_Enemy[nCntEnemy].move = move;
			g_Enemy[nCntEnemy].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_Enemy[nCntEnemy].nType = nType;

			g_Enemy[nCntEnemy].size.x = (g_EnemyInfo[nType].VtxMaxEnemy.x - g_EnemyInfo[nType].VtxMinEnemy.x) / 2.0f;
			g_Enemy[nCntEnemy].size.y = (g_EnemyInfo[nType].VtxMaxEnemy.y - g_EnemyInfo[nType].VtxMinEnemy.y);
			g_Enemy[nCntEnemy].size.z = (g_EnemyInfo[nType].VtxMaxEnemy.z - g_EnemyInfo[nType].VtxMinEnemy.z) / 2.0f;

			break;		//(for���𔲂���)
		}
	}
}
