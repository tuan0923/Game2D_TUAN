//===================================================================
//
//3D�A�N�V����(meshfield.cpp)
//Author:�匴���r
//
//===================================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include"main.h"
#include"meshfield.h"
#include"input.h"

//===================================================================
//�O���[�o���ϐ�
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;									//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;								//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;								//�C���f�b�N�X�ւ̃|�C���^
Meshfield g_Meshfield;
int g_nBlockX = 2;																//X�����̃u���b�N��
int g_nBlockZ = 2;																//Z�����̃u���b�N��
int g_nVertex = ((g_nBlockX + 1) * (g_nBlockZ + 1));							//���_��
int g_nIndex = (((g_nBlockX + 1) * 2 * g_nBlockZ) + (g_nBlockZ - 1) * 2);		//�C���f�b�N�X��
int g_nPrim = ((2 * g_nBlockX * g_nBlockZ) + (4 * (g_nBlockZ - 1)));			//�|���S����

//===================================================================
//���b�V���t�B�[���h�̏������ݒ�
//===================================================================
void InitMeshfield(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//block000.jpg",
		&g_pTextureMeshfield);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nVertex,	//�m�ۂ���o�b�t�@�̃T�C�Y 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	VERTEX_3D*pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@���b�N
	WORD *pIdx;
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	//���_�ԍ��̔z�z
	for (int nCntZ = 0; nCntZ < g_nBlockZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < g_nBlockX + 1; nCntX++)
		{
			//���_���W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(-140.0f + 140.0f * nCntX, 0.0f, 140.0f - 140.0f * nCntZ);
			
			//�e���_�̖@���ݒ�i�x�N�g���̑傫����1�ɂ���j
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(100, 50, 200, 255);

			pVtx[0].tex = D3DXVECTOR2(0.0f + 2.0f * nCntX, 0.0f + 2.0f * nCntZ);

			pVtx++;
		}
	}

	//�C���f�b�N�X�ԍ��̔z�z
	for (int nCntZ = 0; nCntZ < g_nBlockZ ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < g_nBlockX + 1; nCntX++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[0] = (nCntZ * (g_nBlockX + 1) + nCntX) + (g_nBlockX + 1);	//���i�̒��_
			pIdx[1] = (nCntZ * (g_nBlockX + 1) + nCntX);					//��i�̒��_
			pIdx += 2;
		}

		if (nCntZ < g_nBlockZ - 1)
		{//�k�ރ|���S���̍쐬
			pIdx[0] = pIdx[-1];		//�ЂƂO��pIdx�̒l������
			pIdx[1] = (g_nBlockX + 1)*(nCntZ + 2);
			pIdx += 2;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshfield->Unlock();

	//�C���f�b�N�X�o�b�t�@�A�����b�N
	g_pIdxBuffMeshfield->Unlock();
}

//===================================================================
//���b�V���t�B�[���h�̏I������
//===================================================================
void UninitMeshfield(void)
{
	//�o�b�t�@�j��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��U
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}
}

//===================================================================
//���b�V���t�B�[���h�̍X�V����
//===================================================================
void UpdateMeshfield(void)
{
	
}

//===================================================================
//���b�V���t�B�[���h�̕`�揈��
//===================================================================
void DrawMeshfield(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Meshfield.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Meshfield.rot.y, g_Meshfield.rot.x, g_Meshfield.rot.z);
	D3DXMatrixMultiply(&g_Meshfield.mtxWorld, &g_Meshfield.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Meshfield.pos.x, g_Meshfield.pos.y, g_Meshfield.pos.z);
	D3DXMatrixMultiply(&g_Meshfield.mtxWorld, &g_Meshfield.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Meshfield.mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshfield);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���b�V���t�B�[���h�`��
	pDevice->DrawIndexedPrimitive
	(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
	0,							//�`�悷��ŏ��̃C���f�b�N�X
	0,							//�o�b�t�@�̍ŏ��l
	g_nVertex,					//���_��
	0,							//�C���f�b�N�X�̍ŏ��̐�
	g_nPrim);					//�v���~�e�B�u�i�|���S���j��

	//�e�N�X�`�������Ƃɖ߂�
	pDevice->SetTexture(0, NULL);
}