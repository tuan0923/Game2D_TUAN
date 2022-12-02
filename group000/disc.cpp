//----------------------------------------
//�@�f�B�X�N�̏���
//�@Author�F���슲��
//----------------------------------------
#include "Disc.h"
#include "vec.h"
#include "goal.h"
#include "mob.h"
#include "player.h"

//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshDisc = NULL;			//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatDisc = NULL;		//�}�e���A�����ւ̃|�C���^
DWORD g_nNumMatDisc = 0;				//�}�e���A�����̐�
D3DXMATERIAL * g_pMatDisc;				//�}�e���A���f�[�^�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureDisc[10];	//�e�N�X�`���ւ̃|�C���^
Disc g_aDisc;				//�f�B�X�N�̕ϐ�
DISC_SHOT g_DiscType;		//�������f�B�X�N�̎�ނ�ݒ�p
float g_fData;				//�J�[�u�O�����Ɏg�p�B
bool g_bShotUp = false;		//��񂾂��N������悤

//---------------------------------------------------
//	�f�B�X�N�̏�����
//---------------------------------------------------
void InitDisc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�擾

	//�f�B�X�N�̊e�l������
	{
		g_aDisc.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���݂̈ʒu
		g_aDisc.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O��̈ʒu
		g_aDisc.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�p�x
		g_aDisc.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
		g_aDisc.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�J���[
		g_aDisc.bUse = false;				//�g���Ă��邩�ǂ���
		g_aDisc.speed = 0.0f;				//�ړ��X�s�[�h
		g_aDisc.status = STATUS_WAITING;	//���݂̏��
		g_aDisc.vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);			//���_�̍ŏ��l�擾�p
		g_aDisc.vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);		//���_�̍ő�l�擾�p
		g_aDisc.vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);		//���_�̍ő�l�擾�p
		g_aDisc.type = 0;
	}
	g_fData = 0.0f;		//�O�����J�[�u�̎��Ɏg�p
	g_bShotUp = false;	//�d�͂����邩�ǂ���

						//�]�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\disc.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatDisc,
		NULL,
		&g_nNumMatDisc,
		&g_pMeshDisc);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	g_pMatDisc = (D3DXMATERIAL*)g_pBuffMatDisc->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatDisc; nCntMat++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			g_pMatDisc[nCntMat].pTextureFilename,
			&g_pTextureDisc[nCntMat]);
	}

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE * pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

						//���_���̎擾
	nNumVtx = g_pMeshDisc->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshDisc->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshDisc->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);


	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// �ŏ��l�����߂�
		if (vtx.x < g_aDisc.vtxMin.x)
		{// ��r�����l�������Ă铖�������������������A�u������
			g_aDisc.vtxMin.x = vtx.x;
		}
		if (vtx.y < g_aDisc.vtxMin.y)
		{// ��r�����l�������Ă铖�������������������A�u������
			g_aDisc.vtxMin.y = vtx.y;
		}
		if (vtx.z < g_aDisc.vtxMin.z)
		{// ��r�����l�������Ă铖�������������������A�u������
			g_aDisc.vtxMin.z = vtx.z;
		}

		// �ő�l�����߂�
		if (vtx.x > g_aDisc.vtxMax.x)
		{// ��r�����l�������Ă铖��������傫��������A�u������
			g_aDisc.vtxMax.x = vtx.x;
		}
		if (vtx.y > g_aDisc.vtxMax.y)
		{// ��r�����l�������Ă铖��������傫��������A�u������
			g_aDisc.vtxMax.y = vtx.y;
		}
		if (vtx.z > g_aDisc.vtxMax.z)
		{// ��r�����l�������Ă铖��������傫��������A�u������
			g_aDisc.vtxMax.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃|�C���^���i�߂�
		pVtxBuff += sizeFVF;
	}

	//���_�o�b�t�@���A�����b�N
	g_pMeshDisc->UnlockVertexBuffer();

	//�f�B�X�N�̃T�C�Y�v�Z
	g_aDisc.size.x = g_aDisc.vtxMax.x - g_aDisc.vtxMin.x;
	g_aDisc.size.y = g_aDisc.vtxMax.y - g_aDisc.vtxMin.y;
	g_aDisc.size.z = g_aDisc.vtxMax.z - g_aDisc.vtxMin.z;
}

//---------------------------------------------------
//	�f�B�X�N�̏I������
//---------------------------------------------------
void UninitDisc(void)
{
	//���b�V���j��
	if (g_pMeshDisc != NULL)
	{
		g_pMeshDisc->Release();
		g_pMeshDisc = NULL;
	}

	//�}�e���A���j��
	if (g_pBuffMatDisc != NULL)
	{
		g_pBuffMatDisc->Release();
		g_pBuffMatDisc = NULL;
	}

	//�e�N�X�`���j��
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatDisc; nCntMat++)
	{
		if (g_pTextureDisc[nCntMat] != NULL)
		{
			g_pTextureDisc[nCntMat]->Release();
			g_pTextureDisc[nCntMat] = NULL;
		}
	}
}

//---------------------------------------------------
//	�f�B�X�N�̍X�V����
//---------------------------------------------------
void UpdateDisc(void)
{
	if (g_aDisc.bUse == true)
	{
		//���݂̈ʒu��ۑ�
		g_aDisc.posOld = g_aDisc.pos;

		if (g_aDisc.status == STATUS_WAITING)
		{
			//���̂Ƃ��뉽�����Ȃ�
		}

		float fSinData;

		if (g_aDisc.status == STATUS_MOVING)
		{
			switch (g_DiscType)
			{
			case SHOT_NOMAL:		//�ʏ�̃f�B�X�N�O���i�^�������j
				fSinData = 0.0f;
				break;

			case SHOT_CURVE:		//�J�[�u
				g_fData += 0.03f;
				fSinData = sinf((D3DX_PI / 2.0f) + g_fData);
				break;

			case SHOT_UP:			//������ɓ�����
				fSinData = 0.0f;

				if (g_bShotUp == false)
				{//��񂾂��g�p
					g_aDisc.move.y = 1.5f;	//�������
					g_bShotUp = true;
				}
				break;

			default:
				break;
			}

			if (g_DiscType == SHOT_UP)
			{//������֓�������
				//�d��
				g_aDisc.move.y -= 0.05f;
			}

			//�f�B�X�N�̈ړ��ʍX�V
			g_aDisc.move.x = sinf(g_aDisc.rot.y + fSinData) * g_aDisc.speed;
			g_aDisc.move.z = cosf(g_aDisc.rot.y + fSinData) * g_aDisc.speed;

			//�f�B�X�N�̈ʒu�X�V
			g_aDisc.pos.z -= g_aDisc.move.z;
			g_aDisc.pos.x -= g_aDisc.move.x;
			g_aDisc.pos.y += g_aDisc.move.y;

			//���˂Ɋւ��铖���蔻��
			CollisionVec(g_aDisc.pos, g_aDisc.posOld, &g_aDisc.bUse, &g_aDisc.speed, &g_aDisc.rot);

			//�S�[���Ƃ̓����蔻��
			CollisionGoal(g_aDisc.pos, &g_aDisc.bUse, g_aDisc.type);

		}
	}
}

//---------------------------------------------------
//	�f�B�X�N�̕`�揈��
//---------------------------------------------------
void DrawDisc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL * pMat;			//�}�e���A���f�[�^�ւ̃|�C���^

	if (g_aDisc.bUse == true)
	{//�f�B�X�N���g�p����Ă��鎞
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aDisc.mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aDisc.rot.y, g_aDisc.rot.x, g_aDisc.rot.z);
		D3DXMatrixMultiply(&g_aDisc.mtxWorld,
			&g_aDisc.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aDisc.pos.x, g_aDisc.pos.y, g_aDisc.pos.z);
		D3DXMatrixMultiply(&g_aDisc.mtxWorld, &g_aDisc.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aDisc.mtxWorld);

		//���݂̃}�e���A���ێ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatDisc->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatDisc; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureDisc[nCntMat]);

			//���f���p�[�c�̕`��
			g_pMeshDisc->DrawSubset(nCntMat);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureDisc[nCntMat]);
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//---------------------------------------------------
//	�f�B�X�N�̈ʒu�ݒ�i����̓v���C���[�̏����ݒ�ŌĂяo���j
//
//	type �� �v���C���[1�Ȃ�0�A�v���C���[2�Ȃ�1
//---------------------------------------------------
void SetPosDisc(D3DXVECTOR3 pos, int type)
{//�f�B�X�N�̏����ʒu�ݒ�
	if (g_aDisc.bUse == false)
	{//�f�B�X�N���g�p����Ă��Ȃ���
		g_aDisc.pos = D3DXVECTOR3(pos.x, pos.y, pos.z);	//�ʒu�ݒ�
		g_aDisc.bUse = true;				//�g���Ă����Ԃɂ���
		g_aDisc.status = STATUS_WAITING;	//��Ԃ�ݒ�
		g_bShotUp = false;
		g_aDisc.type = type;
	}
}

//---------------------------------------------------
//	�������f�B�X�N�̐ݒ�(����̓f�B�X�N�𓊂���Ƃ��ɌĂԊ֐�)SetBullet�Ɠ����v�́Bmodel.cpp���Q�l�ɁB
//
//	type �� �v���C���[1�Ȃ�0�A�v���C���[2�Ȃ�1
//---------------------------------------------------
void SetMoveDisc(D3DXVECTOR3 rot, float speed, DISC_SHOT shot, int type)
{
	if (g_aDisc.bUse == true)
	{
		if (g_aDisc.status == STATUS_WAITING)
		{
			if (g_aDisc.type == type)
			{
				g_aDisc.rot = rot;		//�p�x�ݒ�
				g_aDisc.speed = speed;	//�X�s�[�h�ݒ�
				g_aDisc.status = STATUS_MOVING;	//��Ԃ�ݒ�
				g_DiscType = shot;		//��ނ�ݒ�
			}
		}
	}
}

//---------------------------------------------------
//	�f�B�X�N�ƃv���C���[�̓����蔻��i����̓L���b�`�̔���j
//
//	type �� �v���C���[1�Ȃ�0�A�v���C���[2�Ȃ�1
//---------------------------------------------------
void CollisionDisc_Player(D3DXVECTOR3 *pos, D3DXVECTOR3 size, int type)
{//�f�B�X�N���v���C���[�ɓ���������
	Player *pPlayer = GetPlayer();
	MOB *pMob = GetMob();

	if (g_aDisc.bUse == true)
	{// bUse��true��������i�f�B�X�N���g�p����Ă����Ԃ̎�
		if (g_aDisc.status == STATUS_MOVING)
		{
			if (pos->y < g_aDisc.pos.y + (g_aDisc.size.y / 2.0f) &&
				pos->y + (size.y) > g_aDisc.pos.y - (g_aDisc.size.y / 2.0f))
			{
				if (pos->z - (size.z / 2) < g_aDisc.pos.z + (g_aDisc.size.z / 2.0f) &&
					pos->z + (size.z / 2) > g_aDisc.pos.z - (g_aDisc.size.z / 2.0f))
				{// *pos��z���W�����f���ɏd�Ȃ��Ă��鎞
					if (pos->x - (size.x / 2) <= g_aDisc.pos.x + (g_aDisc.size.x / 2.0f) &&
						pos->x + (size.x / 2) >= g_aDisc.pos.x - (g_aDisc.size.x / 2.0f))
					{//�������烂�f���ɂ߂荞�񂾎�
						g_aDisc.bUse = false;

						switch(type)
						{
						case 0:
							//�v���C���[1�Ƀf�B�X�N�Z�b�g
							SetPosDisc(D3DXVECTOR3(pPlayer->pos.x + 10.0f, pPlayer->pos.y + 20.0f, pPlayer->pos.z), 0);
							break;

						case 1:
							//�v���C���[2�Ƀf�B�X�N�Z�b�g
							SetPosDisc(D3DXVECTOR3(pMob->pos.x + 10.0f, pMob->pos.y + 20.0f, pMob->pos.z), 1);
							break;

						default:
							break;
						}
					}
				}
				else if (pos->x - (size.x / 2) < g_aDisc.pos.x - (g_aDisc.size.x / 2.0f) &&
					pos->x + (size.x / 2) > g_aDisc.pos.x + (g_aDisc.size.x / 2.0f))
				{// *pos��x���W�����f���ɏd�Ȃ��Ă��鎞
					if (pos->z - (size.z / 2) < g_aDisc.pos.z + (g_aDisc.size.z / 2.0f) &&
						pos->z + (size.z / 2) > g_aDisc.pos.z - (g_aDisc.size.z / 2.0f))
					{//���f���̎�O������߂荞�񂾎�
						//false�ɂ���
						g_aDisc.bUse = false;

						switch (type)
						{
						case 0:
							//�v���C���[1�Ƀf�B�X�N�Z�b�g
							SetPosDisc(D3DXVECTOR3(pPlayer->pos.x + 10.0f, pPlayer->pos.y + 20.0f, pPlayer->pos.z), 0);
							break;

						case 1:
							//�v���C���[2�Ƀf�B�X�N�Z�b�g
							SetPosDisc(D3DXVECTOR3(pMob->pos.x + 10.0f, pMob->pos.y + 20.0f, pMob->pos.z), 1);
							break;

						default:
							break;
						}
					}
				}
			}
		}
	}
}

//---------------------------------------------------
//	�f�B�X�N�̈ʒu�̍X�V�����i�v���C���[���f�B�X�N�����Ă�悤�ɂȂ�j�v���C���[�̍X�V�����ɓ����B�e�Ɠ���
//---------------------------------------------------
void SetPositionDisc(D3DXVECTOR3 pos, int type)
{
	if (g_aDisc.status != STATUS_MOVING)
	{
		if (g_aDisc.type == type)
		{
			g_aDisc.pos = pos;	//�ʒu�X�V
		}
	}
}