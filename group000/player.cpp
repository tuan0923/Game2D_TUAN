//===================================================================
//
//3D�A�N�V����(player.cpp)
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
#include "score.h"
#include"Field.h"
#include"sound.h"
#include "controller.h"
#include"ink.h"
#include"disc.h"
#include"enemy.h"
#include"controller.h"
//===================================================================
//�O���[�o���ϐ�
//===================================================================
Player g_Player;								//�v���C���[�\����
Key g_aKey;										//�L�[�\����
KeySet g_aKeySet;								//�L�[�Z�b�g�\����
MotionSet g_MotionSet;							//���[�V�����\����
Ink  g_Ink;

//===================================================================
//�v���C���[�̏������ݒ�
//===================================================================
void InitPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ZeroMemory(&g_Player, sizeof(g_Player)); //�\���̕ϐ����N���A�ł���֗��֐�

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data//MODEL//player_body.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[0].pBuffMat,
		NULL,
		&g_Player.aModel[0].nNumMat,
		&g_Player.aModel[0].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[1].pBuffMat,
		NULL,
		&g_Player.aModel[1].nNumMat,
		&g_Player.aModel[1].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_armR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[2].pBuffMat,
		NULL,
		&g_Player.aModel[2].nNumMat,
		&g_Player.aModel[2].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_handR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[3].pBuffMat,
		NULL,
		&g_Player.aModel[3].nNumMat,
		&g_Player.aModel[3].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_armL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[4].pBuffMat,
		NULL,
		&g_Player.aModel[4].nNumMat,
		&g_Player.aModel[4].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_handL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[5].pBuffMat,
		NULL,
		&g_Player.aModel[5].nNumMat,
		&g_Player.aModel[5].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_legR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[6].pBuffMat,
		NULL,
		&g_Player.aModel[6].nNumMat,
		&g_Player.aModel[6].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_footR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[7].pBuffMat,
		NULL,
		&g_Player.aModel[7].nNumMat,
		&g_Player.aModel[7].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_legL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[8].pBuffMat,
		NULL,
		&g_Player.aModel[8].nNumMat,
		&g_Player.aModel[8].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_footL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[9].pBuffMat,
		NULL,
		&g_Player.aModel[9].nNumMat,
		&g_Player.aModel[9].pMesh);

	//��
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);		//�ʒu�̏����ݒ�
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Player.aModel[0].nIdx = 0;								//�C���f�b�N�X�ԍ�
	g_Player.aModel[0].nIdxModelParent = -1;					//�e�̃C���f�b�N�X
																//��
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Player.aModel[1].nIdx = 1;								//�C���f�b�N�X�ԍ�
	g_Player.aModel[1].nIdxModelParent = 0;						//�e�̃C���f�b�N�X
																//�E�r
	g_Player.aModel[2].pos = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Player.aModel[2].nIdx = 2;								//�C���f�b�N�X�ԍ�
	g_Player.aModel[2].nIdxModelParent = 0;						//�e�̃C���f�b�N�X
																//�E��
	g_Player.aModel[3].pos = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);		//�ʒu�̏����ݒ�
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Player.aModel[3].nIdx = 3;								//�C���f�b�N�X�ԍ�
	g_Player.aModel[3].nIdxModelParent = 2;						//�e�̃C���f�b�N�X
																//���r
	g_Player.aModel[4].pos = D3DXVECTOR3(15.0f, 30.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Player.aModel[4].nIdx = 4;								//�C���f�b�N�X�ԍ�
	g_Player.aModel[4].nIdxModelParent = 0;						//�e�̃C���f�b�N�X
																//����
	g_Player.aModel[5].pos = D3DXVECTOR3(25.0f, 0.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Player.aModel[5].nIdx = 5;								//�C���f�b�N�X�ԍ�
	g_Player.aModel[5].nIdxModelParent = 4;						//�e�̃C���f�b�N�X
																//�E��
	g_Player.aModel[6].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Player.aModel[6].nIdx = 6;								//�C���f�b�N�X�ԍ�
	g_Player.aModel[6].nIdxModelParent = 0;						//�e�̃C���f�b�N�X
																//�E��
	g_Player.aModel[7].pos = D3DXVECTOR3(0.0f, -15.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Player.aModel[7].nIdx = 7;								//�C���f�b�N�X�ԍ�
	g_Player.aModel[7].nIdxModelParent = 6;						//�e�̃C���f�b�N�X
																//����
	g_Player.aModel[8].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//�ʒu�̏����ݒ�
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Player.aModel[8].nIdx = 8;								//�C���f�b�N�X�ԍ�
	g_Player.aModel[8].nIdxModelParent = 0;						//�e�̃C���f�b�N�X
																//����
	g_Player.aModel[9].pos = D3DXVECTOR3(0.0f, -15.0f, 0.0f);;	//�ʒu�̏����ݒ�
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏����ݒ�
	g_Player.aModel[9].nIdx = 9;								//�C���f�b�N�X�ԍ�
	g_Player.aModel[9].nIdxModelParent = 8;						//�e�̃C���f�b�N�X

																//���[�V�����Z�b�g�̐ݒ�
																//�ҋ@���[�V����
	g_MotionSet.aKeySet[0].nNum_Key = 2;			//�L�[�̐�
	g_MotionSet.aKeySet[0].fFlame = 0.0f;			//�ŏ��̃t���[��
	g_MotionSet.aKeySet[0].bLoop = true;			//���[�v����
													//�L�[�t���[�����
	g_MotionSet.aKeySet[0].aKey[0].pos[0] = D3DXVECTOR3(0.0f, 20.5f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].rot[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].pos[1] = D3DXVECTOR3(0.0f, 30.5f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].rot[2] = D3DXVECTOR3(0.0f, 0.0f, 0.5f);
	g_MotionSet.aKeySet[0].aKey[0].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -0.5f);
	g_MotionSet.aKeySet[0].aKey[0].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].rot[6] = D3DXVECTOR3(0.0f, 0.0f, -0.09f);
	g_MotionSet.aKeySet[0].aKey[0].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MotionSet.aKeySet[0].aKey[0].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[0].fMaxFlame = 140.0f;	//�ő�t���[����
														//�L�[�t���[�����
	g_MotionSet.aKeySet[0].aKey[1].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].rot[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].rot[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].rot[4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].rot[6] = D3DXVECTOR3(0.0f, 0.0f, -0.09f);
	g_MotionSet.aKeySet[0].aKey[1].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MotionSet.aKeySet[0].aKey[1].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[0].aKey[1].fMaxFlame = 140.0f;	//�ő�t���[����

														//�ړ����[�V����
	g_MotionSet.aKeySet[1].nNum_Key = 4;			//�L�[�̐�
	g_MotionSet.aKeySet[1].fFlame = 0.0f;			//�ŏ��̃t���[��
	g_MotionSet.aKeySet[1].bLoop = true;			//���[�v����
													//�L�[�t���[�����1
	g_MotionSet.aKeySet[1].aKey[0].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].rot[2] = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	g_MotionSet.aKeySet[1].aKey[0].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].rot[4] = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
	g_MotionSet.aKeySet[1].aKey[0].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].rot[6] = D3DXVECTOR3(-0.5f, 0.0f, -0.09f);
	g_MotionSet.aKeySet[1].aKey[0].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].rot[8] = D3DXVECTOR3(0.5f, 0.0f, 0.09f);
	g_MotionSet.aKeySet[1].aKey[0].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[0].fMaxFlame = 150.0f;	//�ő�t���[����
														//�L�[�t���[�����
	g_MotionSet.aKeySet[1].aKey[1].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].rot[2] = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	g_MotionSet.aKeySet[1].aKey[1].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].rot[4] = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
	g_MotionSet.aKeySet[1].aKey[1].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].rot[6] = D3DXVECTOR3(0.5f, 0.0f, -0.09f);
	g_MotionSet.aKeySet[1].aKey[1].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].rot[8] = D3DXVECTOR3(-0.5f, 0.0f, 0.09f);
	g_MotionSet.aKeySet[1].aKey[1].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[1].fMaxFlame = 150.0f;	//�ő�t���[����
														//�L�[�t���[��3��
	g_MotionSet.aKeySet[1].aKey[2].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].rot[2] = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	g_MotionSet.aKeySet[1].aKey[2].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].rot[4] = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
	g_MotionSet.aKeySet[1].aKey[2].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].rot[6] = D3DXVECTOR3(-0.5f, 0.0f, -0.09f);
	g_MotionSet.aKeySet[1].aKey[2].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].rot[8] = D3DXVECTOR3(0.5f, 0.0f, 0.09f);
	g_MotionSet.aKeySet[1].aKey[2].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[2].fMaxFlame = 150.0f;	//�ő�t���[����
														//�L�[�t���[��4��
	g_MotionSet.aKeySet[1].aKey[3].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].rot[2] = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	g_MotionSet.aKeySet[1].aKey[3].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].rot[4] = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
	g_MotionSet.aKeySet[1].aKey[3].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].rot[6] = D3DXVECTOR3(0.5f, 0.0f, -0.09f);
	g_MotionSet.aKeySet[1].aKey[3].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].rot[8] = D3DXVECTOR3(-0.5f, 0.0f, 0.09f);
	g_MotionSet.aKeySet[1].aKey[3].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[1].aKey[3].fMaxFlame = 150.0f;	//�ő�t���[����

														//�������[�V����
	g_MotionSet.aKeySet[2].nNum_Key = 3;			//�L�[�̐�
	g_MotionSet.aKeySet[2].fFlame = 0.0f;			//�ŏ��̃t���[��
	g_MotionSet.aKeySet[2].bLoop = false;			//���[�v����
													//�L�[�t���[�����
	g_MotionSet.aKeySet[2].aKey[0].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].rot[0] = D3DXVECTOR3(0.0f, -0.75f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].rot[2] = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	g_MotionSet.aKeySet[2].aKey[0].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].rot[3] = D3DXVECTOR3(1.0f, -0.25f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MotionSet.aKeySet[2].aKey[0].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].rot[6] = D3DXVECTOR3(0.8f, 0.0f, -0.09f);
	g_MotionSet.aKeySet[2].aKey[0].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MotionSet.aKeySet[2].aKey[0].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[0].fMaxFlame = 150.0f;	//�ő�t���[����
														//�L�[�t���[�����
	g_MotionSet.aKeySet[2].aKey[1].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].rot[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].rot[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MotionSet.aKeySet[2].aKey[1].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].rot[6] = D3DXVECTOR3(0.0f, 0.0f, -0.09f);
	g_MotionSet.aKeySet[2].aKey[1].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MotionSet.aKeySet[2].aKey[1].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[1].fMaxFlame = 150.0f;	//�ő�t���[����
														//�L�[�t���[��3��
	g_MotionSet.aKeySet[2].aKey[2].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].rot[0] = D3DXVECTOR3(0.0f, 0.75f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].rot[2] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MotionSet.aKeySet[2].aKey[2].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MotionSet.aKeySet[2].aKey[2].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].rot[6] = D3DXVECTOR3(-0.8f, 0.0f, -0.09f);
	g_MotionSet.aKeySet[2].aKey[2].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MotionSet.aKeySet[2].aKey[2].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MotionSet.aKeySet[2].aKey[2].fMaxFlame = 150.0f;	//�ő�t���[����

	for (int nCntModel = 0; nCntModel < MAX_PLAYER_PARTS; nCntModel++)
	{
		//���_���擾
		nNumVtx = g_Player.aModel[nCntModel].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y�擾
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_Player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		//��r�̂��߂̐��l���
		g_Player.vtxMax.x = -1000.0f;
		g_Player.vtxMin.x = 1000.0f;
		g_Player.vtxMax.y = -1000.0f;
		g_Player.vtxMin.y = 1000.0f;
		g_Player.vtxMax.z = -1000.0f;
		g_Player.vtxMin.z = 1000.0f;

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ăv���C���[��Min,Max���擾
			if (vtx.x > g_Player.vtxMax.x)
			{//X���W�̍ő�l
				g_Player.vtxMax.x = vtx.x;
			}

			if (vtx.x < g_Player.vtxMin.x)
			{//X���W�̍ŏ��l
				g_Player.vtxMin.x = vtx.x;
			}

			if (vtx.y > g_Player.vtxMax.y)
			{//Y���W�̍ő�l
				g_Player.vtxMax.y = vtx.y;
			}

			if (vtx.y < g_Player.vtxMin.y)
			{//Y���W�̍ŏ��l
				g_Player.vtxMin.y = vtx.y;
			}

			if (vtx.z > g_Player.vtxMax.z)
			{//Z���W�̍ő�l
				g_Player.vtxMax.z = vtx.z;
			}

			if (vtx.z < g_Player.vtxMin.z)
			{//Z���W�̍ŏ��l
				g_Player.vtxMin.z = vtx.z;
			}
			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�A�����b�N
		g_Player.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}

	FILE *pFile = fopen("data//TEXTFILE//player.txt", "r");
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
	g_Player.bUse = false;
	g_Player.pos = posplayer;					//�ʒu�̏����ݒ�
	g_Player.rot = rotplayer;					//�����̏����ݒ�
	g_Player.size.x = g_Player.vtxMax.x - g_Player.vtxMin.x;		//X�����̃T�C�Y
	g_Player.size.y = g_Player.vtxMax.y - g_Player.vtxMin.y;		//X�����̃T�C�Y
	g_Player.size.z = g_Player.vtxMax.z - g_Player.vtxMin.z;		//Z�����̃T�C�Y
	g_Player.IdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 0.5f, g_Player.pos.z), g_Player.rot);
	SetPlayer(posplayer, rotplayer, PLAYER_P1);
	//�f�B�X�N�̈ʒu
	SetPosDisc(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 20.0f, g_Player.pos.z + 30.0f), 0);
}

//===================================================================
//�v���C���[�̏I������
//===================================================================
void UninitPlayer(void)
{
	//�T�E���h�̒�~
	StopSound();
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_PARTS; nCntModel++)
	{
		//�o�b�t�@�j��
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}

		//�e�N�X�`���j��
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//===================================================================
//�v���C���[�̍X�V����
//===================================================================
void UpdatePlayer(void)
{
	int nPlayKeySet = g_MotionSet.nUseKeySet;				//�g�p���̃L�[�Z�b�g�̔ԍ��̕ϐ�
	KeySet* keyset = &g_MotionSet.aKeySet[nPlayKeySet];		//�g�p���̃L�[�Z�b�g
	int nPlaykey = keyset->nUseKey;							//�g�p���̃L�[�ԍ�
	Key* key = &keyset->aKey[nPlaykey];						//�g�p���̃L�[
	int nNextUsekey = (nPlaykey + 1) % keyset->nNum_Key;	//���̃L�[�ԍ�
	Key* nextkey = &keyset->aKey[nNextUsekey];				//���̃L�[

															//���f���ɑ΂��ăL�[�Z�b�g��]�A�ʒu�̉��Z����
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_PARTS; nCntModel++)
	{
		//�ڕW�܂ł̍���
		D3DXVECTOR3 diffpos = nextkey->pos[nCntModel] - key->pos[nCntModel];
		//���݂̏ꏊ
		g_Player.aModel[nCntModel].pos = key->pos[nCntModel] + (diffpos / key->fMaxFlame) * keyset->fFlame;

		//�ڕW�܂ł̌X��
		D3DXVECTOR3 diffrot = nextkey->rot[nCntModel] - key->rot[nCntModel];
		//���݂̌X��
		g_Player.aModel[nCntModel].rot = key->rot[nCntModel] + (diffrot / key->fMaxFlame) * keyset->fFlame;

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

	//�ړ�����
	SetMove();

	if (((g_MotionSet.nUseKeySet == 2) && (g_MotionSet.aKeySet[2].bUse == false)) ||
		(g_MotionSet.nUseKeySet != 2))
	{//�U�����[�V�����I��or���������U������Ȃ�
	 //�L�[�Z�b�g��ύX
		if (g_Player.move.x != 0.0f || g_Player.move.z != 0.0f)
		{//�ړ����Ă���
			if (g_MotionSet.nUseKeySet != 1)
			{//�ړ����[�V�����ɂ���
				g_MotionSet.nUseKeySet = 1;
				g_MotionSet.aKeySet[1].nUseKey = 0;
				g_MotionSet.aKeySet[1].fFlame = 0.0f;
				g_MotionSet.aKeySet[1].bUse = true;
			}
		}
		else
		{//�~�܂��Ă���
			if (g_MotionSet.nUseKeySet != 0)
			{//�ҋ@���[�V�����ɂ���
				g_MotionSet.nUseKeySet = 0;
				g_MotionSet.aKeySet[0].nUseKey = 0;
				g_MotionSet.aKeySet[0].fFlame = 0.0f;
				g_MotionSet.aKeySet[0].bUse = true;
			}
		}
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A) == true)
	{//SPACE�L�[������or�W���C�p�b�hA�{�^������
	 //keyset->nUseKey = 0;
		if (g_MotionSet.nUseKeySet != 2)
		{//�������[�V�����ɂ���

		 //�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_Throw);
			g_MotionSet.nUseKeySet = 2;
			g_MotionSet.aKeySet[2].nUseKey = 0;
			g_MotionSet.aKeySet[2].fFlame = 0.0f;
			g_MotionSet.aKeySet[2].bUse = true;

			SetMoveDisc(D3DXVECTOR3(g_Player.rot),	//�p�x
				7.5f, SHOT_NOMAL,0);		//�f�B�X�N�̃X�s�[�h
		}


		D3DXVECTOR3 move = D3DXVECTOR3(sinf(g_Player.rot.y + D3DX_PI) * 1.0f, 0, cosf(g_Player.rot.y + D3DX_PI) * 1.0f);
	}


	bool iMasat = CollisionField
	(
		&g_Player.pos,
		&g_Player.posOld,
		g_Player.size / 2
	);

	CollisionEnemy
	(
		&g_Player.pos,
		&g_Player.posOld,
		&g_Player.move,
		&g_Player.size
	);

	CollisionDisc_Player(&g_Player.pos, D3DXVECTOR3(10.0f, 40.0f, 10.0f), 0);

	SetPositionDisc(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 30.0f, g_Player.pos.z + 30.0f), 0);
}

//===================================================================
//�v���C���[�̕`�揈��
//===================================================================
void DrawPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	if (g_Player.bUse == false)
	{//false�̂Ƃ��ɕ`�悵�Ȃ�
		return;
	}

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	for (int nCntModel = 0; nCntModel < MAX_PLAYER_PARTS; nCntModel++)
	{
		//�v���C���[�p�[�c�̍\���̂̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		//�v���C���[�p�[�c�̍\���̂̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRot);

		//�v���C���[�p�[�c�̍\���̂̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTrans);

		//�����̐e�v���C���[�̃}�g���b�N�X�Ƃ̊|���Z
		D3DXMATRIX mtxParent;
		if (g_Player.aModel[nCntModel].nIdxModelParent == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}

		else
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}

		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

		//���݂̃}�e���A���ێ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//�}�e���A���ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�v���C���[�p�[�c�̕`��
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}
	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===================================================================
//�v���C���[�̈ړ�����
//===================================================================
void SetMove(void)
{
	Camera *Camera = GetCamera();
	Wall *Wall = GetWall();

	//�X�e�B�b�N�̏����擾
	D3DXVECTOR3 Stick = GetControllerStickDir(0);

	if (GetKeyboardPress(DIK_A) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_LEFT) == true
		|| GetControllerStickPress(0, STICK_LEFT) == true)
	{//A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_W) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_UP) == true)
		{//���O�ړ�
			g_Player.move.x += sinf(Camera->rot.y + (-D3DX_PI * 0.25f)) * PLAYER_SPEED;
			g_Player.move.z += cosf(Camera->rot.y + (-D3DX_PI * 0.25f))* PLAYER_SPEED;
			g_Player.rot.y = (Camera->rot.y + (D3DX_PI * 0.75f));
		}

		else if (GetKeyboardPress(DIK_S) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{//�����ړ�
			g_Player.move.x += sinf(Camera->rot.y + (-D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Player.move.z += cosf(Camera->rot.y + (-D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Player.rot.y = (Camera->rot.y + (D3DX_PI * 0.25f));
		}
		else if (GetControllerStickPress(0, STICK_UP) == true || GetControllerStickPress(0, STICK_DOWN) == true)
		{//�X�e�B�b�N�̎΂�
			g_Player.move.x += Stick.x * PLAYER_SPEED;
			g_Player.move.z += Stick.y * PLAYER_SPEED;
		}
		else
		{//���ړ�
			g_Player.move.x += sinf(Camera->rot.y + (-D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Player.move.z += cosf(Camera->rot.y + (-D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Player.rot.y = (Camera->rot.y + (D3DX_PI * 0.5f));
		}
	}

	else if (GetKeyboardPress(DIK_D) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_RIGHT) == true
		|| GetControllerStickPress(0, STICK_RIGHT) == true)
	{//D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_S) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{//�E���ړ�
			g_Player.move.x += sinf(Camera->rot.y + (D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Player.move.z += cosf(Camera->rot.y + (D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Player.rot.y = (Camera->rot.y + (D3DX_PI * -0.25f));
		}

		else if (GetKeyboardPress(DIK_W) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_UP) == true)
		{//�E�O�ړ�
			g_Player.move.x += sinf(Camera->rot.y + (D3DX_PI * 0.25f)) * PLAYER_SPEED;
			g_Player.move.z += cosf(Camera->rot.y + (D3DX_PI * 0.25f))* PLAYER_SPEED;
			g_Player.rot.y = (Camera->rot.y + (D3DX_PI * -0.75f));
		}
		else if (GetControllerStickPress(0, STICK_UP) == true || GetControllerStickPress(0, STICK_DOWN) == true)
		{//�X�e�B�b�N�̎΂�
			g_Player.move.x += Stick.x * PLAYER_SPEED;
			g_Player.move.z += Stick.y * PLAYER_SPEED;
		}
		else
		{//�E�ړ�
			g_Player.move.x += sinf(Camera->rot.y + (D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Player.move.z += cosf(Camera->rot.y + (D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Player.rot.y = (Camera->rot.y + (D3DX_PI * -0.5f));
		}

	}

	else if (GetKeyboardPress(DIK_W) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_UP) == true
		|| GetControllerStickPress(0, STICK_UP) == true)
	{//W�L�[�������ꂽ
	 //�O�ړ�
		g_Player.move.x += sinf(Camera->rot.y + (D3DX_PI * 0.0f)) * PLAYER_SPEED;
		g_Player.move.z += cosf(Camera->rot.y + (D3DX_PI * 0.0f)) * PLAYER_SPEED;
		g_Player.rot.y = (Camera->rot.y + (D3DX_PI * 1.0f));
	}

	else if (GetKeyboardPress(DIK_S) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_DOWN) == true
		|| GetControllerStickPress(0, STICK_DOWN) == true)
	{//S�L�[�������ꂽ
	 //���ړ�
		g_Player.move.x += sinf(Camera->rot.y + (D3DX_PI * 1.0f)) * PLAYER_SPEED;
		g_Player.move.z += cosf(Camera->rot.y + (D3DX_PI * 1.0f)) * PLAYER_SPEED;
		g_Player.rot.y = (Camera->rot.y + (D3DX_PI * 0.0f));
	}

	//�O��̈ʒu��ۑ�
	g_Player.posOld = g_Player.pos;

	//�ʒu�X�V
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.z += g_Player.move.z;

	////�Ԃ������Ƃ��̓����蔻��
	/*CollisionEnemy(&g_Player.pos,
	&g_Player.posOld,
	&g_Player.size,
	&g_Player.move);*/

	//�ړ��ʍX�V�i�����j
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.1f;	//�ړI�̒l-���݂̒l * �����W��
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.1f;

	//���̐��l�����ɂȂ�����0�ɂ���
	if (g_Player.move.x <= 0.1f && g_Player.move.x >= -0.1f)
	{
		g_Player.move.x = 0.0f;

	}

	if (g_Player.move.z <= 0.1f && g_Player.move.z >= -0.1f)
	{
		g_Player.move.z = 0.0f;
	}

	SetPositionShadow(g_Player.IdxShadow, D3DXVECTOR3(g_Player.pos.x, 0.3f, g_Player.pos.z));
}

//===================================================================
//�v���C���[�̐ݒu����
//===================================================================
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type)
{
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_PARTS; nCntPlayer++)
	{
		//���_�o�b�t�@�̃��b�N
		g_Player.aModel[nCntPlayer].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		g_Player.bUse = true;	//�g�p���Ă���
		g_Player.pos = pos;		//�ʒu�̏����ݒ�
		g_Player.rot = rot;		//�����̏����ݒ�

								//���_�o�b�t�@�A�����b�N
		g_Player.aModel[nCntPlayer].pMesh->UnlockVertexBuffer();
	}
}

//===================================================================
//�擾����
//===================================================================
Player* GetPlayer(void)
{
	return &g_Player;
}