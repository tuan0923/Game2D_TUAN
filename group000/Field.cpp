//===============================================
//
// Field.cpp
// Author: �e���A��
//
//===============================================
#include "Field.h"
#include "game.h"
#include "input.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

////�}�N����`
#define SPEED (1.50f)
#define Field_MAX (128)
#define SIZE_Field_X (2.0f)
#define SIZE_Field_Y (2.0f)
#define SIZE_Field_Z (2.0f)

#define SIZE_Y (2.0f)
#define SIZE_Z (2.0f)
#define NUM_Field (9)

//�O���[�o���ϐ�  
typedef struct
{
	
	LPD3DXMESH pMeshField;     //���b�V:���_�̏W�܂�̂���
	LPD3DXBUFFER pBuffMatField;//�}�e���A�����ւ̃|�C���^
	DWORD nNumMatField;           //�}�e���A�����̐�
	D3DXVECTOR3 vtxMinField;
	D3DXVECTOR3 vtxMaxField;

}Field_IF;
Field_IF g_aFieldIF[NUM_Field];
Field g_aField[Field_MAX];
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;	//�e�N�X�`��

//=======================================
//����������
//=======================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntField = 0; nCntField < Field_MAX; nCntField++)
	{
		g_aField[nCntField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCntField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCntField].rotDestField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCntField].scaleVectorField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCntField].bUse = false;
		g_aField[nCntField].type = Field_TYPE_WALL_RED;
	}
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//yuka1.jpg",
		&g_pTextureField);
	
	//Xfile �ǂݍ���
	D3DXLoadMeshFromX("data//MODEL//wall_red.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aFieldIF[0].pBuffMatField,
		NULL,
		&g_aFieldIF[0].nNumMatField,
		&g_aFieldIF[0].pMeshField);

	D3DXLoadMeshFromX("data//MODEL//wall_blue.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aFieldIF[1].pBuffMatField,
		NULL,
		&g_aFieldIF[1].nNumMatField,
		&g_aFieldIF[1].pMeshField);

	D3DXLoadMeshFromX("data//MODEL//yuka_red.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aFieldIF[2].pBuffMatField,
		NULL,
		&g_aFieldIF[2].nNumMatField,
		&g_aFieldIF[2].pMeshField);
	D3DXLoadMeshFromX("data//MODEL//yuka_blue.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aFieldIF[3].pBuffMatField,
		NULL,
		&g_aFieldIF[3].nNumMatField,
		&g_aFieldIF[3].pMeshField);

	D3DXLoadMeshFromX("data//MODEL//wall_naka.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aFieldIF[4].pBuffMatField,
		NULL,
		&g_aFieldIF[4].nNumMatField,
		&g_aFieldIF[4].pMeshField);

	D3DXLoadMeshFromX("data//MODEL//kansha.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aFieldIF[5].pBuffMatField,
		NULL,
		&g_aFieldIF[5].nNumMatField,
		&g_aFieldIF[5].pMeshField);
	D3DXLoadMeshFromX("data//MODEL//minirobot.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aFieldIF[6].pBuffMatField,
		NULL,
		&g_aFieldIF[6].nNumMatField,
		&g_aFieldIF[6].pMeshField);
	D3DXLoadMeshFromX("data//MODEL//robotX.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aFieldIF[7].pBuffMatField,
		NULL,
		&g_aFieldIF[7].nNumMatField,
		&g_aFieldIF[7].pMeshField);
	D3DXLoadMeshFromX("data//MODEL//testgame.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aFieldIF[8].pBuffMatField,
		NULL,
		&g_aFieldIF[8].nNumMatField,
		&g_aFieldIF[8].pMeshField);

	int nNumVtx;     //���_��
	DWORD sizeFVF;   //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff;   //���_�o�b�t�@�ւ̃|�C���^
					 //���_���̎擾
	for (int nCntField = 0; nCntField < NUM_Field; nCntField++)
	{
		g_aFieldIF[nCntField].vtxMaxField = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_aFieldIF[nCntField].vtxMinField = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);

		nNumVtx = g_aFieldIF[nCntField].pMeshField->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aFieldIF[nCntField].pMeshField->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aFieldIF[nCntField].pMeshField->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			// �ŏ��l�v�Z
			if (vtx.x < g_aFieldIF[nCntField].vtxMinField.x)
			{// ��r�����l�������Ă铖�������������������u��������
				g_aFieldIF[nCntField].vtxMinField.x = floorf(vtx.x);
			}

			if (vtx.z < g_aFieldIF[nCntField].vtxMinField.z)
			{// ��r�����l�������Ă铖�������������������u��������
				g_aFieldIF[nCntField].vtxMinField.z = floorf(vtx.z);
			}

			// �ő�l���v�Z
			if (vtx.x > g_aFieldIF[nCntField].vtxMaxField.x)
			{// ��r�����l�������Ă铖��������傫��������u��������
				g_aFieldIF[nCntField].vtxMaxField.x = floorf(vtx.x);
			}

			if (vtx.z > g_aFieldIF[nCntField].vtxMaxField.z)
			{// ��r�����l�������Ă铖��������傫��������u��������
				g_aFieldIF[nCntField].vtxMaxField.z = floorf(vtx.z);
			}
			//���_�t�H�[�}�b�g�̃|�C���^���i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@���A�����b�N
		g_aFieldIF[nCntField].pMeshField->UnlockVertexBuffer();
	}
	//wall_red	

	SetField(D3DXVECTOR3(-350.0f, 0.0f, -320.0f), D3DXVECTOR3(0.0f, D3DX_PI * 2, 0.0f), D3DXVECTOR3(SIZE_Field_X* 3, SIZE_Field_Y*3, SIZE_Field_Z * 4), Field_TYPE_WALL_RED);
	SetField(D3DXVECTOR3(335.0f, 0.0f, -320.0f), D3DXVECTOR3(0.0f, D3DX_PI*2, 0.0f), D3DXVECTOR3(SIZE_Field_X* 3, SIZE_Field_Y*3, SIZE_Field_Z * 4), Field_TYPE_WALL_RED);
	//
	////wall_blue
	SetField(D3DXVECTOR3(-350.0f, 0.0f,300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 2, 0.0f), D3DXVECTOR3(SIZE_Field_X * 3, SIZE_Field_Y * 3, SIZE_Field_Z * 4), Field_TYPE_WALL_BLUE);
	SetField(D3DXVECTOR3(340.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI*2, 0.0f), D3DXVECTOR3(SIZE_Field_X * 3, SIZE_Field_Y * 3, SIZE_Field_Z * 4), Field_TYPE_WALL_BLUE);

	//yuka_red
	SetField(D3DXVECTOR3(-10.0f, -1.0f, 310.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X*3.5, SIZE_Field_Y, SIZE_Field_Z*4 ), Field_TYPE_YUKA_RED);
	
	//yuka_Blue
	SetField(D3DXVECTOR3(0.0f, -1.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X*3.5, SIZE_Field_Y, SIZE_Field_Z*4), Field_TYPE_YUKA_BLUE);
	
	//wall_naka
	SetField(D3DXVECTOR3(0.0f, -1.0f, 5.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X*3.5, SIZE_Field_Y *4, SIZE_Field_Z *3.5), Field_TYPE_WALL_NAKA);
	//
	SetField(D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X*3.5, SIZE_Field_X * 4, SIZE_Field_Z *3.5), Field_TYPE_KANSHA);
	//�E
	SetField(D3DXVECTOR3(-420.0f, 50.0f, 650.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(-420.0f, 50.0f, 740.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(-420.0f, 50.0f, 850.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(-420.0f, 50.0f, -460.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINION);

	SetField(D3DXVECTOR3(-420.0f, 50.0f, 300.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(-490.0f, 100.0f, 380.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(-420.0f, 50.0f, 460.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(-420.0f, 50.0f, 560.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINION);

	SetField(D3DXVECTOR3(-420.0f, 50.0f, 200.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(-490.0f, 100.0f, 150.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(-420.0f, 50.0f, 70.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(-420.0f, 50.0f, -30.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(-490.0f, 100.0f, -100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(-420.0f, 50.0f, -170.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(-420.0f, 50.0f, -230.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(-420.0f, 50.0f, -570.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(-420.0f, 50.0f, -730.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINION);

	//��
	SetField(D3DXVECTOR3(420.0f, 50.0f, 650.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(420.0f, 50.0f, 740.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(420.0f, 50.0f, 850.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(420.0f, 50.0f, -460.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINION);

	SetField(D3DXVECTOR3(420.0f, 50.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(490.0f, 100.0f, 380.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(420.0f, 50.0f, 460.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(420.0f, 50.0f, 560.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINION);

	SetField(D3DXVECTOR3(420.0f, 50.0f, 200.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(490.0f, 100.0f, 150.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(420.0f, 50.0f, 70.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(420.0f, 50.0f, -30.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(490.0f, 100.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(420.0f, 50.0f, -170.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(420.0f, 50.0f, -230.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(420.0f, 50.0f, -570.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(420.0f, 50.0f, -730.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINION);

	//��
	SetField(D3DXVECTOR3(0.0f, 50.0f, 790.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(80.0f, 50.0f, 790.0f), D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(170.0f, 50.0f, 790.0f), D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(-170.0f, 50.0f, 790.0f), D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(-250.0f, 50.0f, 790.0f), D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(-320.0f, 50.0f, 790.0f), D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(230.0f, 50.0f, 790.0f), D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(120.0f, 50.0f, 790.0f), D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(-70.0f, 50.0f, 790.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);

	SetField(D3DXVECTOR3(20.0f, 100.0f, 850.0f), D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(130.0f, 100.0f, 850.0f), D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(-120.0f, 100.0f, 850.0f), D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(270.0f, 100.0f, 850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(360.0f, 100.0f, 850.0f), D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	//�����
	SetField(D3DXVECTOR3(0.0f, 50.0f, -760.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(80.0f, 50.0f, -760.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.4, SIZE_Field_X / 1.4, SIZE_Field_Z / 1.4), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(170.0f, 50.0f, -760.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(-170.0f, 50.0f, -760.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(-250.0f, 50.0f, -760.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(-320.0f, 50.0f, -760.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(230.0f, 50.0f, -760.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(120.0f, 50.0f, -760.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(-70.0f, 50.0f, -760.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINIROBOT);

	SetField(D3DXVECTOR3(20.0f, 100.0f, -810.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINIROBOT);
	SetField(D3DXVECTOR3(130.0f, 100.0f, -810.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(-120.0f, 100.0f, -810.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_ROBOT);
	SetField(D3DXVECTOR3(270.0f, 100.0f, -810.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINION);
	SetField(D3DXVECTOR3(360.0f, 100.0f, -810.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), D3DXVECTOR3(SIZE_Field_X / 1.8, SIZE_Field_X / 2.2, SIZE_Field_Z / 1.8), Field_TYPE_MINIROBOT);


}
//=======================================
//�I������
//======================================= 
void UninitField(void)
{
	for (int nCntField = 0; nCntField < NUM_Field; nCntField++)
	{
		//���b�V���j��
		if (g_aFieldIF[nCntField].pMeshField != NULL)
		{
			g_aFieldIF[nCntField].pMeshField->Release();
			g_aFieldIF[nCntField].pMeshField = NULL;
		}
		//�}�e���A���̔j��
		if (g_aFieldIF[nCntField].pBuffMatField != NULL)
		{
			g_aFieldIF[nCntField].pBuffMatField->Release();
			g_aFieldIF[nCntField].pBuffMatField = NULL;
		}

	}
	//�e�N�X�`���j��
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}


}

//=======================================
//�X�V����
//=======================================    
void UpdateField(void)
{

	

}
//=======================================
//�`��̏���
//=======================================       
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, scale;     //�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;                    //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;                     //�}�e���A���f�[�^�ւ̃|�C���^
	for (int nCnt = 0; nCnt < Field_MAX; nCnt++)
	{
		if (g_aField[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aField[nCnt].mtxWorld);

			//���f���̃T�C�Y
			D3DXMatrixScaling(&scale,
				g_aField[nCnt].scaleVectorField.x,
				g_aField[nCnt].scaleVectorField.y,
				g_aField[nCnt].scaleVectorField.z);
			D3DXMatrixMultiply(&g_aField[nCnt].mtxWorld, &g_aField[nCnt].mtxWorld, &scale);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aField[nCnt].rot.y, g_aField[nCnt].rot.x, g_aField[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aField[nCnt].mtxWorld, &g_aField[nCnt].mtxWorld, &mtxRot);

			////�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aField[nCnt].pos.x, g_aField[nCnt].pos.y, g_aField[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aField[nCnt].mtxWorld, &g_aField[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aField[nCnt].mtxWorld);

			//���݂̃}�e���A����ۓ�
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aFieldIF[g_aField[nCnt].type].pBuffMatField->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aFieldIF[g_aField[nCnt].type].nNumMatField; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//���f���p�[�c�̕`��
				g_aFieldIF[g_aField[nCnt].type].pMeshField->DrawSubset(nCntMat);
				
				if (g_aField[nCnt].type == Field_TYPE_YUKA_RED || g_aField[nCnt].type == Field_TYPE_YUKA_BLUE)
				{
					//�e�N�X�`���ݒ�
					pDevice->SetTexture(0, g_pTextureField);
				}
				else
				{
					pDevice->SetTexture(0,NULL);
				}
			}
			
			// �ۓ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}
void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scaleVectorField, Field_TYPE type)
{

	for (int nCntField = 0; nCntField < Field_MAX; nCntField++)
	{
		//bUse ��false�̏ꍇ, pos,rot������bUse��true�ɂ���
		if (g_aField[nCntField].bUse == false)
		{
			g_aField[nCntField].pos = pos;
			g_aField[nCntField].rot = rot;
			g_aField[nCntField].bUse = true;
			g_aField[nCntField].scaleVectorField = scaleVectorField;
			g_aField[nCntField].type = type;
			break;
		}
	}
}

//-------------------------------------------
//���f���̓����蔻��
//-------------------------------------------
bool CollisionField(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size)
{
	bool iMasat = false;
	for (int nCntField = 0; nCntField < Field_MAX; nCntField++)
	{
		if (g_aField[nCntField].bUse == true && g_aField[nCntField].type != Field_TYPE_YUKA_RED && g_aField[nCntField].type != Field_TYPE_YUKA_BLUE)
		{
			if (pos->z - (size.z / 2) < g_aField[nCntField].pos.z + g_aFieldIF[g_aField[nCntField].type].vtxMaxField.z*g_aField[nCntField].scaleVectorField.z &&
				pos->z + (size.z / 2) > g_aField[nCntField].pos.z + g_aFieldIF[g_aField[nCntField].type].vtxMinField.z*g_aField[nCntField].scaleVectorField.z)
			{ //������(x)
				if (posOld->x + (size.x / 2.f) <= g_aField[nCntField].pos.x + g_aFieldIF[g_aField[nCntField].type].vtxMinField.x*g_aField[nCntField].scaleVectorField.x &&
					pos->x + (size.x / 2.f) > g_aField[nCntField].pos.x + g_aFieldIF[g_aField[nCntField].type].vtxMinField.x*g_aField[nCntField].scaleVectorField.x)
				{
					iMasat = true;
					pos->x = g_aField[nCntField].pos.x + g_aFieldIF[g_aField[nCntField].type].vtxMinField.x*g_aField[nCntField].scaleVectorField.x - (size.x / 2);
				}
				//�E����(x)
				else if (posOld->x - (size.x / 2) >= g_aField[nCntField].pos.x + g_aFieldIF[g_aField[nCntField].type].vtxMaxField.x*g_aField[nCntField].scaleVectorField.x &&
					pos->x - (size.x / 2) < g_aField[nCntField].pos.x + g_aFieldIF[g_aField[nCntField].type].vtxMaxField.x*g_aField[nCntField].scaleVectorField.x)
				{
					iMasat = true;
					pos->x = g_aField[nCntField].pos.x + g_aFieldIF[g_aField[nCntField].type].vtxMaxField.x*g_aField[nCntField].scaleVectorField.x + (size.x / 2);
				}
			}
			if (pos->x - (size.x / 2) < g_aField[nCntField].pos.x + g_aFieldIF[g_aField[nCntField].type].vtxMaxField.x*g_aField[nCntField].scaleVectorField.x &&
				pos->x + (size.x / 2) > g_aField[nCntField].pos.x + g_aFieldIF[g_aField[nCntField].type].vtxMinField.x*g_aField[nCntField].scaleVectorField.x)
			{ // ��(z)

				if (posOld->z + (size.z / 2) <= g_aField[nCntField].pos.z + g_aFieldIF[g_aField[nCntField].type].vtxMinField.z*g_aField[nCntField].scaleVectorField.z &&
					pos->z + (size.z / 2) >  g_aField[nCntField].pos.z + g_aFieldIF[g_aField[nCntField].type].vtxMinField.z*g_aField[nCntField].scaleVectorField.z)
				{
					iMasat = true;
					pos->z = g_aField[nCntField].pos.z + g_aFieldIF[g_aField[nCntField].type].vtxMinField.z*g_aField[nCntField].scaleVectorField.z - (size.z / 2);

				}

				// ��(z)
				else if (posOld->z - (size.z / 2) >= g_aField[nCntField].pos.z + g_aFieldIF[g_aField[nCntField].type].vtxMaxField.z*g_aField[nCntField].scaleVectorField.z &&
					pos->z - (size.z / 2) <  g_aField[nCntField].pos.z + g_aFieldIF[g_aField[nCntField].type].vtxMaxField.z*g_aField[nCntField].scaleVectorField.z)
				{
					iMasat = true;
					pos->z = g_aField[nCntField].pos.z + g_aFieldIF[g_aField[nCntField].type].vtxMaxField.z*g_aField[nCntField].scaleVectorField.z + (size.z / 2);

				}
			}
		}
	}
	return iMasat;
}

Field*GetField(void)
{
	return g_aField;
}