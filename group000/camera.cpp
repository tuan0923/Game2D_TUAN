//===================================================================
//
//3D�A�N�V����(camera.cpp)
//Author:�e���A��
//
//===================================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "mob.h"
//===================================================================
//�O���[�o���ϐ�
//===================================================================
Camera g_camera[2];
Player *pPlayer = GetPlayer();
MOB*pMob = GetMob();
//===================================================================
//�J�����̏���������
//===================================================================
void InitCamera(void)
{
	//�J�����@
	//���_�E�����_�E�������ݒ肷��
	g_camera[0].posV = D3DXVECTOR3(0.0f, 150.0f, 250.0f);	//�����_
	g_camera[0].posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);		//���_
	g_camera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//�����
	g_camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//y���ŉ�]����
	g_camera[0].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//posRDest�̏�����
	g_camera[0].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//posVDest�̏�����

	//���_�ƒ����_�Ԃ̋���
	g_camera[0].fDistance = sqrtf((g_camera[0].posV.x - g_camera[0].posR.x)*(g_camera[0].posV.x - g_camera[0].posR.x)
		+ (g_camera[0].posV.z - g_camera[0].posR.z)*(g_camera[0].posV.z - g_camera[0].posR.z));

	//�����_�ƖړI�̒����_�Ԃ̋���
	g_camera[0].fDistanceA = sqrtf((g_camera[0].posRDest.x - pPlayer->pos.x) * (g_camera[0].posRDest.x - pPlayer->pos.x)
		+ (g_camera[0].posRDest.z - pPlayer->pos.z)  * (g_camera[0].posRDest.z - pPlayer->pos.z));


	g_camera[0].viewport.MinZ = 0.0f;
	g_camera[0].viewport.MaxZ = 1.0f;
	g_camera[0].viewport.X = 0.0f;
	g_camera[0].viewport.Y = 0.0f;
	g_camera[0].viewport.Width = SCREEN_WIDTH / 2;
	g_camera[0].viewport.Height = 720.0f;

	//�J�����A
	//���_�E�����_�E�������ݒ肷��
	g_camera[1].posV = D3DXVECTOR3(0.0f, 150.0f, 250.0f);	//�����_
	g_camera[1].posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);		//���_
	g_camera[1].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//�����
	g_camera[1].rot = D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f);	//y���ŉ�]����
	g_camera[1].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//posRDest�̏�����
	g_camera[1].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//posVDest�̏�����


	 //���_�ƒ����_�Ԃ̋���

	g_camera[1].fDistance = sqrtf((g_camera[1].posV.x - g_camera[1].posR.x)*(g_camera[1].posV.x - g_camera[1].posR.x)
		+ (g_camera[1].posV.z - g_camera[1].posR.z)*(g_camera[1].posV.z - g_camera[1].posR.z));

	//�����_�ƖړI�̒����_�Ԃ̋���
	g_camera[1].fDistanceA = sqrtf((g_camera[1].posRDest.x - pMob->pos.x) * (g_camera[1].posRDest.x - pMob->pos.x)
		+ (g_camera[1].posRDest.z - pMob->pos.z)  * (g_camera[1].posRDest.z - pMob->pos.z));


	g_camera[1].viewport.MinZ = 0.0f;
	g_camera[1].viewport.MaxZ = 1.0f;
	g_camera[1].viewport.X = 640.0f;
	g_camera[1].viewport.Y = 0.0f;
	g_camera[1].viewport.Width = SCREEN_WIDTH / 2;
	g_camera[1].viewport.Height = 720.0f;
}
//===================================================================
//�J�����I������
//===================================================================
void UninitCamera(void)
{

}

//===================================================================
//�J�����X�V����
//===================================================================
void UpdateCamera(void)
{
	//�J�����ړ�����
	MoveCamera();
}

//===================================================================
//�J�����Z�b�g����
//===================================================================
void SetCamera(int nCnt)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nCnt].mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera[nCnt].mtxView,
		&g_camera[nCnt].posV,
		&g_camera[nCnt].posR,
		&g_camera[nCnt].vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nCnt].mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nCnt].mtxProjection);

	//�|���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera[nCnt].mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);
	//
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nCnt].mtxProjection);

}
//===============================================
Camera *GetCamera(void)
{

	return &g_camera[0];

}


//===================================================================
//�J�����ړ�����
//===================================================================
void MoveCamera(void)
{
	//�J�����@
	//�J�����̒Ǐ]����
	g_camera[0].posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * 10;
	g_camera[0].posRDest.y = pPlayer->pos.y;
	g_camera[0].posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * 10;

	g_camera[0].posVDest.x = pPlayer->pos.x - sinf(g_camera[0].rot.y) * 250;
	g_camera[0].posVDest.y = pPlayer->pos.y;
	g_camera[0].posVDest.z = pPlayer->pos.z - cosf(g_camera[0].rot.y) * 250;

	g_camera[0].posR.x += (g_camera[0].posRDest.x - g_camera[0].posR.x)*0.1f;
	g_camera[0].posV.x += (g_camera[0].posVDest.x - g_camera[0].posV.x)*0.1f;
	g_camera[0].posR.z += (g_camera[0].posRDest.z - g_camera[0].posR.z)*0.1f;
	g_camera[0].posV.z += (g_camera[0].posVDest.z - g_camera[0].posV.z)*0.1f;

	//�J�����A
	//�J�����̒Ǐ]����
	g_camera[1].posRDest.x = pMob->pos.x - sinf(pMob->rot.y) * 10;
	g_camera[1].posRDest.y = pMob->pos.y;
	g_camera[1].posRDest.z = pMob->pos.z - cosf(pMob->rot.y) *10;

	g_camera[1].posVDest.x = pMob->pos.x - sinf(g_camera[1].rot.y) *250;
	g_camera[1].posVDest.y = pMob->pos.y;
	g_camera[1].posVDest.z = pMob->pos.z - cosf(g_camera[1].rot.y) * 250;

	g_camera[1].posR.x += (g_camera[1].posRDest.x - g_camera[1].posR.x)*0.1f;
	g_camera[1].posV.x += (g_camera[1].posVDest.x - g_camera[1].posV.x)*0.1f;
	g_camera[1].posR.z += (g_camera[1].posRDest.z - g_camera[1].posR.z)*0.1f;
	g_camera[1].posV.z += (g_camera[1].posVDest.z - g_camera[1].posV.z)*0.1f;


	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_camera[nCnt].rot.y > D3DX_PI)
		{
			g_camera[nCnt].rot.y -= D3DX_PI * 2;
		}
		if (g_camera[nCnt].rot.y < -D3DX_PI)
		{
			g_camera[nCnt].rot.y += D3DX_PI * 2;
		}
	}

}