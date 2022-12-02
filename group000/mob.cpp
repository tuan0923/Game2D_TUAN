//===================================================================
//
//3D�A�N�V����(mob.cpp)
//Author:�匴���r
//
//===================================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include <stdio.h>
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "meshfield.h"
#include "shadow.h"
#include "wall.h"
#include "mob.h"
#include "controller.h"
#include"score.h"
#include"disc.h"
#include "Field.h"
#include "enemy.h"
#include"controller.h"

//===================================================================
//�O���[�o���ϐ�
//===================================================================
MOB g_Mob;								//�v���C���[�\����
MobKey g_aMobKey;						//�L�[�\����
MobKeySet g_aMobKeySet;					//�L�[�Z�b�g�\����
MobMotionSet g_MobMotionSet;			//���[�V�����\����

//===================================================================
//�v���C���[�̏������ݒ�
//===================================================================
void InitMob(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ZeroMemory(&g_Mob, sizeof(g_Mob)); //�\���̕ϐ����N���A�ł���֗��֐�

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

						//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data//MODEL//player_body.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[0].pBuffMat,
		NULL,
		&g_Mob.aModel[0].nNumMat,
		&g_Mob.aModel[0].pMesh);

	D3DXLoadMeshFromX("data//MODEL//mob_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[1].pBuffMat,
		NULL,
		&g_Mob.aModel[1].nNumMat,
		&g_Mob.aModel[1].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_armR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[2].pBuffMat,
		NULL,
		&g_Mob.aModel[2].nNumMat,
		&g_Mob.aModel[2].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_handR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[3].pBuffMat,
		NULL,
		&g_Mob.aModel[3].nNumMat,
		&g_Mob.aModel[3].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_armL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[4].pBuffMat,
		NULL,
		&g_Mob.aModel[4].nNumMat,
		&g_Mob.aModel[4].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_handL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[5].pBuffMat,
		NULL,
		&g_Mob.aModel[5].nNumMat,
		&g_Mob.aModel[5].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_legR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[6].pBuffMat,
		NULL,
		&g_Mob.aModel[6].nNumMat,
		&g_Mob.aModel[6].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_footR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[7].pBuffMat,
		NULL,
		&g_Mob.aModel[7].nNumMat,
		&g_Mob.aModel[7].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_legL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[8].pBuffMat,
		NULL,
		&g_Mob.aModel[8].nNumMat,
		&g_Mob.aModel[8].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_footL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[9].pBuffMat,
		NULL,
		&g_Mob.aModel[9].nNumMat,
		&g_Mob.aModel[9].pMesh);

	//��
	g_Mob.aModel[0].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);		//�ʒu�̏����ݒ�
	g_Mob.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Mob.aModel[0].nIdx = 0;								//�C���f�b�N�X�ԍ�
	g_Mob.aModel[0].nIdxModelParent = -1;					//�e�̃C���f�b�N�X
															//��
	g_Mob.aModel[1].pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Mob.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Mob.aModel[1].nIdx = 1;								//�C���f�b�N�X�ԍ�
	g_Mob.aModel[1].nIdxModelParent = 0;						//�e�̃C���f�b�N�X
																//�E�r
	g_Mob.aModel[2].pos = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Mob.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Mob.aModel[2].nIdx = 2;								//�C���f�b�N�X�ԍ�
	g_Mob.aModel[2].nIdxModelParent = 0;						//�e�̃C���f�b�N�X
																//�E��
	g_Mob.aModel[3].pos = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);		//�ʒu�̏����ݒ�
	g_Mob.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Mob.aModel[3].nIdx = 3;								//�C���f�b�N�X�ԍ�
	g_Mob.aModel[3].nIdxModelParent = 2;						//�e�̃C���f�b�N�X
																//���r
	g_Mob.aModel[4].pos = D3DXVECTOR3(15.0f, 30.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Mob.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Mob.aModel[4].nIdx = 4;								//�C���f�b�N�X�ԍ�
	g_Mob.aModel[4].nIdxModelParent = 0;						//�e�̃C���f�b�N�X
																//����
	g_Mob.aModel[5].pos = D3DXVECTOR3(25.0f, 0.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Mob.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Mob.aModel[5].nIdx = 5;								//�C���f�b�N�X�ԍ�
	g_Mob.aModel[5].nIdxModelParent = 4;						//�e�̃C���f�b�N�X
																//�E��
	g_Mob.aModel[6].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Mob.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Mob.aModel[6].nIdx = 6;								//�C���f�b�N�X�ԍ�
	g_Mob.aModel[6].nIdxModelParent = 0;						//�e�̃C���f�b�N�X
																//�E��
	g_Mob.aModel[7].pos = D3DXVECTOR3(0.0f, -15.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Mob.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Mob.aModel[7].nIdx = 7;								//�C���f�b�N�X�ԍ�
	g_Mob.aModel[7].nIdxModelParent = 6;						//�e�̃C���f�b�N�X
																//����
	g_Mob.aModel[8].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Mob.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Mob.aModel[8].nIdx = 8;								//�C���f�b�N�X�ԍ�
	g_Mob.aModel[8].nIdxModelParent = 0;						//�e�̃C���f�b�N�X
																//����
	g_Mob.aModel[9].pos = D3DXVECTOR3(0.0f, -15.0f, 0.0f);;	//�ʒu�̏����ݒ�
	g_Mob.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Mob.aModel[9].nIdx = 9;								//�C���f�b�N�X�ԍ�
	g_Mob.aModel[9].nIdxModelParent = 8;						//�e�̃C���f�b�N�X

																//���[�V�����Z�b�g�̐ݒ�
																//�ҋ@���[�V����
	g_MobMotionSet.aMobKeySet[0].nNum_Key = 2;			//�L�[�̐�
	g_MobMotionSet.aMobKeySet[0].fFlame = 0.0f;			//�ŏ��̃t���[��
	g_MobMotionSet.aMobKeySet[0].bLoop = true;			//���[�v����
														//�L�[�t���[�����
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[0] = D3DXVECTOR3(0.0f, 20.5f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[1] = D3DXVECTOR3(0.0f, 30.5f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[2] = D3DXVECTOR3(0.0f, 0.0f, 0.5f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -0.5f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[6] = D3DXVECTOR3(0.0f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].fMaxFlame = 140.0f;	//�ő�t���[����
																//�L�[�t���[�����
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[6] = D3DXVECTOR3(0.0f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].fMaxFlame = 140.0f;	//�ő�t���[����

																//�ړ����[�V����
	g_MobMotionSet.aMobKeySet[1].nNum_Key = 4;			//�L�[�̐�
	g_MobMotionSet.aMobKeySet[1].fFlame = 0.0f;			//�ŏ��̃t���[��
	g_MobMotionSet.aMobKeySet[1].bLoop = true;			//���[�v����
														//�L�[�t���[�����1
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[2] = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[4] = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[6] = D3DXVECTOR3(-0.5f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[8] = D3DXVECTOR3(0.5f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].fMaxFlame = 150.0f;	//�ő�t���[����
																//�L�[�t���[�����
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[2] = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[4] = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[6] = D3DXVECTOR3(0.5f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[8] = D3DXVECTOR3(-0.5f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].fMaxFlame = 150.0f;	//�ő�t���[����
																//�L�[�t���[��3��
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[2] = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[4] = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[6] = D3DXVECTOR3(-0.5f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[8] = D3DXVECTOR3(0.5f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].fMaxFlame = 150.0f;	//�ő�t���[����
																//�L�[�t���[��4��
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[2] = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[4] = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[6] = D3DXVECTOR3(0.5f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[8] = D3DXVECTOR3(-0.5f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].fMaxFlame = 150.0f;	//�ő�t���[����

																//�������[�V����
	g_MobMotionSet.aMobKeySet[2].nNum_Key = 3;			//�L�[�̐�
	g_MobMotionSet.aMobKeySet[2].fFlame = 0.0f;			//�ŏ��̃t���[��
	g_MobMotionSet.aMobKeySet[2].bLoop = false;			//���[�v����
														//�L�[�t���[�����
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[0] = D3DXVECTOR3(0.0f, -0.75f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[2] = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[3] = D3DXVECTOR3(1.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[6] = D3DXVECTOR3(0.8f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].fMaxFlame = 150.0f;	//�ő�t���[����
																//�L�[�t���[�����
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[6] = D3DXVECTOR3(0.0f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].fMaxFlame = 150.0f;	//�ő�t���[����
																//�L�[�t���[��3��
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[0] = D3DXVECTOR3(0.0f, 0.75f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[2] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[6] = D3DXVECTOR3(-0.8f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].fMaxFlame = 150.0f;	//�ő�t���[����

	for (int nCntModel = 0; nCntModel < MAX_MOB_PARTS; nCntModel++)
	{
		//���_���擾
		nNumVtx = g_Mob.aModel[nCntModel].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y�擾
		sizeFVF = D3DXGetFVFVertexSize(g_Mob.aModel[nCntModel].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_Mob.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		//��r�̂��߂̐��l���
		g_Mob.vtxMax.x = -1000.0f;
		g_Mob.vtxMin.x = 1000.0f;
		g_Mob.vtxMax.y = -1000.0f;
		g_Mob.vtxMin.y = 1000.0f;
		g_Mob.vtxMax.z = -1000.0f;
		g_Mob.vtxMin.z = 1000.0f;

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ăv���C���[��Min,Max���擾
			if (vtx.x > g_Mob.vtxMax.x)
			{//X���W�̍ő�l
				g_Mob.vtxMax.x = vtx.x;
			}

			if (vtx.x < g_Mob.vtxMin.x)
			{//X���W�̍ŏ��l
				g_Mob.vtxMin.x = vtx.x;
			}

			if (vtx.y > g_Mob.vtxMax.y)
			{//Y���W�̍ő�l
				g_Mob.vtxMax.y = vtx.y;
			}

			if (vtx.y < g_Mob.vtxMin.y)
			{//Y���W�̍ŏ��l
				g_Mob.vtxMin.y = vtx.y;
			}

			if (vtx.z > g_Mob.vtxMax.z)
			{//Z���W�̍ő�l
				g_Mob.vtxMax.z = vtx.z;
			}

			if (vtx.z < g_Mob.vtxMin.z)
			{//Z���W�̍ŏ��l
				g_Mob.vtxMin.z = vtx.z;
			}
			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�A�����b�N
		g_Mob.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}

	FILE *pFile = fopen("data//TEXTFILE//mob.txt", "r");
	D3DXVECTOR3 posplayer;
	D3DXVECTOR3 rotplayer;
	char aData[128];
	fscanf(pFile, "pos = %f %f %f", &posplayer.x, &posplayer.y, &posplayer.z);
	fscanf(pFile, "%s", &aData[0]);
	fscanf(pFile, "%s", &aData[0]);
	fscanf(pFile, "%f", &rotplayer.x);
	fscanf(pFile, "%f", &rotplayer.y);
	fscanf(pFile, "%f", &rotplayer.z);
	/*fscanf(pFile, "rot = %f %f %f", &rotplayer.x, &rotplayer.y, &rotplayer.z);*/
	fclose(pFile);
	/*posplayer = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	rotplayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);*/
	g_Mob.bUse = false;
	g_Mob.pos = posplayer;					//�ʒu�̏����ݒ�
	g_Mob.rot = rotplayer;					//�����̏����ݒ�
	g_Mob.size.x = g_Mob.vtxMax.x - g_Mob.vtxMin.x;		//X�����̃T�C�Y
	g_Mob.size.z = g_Mob.vtxMax.z - g_Mob.vtxMin.z;		//Z�����̃T�C�Y
	g_Mob.IdxShadow = SetShadow(D3DXVECTOR3(g_Mob.pos.x, 0.5f, g_Mob.pos.z), g_Mob.rot);
	SetMob(posplayer, rotplayer, PLAYER_P1);
}

//===================================================================
//�v���C���[�̏I������
//===================================================================
void UninitMob(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MOB_PARTS; nCntModel++)
	{
		//�o�b�t�@�j��
		if (g_Mob.aModel[nCntModel].pMesh != NULL)
		{
			g_Mob.aModel[nCntModel].pMesh->Release();
			g_Mob.aModel[nCntModel].pMesh = NULL;
		}

		//�e�N�X�`���j��
		if (g_Mob.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Mob.aModel[nCntModel].pBuffMat->Release();
			g_Mob.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//===================================================================
//�v���C���[�̍X�V����
//===================================================================
void UpdateMob(void)
{
	int nPlayKeySet = g_MobMotionSet.nUseKeySet;				//�g�p���̃L�[�Z�b�g�̔ԍ��̕ϐ�
	MobKeySet* keyset = &g_MobMotionSet.aMobKeySet[nPlayKeySet];		//�g�p���̃L�[�Z�b�g
	int nPlaykey = keyset->nUseKey;							//�g�p���̃L�[�ԍ�
	MobKey* key = &keyset->aMobKey[nPlaykey];						//�g�p���̃L�[
	int nNextUsekey = (nPlaykey + 1) % keyset->nNum_Key;	//���̃L�[�ԍ�
	MobKey* nextkey = &keyset->aMobKey[nNextUsekey];				//���̃L�[

																	//�ړ�����
	SetMobMove();

	//���f���ɑ΂��ăL�[�Z�b�g��]�A�ʒu�̉��Z����
	for (int nCntModel = 0; nCntModel < MAX_MOB_PARTS; nCntModel++)
	{
		//�ڕW�܂ł̍���
		D3DXVECTOR3 diffpos = nextkey->pos[nCntModel] - key->pos[nCntModel];
		//���݂̏ꏊ
		g_Mob.aModel[nCntModel].pos = key->pos[nCntModel] + (diffpos / key->fMaxFlame) * keyset->fFlame;

		//�ڕW�܂ł̌X��
		D3DXVECTOR3 diffrot = nextkey->rot[nCntModel] - key->rot[nCntModel];
		//���݂̌X��
		g_Mob.aModel[nCntModel].rot = key->rot[nCntModel] + (diffrot / key->fMaxFlame) * keyset->fFlame;

		//���݂̃t���[�������Z�A�L�[�̏I������
		keyset->fFlame += 1.0f;

		if (keyset->fFlame >= key->fMaxFlame)
		{//�L�[���ŏI�t���[���ɓ��B
			if (nPlaykey + 1 == keyset->nNum_Key)
			{//�Ō�̃L�[�������ꍇ
				if (keyset->bLoop == true)
				{//���[�v���[�V�����̂Ƃ��ŏ��̃L�[�Ɉڍs
					keyset->fFlame = 0.0f;
					keyset->nUseKey = nNextUsekey;
				}
				else
				{//���[�v���[�V��������Ȃ��Ƃ��A���[�V�����I��
					keyset->bUse = false;
				}
			}
			else
			{//���̃L�[�Ɉڍs�i�Ō�ł͂Ȃ��j
				keyset->fFlame = 0.0f;
				keyset->nUseKey = nNextUsekey;
			}
		}
	}

	if (((g_MobMotionSet.nUseKeySet == 2) && (g_MobMotionSet.aMobKeySet[2].bUse == false)) ||
		(g_MobMotionSet.nUseKeySet != 2))
	{//�������[�V�����I��or����������������Ȃ�
	 //�L�[�Z�b�g��ύX
		if (g_Mob.move.x != 0.0f || g_Mob.move.z != 0.0f)
		{//�ړ����Ă���
			if (g_MobMotionSet.nUseKeySet != 1)
			{//�ړ����[�V�����ɂ���
				g_MobMotionSet.nUseKeySet = 1;
				g_MobMotionSet.aMobKeySet[1].nUseKey = 0;
				g_MobMotionSet.aMobKeySet[1].fFlame = 0.0f;
				g_MobMotionSet.aMobKeySet[1].bUse = true;
			}
		}
		else
		{//�~�܂��Ă���
			if (g_MobMotionSet.nUseKeySet != 0)
			{//�ҋ@���[�V�����ɂ���
				g_MobMotionSet.nUseKeySet = 0;
				g_MobMotionSet.aMobKeySet[0].nUseKey = 0;
				g_MobMotionSet.aMobKeySet[0].fFlame = 0.0f;
				g_MobMotionSet.aMobKeySet[0].bUse = true;
			}
		}
	}

	if (GetKeyboardTrigger(DIK_O) == true || GetControllerPressTrigger(1, XINPUT_GAMEPAD_A) == true)
	{//SPACE�L�[������or�W���C�p�b�hA�{�^������

		if (g_MobMotionSet.nUseKeySet != 2)
		{//�������[�V�����ɂ���
			g_MobMotionSet.nUseKeySet = 2;
			g_MobMotionSet.aMobKeySet[2].nUseKey = 0;
			g_MobMotionSet.aMobKeySet[2].fFlame = 0.0f;
			g_MobMotionSet.aMobKeySet[2].bUse = true;
			
		}

		SetMoveDisc(D3DXVECTOR3(g_Mob.rot),	//�p�x
			7.5f, SHOT_NOMAL,1);		//�f�B�X�N�̃X�s�[�h

		D3DXVECTOR3 move = D3DXVECTOR3(sinf(g_Mob.rot.y + D3DX_PI) * 1.0f, 0, cosf(g_Mob.rot.y + D3DX_PI) * 1.0f);
	}

	bool iMasat = CollisionField
	(
		&g_Mob.pos,
		&g_Mob.posOld,
		g_Mob.size / 2
	);

	CollisionEnemy
	(
		&g_Mob.pos,
		&g_Mob.posOld,
		&g_Mob.move,
		&g_Mob.size
	);

	CollisionDisc_Player(&g_Mob.pos, D3DXVECTOR3(10.0f, 40.0f, 10.0f), 1);

	SetPositionDisc(D3DXVECTOR3(g_Mob.pos.x, g_Mob.pos.y + 30.0f, g_Mob.pos.z - 30.0f), 1);
}

//===================================================================
//�v���C���[�̕`�揈��
//===================================================================
void DrawMob(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	if (g_Mob.bUse == false)
	{//false�̂Ƃ��ɕ`�悵�Ȃ�
		return;
	}

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Mob.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Mob.rot.y, g_Mob.rot.x, g_Mob.rot.z);
	D3DXMatrixMultiply(&g_Mob.mtxWorld, &g_Mob.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Mob.pos.x, g_Mob.pos.y, g_Mob.pos.z);
	D3DXMatrixMultiply(&g_Mob.mtxWorld, &g_Mob.mtxWorld, &mtxTrans);

	for (int nCntModel = 0; nCntModel < MAX_MOB_PARTS; nCntModel++)
	{
		//�v���C���[�p�[�c�̍\���̂̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Mob.aModel[nCntModel].mtxWorld);

		//�v���C���[�p�[�c�̍\���̂̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Mob.aModel[nCntModel].rot.y, g_Mob.aModel[nCntModel].rot.x, g_Mob.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Mob.aModel[nCntModel].mtxWorld, &g_Mob.aModel[nCntModel].mtxWorld, &mtxRot);

		//�v���C���[�p�[�c�̍\���̂̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Mob.aModel[nCntModel].pos.x, g_Mob.aModel[nCntModel].pos.y, g_Mob.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Mob.aModel[nCntModel].mtxWorld, &g_Mob.aModel[nCntModel].mtxWorld, &mtxTrans);

		//�����̐e�v���C���[�̃}�g���b�N�X�Ƃ̊|���Z
		D3DXMATRIX mtxParent;
		if (g_Mob.aModel[nCntModel].nIdxModelParent == -1)
		{
			mtxParent = g_Mob.mtxWorld;
		}

		else
		{
			mtxParent = g_Mob.aModel[g_Mob.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}

		D3DXMatrixMultiply(&g_Mob.aModel[nCntModel].mtxWorld, &g_Mob.aModel[nCntModel].mtxWorld, &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Mob.aModel[nCntModel].mtxWorld);

		//���݂̃}�e���A���ێ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Mob.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Mob.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//�}�e���A���ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�v���C���[�p�[�c�̕`��
			g_Mob.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}
	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===================================================================
//�v���C���[�̈ړ�����
//===================================================================
void SetMobMove(void)
{
	Camera *pCamera = GetCamera();
	Wall *Wall = GetWall();

	//�X�e�B�b�N�̏����擾
	D3DXVECTOR3 Stick = GetControllerStickDir(1);

	if (GetKeyboardPress(DIK_LEFT) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_LEFT) == true
		|| GetControllerStickPress(1, STICK_LEFT) == true)
	{//A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_UP) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_UP) == true)
		{//���O�ړ�
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (-D3DX_PI * 0.25f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (-D3DX_PI * 0.25f))* PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * 0.75f));
		}

		else if (GetKeyboardPress(DIK_DOWN) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{//�����ړ�
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (-D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (-D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * 0.25f));
		}

		else if (GetControllerStickPress(1, STICK_UP) == true || GetControllerStickPress(1, STICK_DOWN) == true)
		{//�X�e�B�b�N�̎΂�
			g_Mob.move.x -= Stick.x * PLAYER_SPEED;
			g_Mob.move.z -= Stick.y * PLAYER_SPEED;
		}

		else
		{//���ړ�
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (-D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (-D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * 0.5f));
		}
	}

	else if (GetKeyboardPress(DIK_RIGHT) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_RIGHT) == true
		|| GetControllerStickPress(1, STICK_RIGHT) == true)
	{//D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_DOWN) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{//�E���ړ�
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * -0.25f));
		}

		else if (GetKeyboardPress(DIK_UP) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_UP) == true)
		{//�E�O�ړ�
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (D3DX_PI * 0.25f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (D3DX_PI * 0.25f))* PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * -0.75f));
		}

		else if (GetControllerStickPress(1, STICK_UP) == true || GetControllerStickPress(1, STICK_DOWN) == true)
		{//�X�e�B�b�N�̎΂�
			g_Mob.move.x -= Stick.x * PLAYER_SPEED;
			g_Mob.move.z -= Stick.y * PLAYER_SPEED;
		}

		else
		{//�E�ړ�
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * -0.5f));
		}

	}

	else if (GetKeyboardPress(DIK_UP) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_UP) == true
		|| GetControllerStickPress(1, STICK_UP) == true)
	{//W�L�[�������ꂽ
	 //�O�ړ�
		g_Mob.move.x += sinf((pCamera + 1)->rot.y + (D3DX_PI * 0.0f)) * PLAYER_SPEED;
		g_Mob.move.z += cosf((pCamera + 1)->rot.y + (D3DX_PI * 0.0f)) * PLAYER_SPEED;
		g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * 1.0f));
	}

	else if (GetKeyboardPress(DIK_DOWN) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_DOWN) == true
		|| GetControllerStickPress(1, STICK_DOWN) == true)
	{//S�L�[�������ꂽ
	 //���ړ�
		g_Mob.move.x += sinf((pCamera + 1)->rot.y + (D3DX_PI * 1.0f)) * PLAYER_SPEED;
		g_Mob.move.z += cosf((pCamera + 1)->rot.y + (D3DX_PI * 1.0f)) * PLAYER_SPEED;
		g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * 0.0f));
	}


	//�O��̈ʒu��ۑ�
	g_Mob.posOld = g_Mob.pos;

	//�ʒu�X�V
	g_Mob.pos.x += g_Mob.move.x;
	g_Mob.pos.z += g_Mob.move.z;

	////�Ԃ������Ƃ��̓����蔻��
	/*CollisionEnemy(&g_Mob.pos,
	&g_Mob.posOld,
	&g_Mob.size,
	&g_Mob.move);*/

	//�ړ��ʍX�V�i�����j
	g_Mob.move.x += (0.0f - g_Mob.move.x) * 0.1f;	//�ړI�̒l-���݂̒l * �����W��
	g_Mob.move.z += (0.0f - g_Mob.move.z) * 0.1f;

	//���̐��l�����ɂȂ�����0�ɂ���
	if (g_Mob.move.x <= 0.1f && g_Mob.move.x >= -0.1f)
	{
		g_Mob.move.x = 0.0f;

	}

	if (g_Mob.move.z <= 0.1f && g_Mob.move.z >= -0.1f)
	{
		g_Mob.move.z = 0.0f;
	}
	SetPositionShadow(g_Mob.IdxShadow, D3DXVECTOR3(g_Mob.pos.x, 0.3f, g_Mob.pos.z));
}

//===================================================================
//�v���C���[�̐ݒu����
//===================================================================
void SetMob(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type)
{
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	for (int nCntPlayer = 0; nCntPlayer < MAX_MOB_PARTS; nCntPlayer++)
	{
		//���_�o�b�t�@�̃��b�N
		g_Mob.aModel[nCntPlayer].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		g_Mob.bUse = true;	//�g�p���Ă���
		g_Mob.pos = pos;		//�ʒu�̏����ݒ�
		g_Mob.rot = rot;		//�����̏����ݒ�

								//���_�o�b�t�@�A�����b�N
		g_Mob.aModel[nCntPlayer].pMesh->UnlockVertexBuffer();
	}
}

//===================================================================
//�擾����
//===================================================================
MOB* GetMob(void)
{
	return &g_Mob;
}