////----------------------------------------
////�@���f���̏���
////�@Author�F���슲��
////----------------------------------------
//#include "model.h"
//#include "camera.h"
//#include "input.h"
//#include "shadow.h"
//#include "disc.h"
//
//
////�O���[�o���ϐ��錾
//LPDIRECT3DTEXTURE9 g_pTextureModel = NULL;	//�e�N�X�`���ւ̃|�C���^
//LPD3DXMESH g_pMeshModel = NULL;				//���b�V�����ւ̃|�C���^
//LPD3DXBUFFER g_pBuffMatModel = NULL;		//�}�e���A�����ւ̃|�C���^
//DWORD g_nNumMatModel = 0;					//�}�e���A�����̐�
//Model g_aModel[MAX_MODEL];
////int g_SelectModel;							//���f���I��p
//
////�v���g�^�C�v�錾
//void MovePlayer1(void);
//
////---------------------------------------------------
////	���f���̏���������
////---------------------------------------------------
//void InitModel(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(
//		pDevice,
//		"data\\TEXTURE\\uroko_red.jpg",
//		&g_pTextureModel);
//
//	//�]�t�@�C���̓ǂݍ���
//	D3DXLoadMeshFromX("data\\MODEL\\tank100.x",
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&g_pBuffMatModel,
//		NULL,
//		&g_nNumMatModel,
//		&g_pMeshModel);
//
//	//�e�l�̏�����
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
//		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
//		g_aModel[nCntModel].diff = 0.0f;							//�����v�Z�p
//		g_aModel[nCntModel].rotDestModel = 0.0f;					//�ړI�̊p�x
//		g_aModel[nCntModel].IdxShadow = SetShadow(D3DXVECTOR3(g_aModel[nCntModel].pos.x, 0.1f, g_aModel[nCntModel].pos.z), g_aModel[nCntModel].rot);
//		g_aModel[nCntModel].bUse = false;							//�g���Ă邩�ǂ���
//	}
//	//g_SelectModel = 0;
//
//	//���f���Z�b�g
//	SetModel(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//
//
//	//�f�B�X�N�̈ʒu
//	SetPosDisc(D3DXVECTOR3(g_aModel[0].pos.x, g_aModel[0].pos.y + 20.0f, g_aModel[0].pos.z)/*, PLAYER_P1*/);
//}//���킟
//
////---------------------------------------------------
////	���f���̏I������
////---------------------------------------------------
//void UninitModel(void)
//{
//	//���b�V���j��
//	if (g_pMeshModel != NULL)
//	{
//		g_pMeshModel->Release();
//		g_pMeshModel = NULL;
//	}
//
//	//�}�e���A���j��
//	if (g_pBuffMatModel != NULL)
//	{
//		g_pBuffMatModel->Release();
//		g_pBuffMatModel = NULL;
//	}
//
//	//�e�N�X�`���j��
//	if (g_pTextureModel != NULL)
//	{
//		g_pTextureModel->Release();
//		g_pTextureModel = NULL;
//	}
//}
//
////---------------------------------------------------
////	���f���̍X�V����
////---------------------------------------------------
//void UpdateModel(void)
//{
//
//	//���f���̈ړ�����
//	MoveModel();
//
//	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
//	{
//		CollisionDisc_Player(&g_aModel[nCnt].pos, D3DXVECTOR3(5.0f, 5.0f, 5.0f), g_aModel[nCnt].type);
//	}
//
//	//�e�̈ʒu���X�V
//	SetPositionShadow(0, D3DXVECTOR3(g_aModel[0].pos.x, 0.1f, g_aModel[0].pos.z));
//
//	//SetPositionDisc(D3DXVECTOR3(g_aModel[0].pos.x, g_aModel[0].pos.y + 20.0f, g_aModel[0].pos.z));
//}
//
////---------------------------------------------------
////	���f���̈ړ�����
////---------------------------------------------------
//void MoveModel(void)
//{
//	MovePlayer1();
//}
//
////---------------------------------------------------
////	�v���C���[1�̈ړ�����
////---------------------------------------------------
//void MovePlayer1(void)
//{
//	Camera * pCamera = GetCamera();
//
//	if (GetKeyboardPress(DIK_UPARROW) == true)
//	{//���L�[�������ꂽ�Ƃ�
//		if (GetKeyboardPress(DIK_RIGHTARROW) == true)
//		{//���L�[�Ɖ����ꂽ�Ƃ�(���΂ߏ����)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4)) * MODEL_SPEED;	//���f���̈ʒu�ړ�
//			g_aModel[0].pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4)) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y - (D3DX_PI / 4 * 3.0f);			//���f���̌����ύX
//		}
//		else if (GetKeyboardPress(DIK_LEFTARROW) == true)
//		{//���L�[�Ɖ����ꂽ�Ƃ�(�E�΂ߏ����)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4)) * MODEL_SPEED;	//���f���̈ʒu�ړ�
//			g_aModel[0].pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4)) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y + (D3DX_PI / 4 * 3.0f);			//���f���̌����ύX
//		}
//		else
//		{//���L�[�̂�(������ֈړ�)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y) * MODEL_SPEED;	//���f���̈ʒu�ړ�
//			g_aModel[0].pos.z += cosf(pCamera->rot.y) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y + D3DX_PI;		//���f���̌����ύX
//		}
//	}
//	else if (GetKeyboardPress(DIK_DOWNARROW) == true)
//	{//���L�[�������ꂽ�Ƃ�
//		if (GetKeyboardPress(DIK_RIGHTARROW) == true)
//		{//���L�[�Ɖ����ꂽ�Ƃ�(���΂߉�����)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * MODEL_SPEED;		//���f���̈ʒu�ړ�
//			g_aModel[0].pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y - (D3DX_PI / 4);							//���f���̌����ύX
//		}
//		else if (GetKeyboardPress(DIK_LEFTARROW) == true)
//		{//���L�[�Ɖ����ꂽ�Ƃ�(�E�΂߉�����)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * MODEL_SPEED;		//���f���̈ʒu�ړ�
//			g_aModel[0].pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y + (D3DX_PI / 4);							//���f���̌����ύX
//		}
//		else
//		{//���L�[�̂�(�������ֈړ�)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y + D3DX_PI) * MODEL_SPEED;		//���f���̈ʒu�ړ�
//			g_aModel[0].pos.z += cosf(pCamera->rot.y + D3DX_PI) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y;								//���f���̌����ύX
//		}
//	}
//	else if (GetKeyboardPress(DIK_RIGHTARROW) == true)
//	{//���L�[�������ꂽ�Ƃ�(�E�����ֈړ�)
//		g_aModel[0].pos.x += sinf(pCamera->rot.y + (D3DX_PI / 2)) * MODEL_SPEED;	//���f���̈ʒu�ړ�
//		g_aModel[0].pos.z += cosf(pCamera->rot.y + (D3DX_PI / 2)) * MODEL_SPEED;
//
//		g_aModel[0].rotDestModel = pCamera->rot.y - (D3DX_PI / 2);					//���f���̌����ύX
//	}
//	else if (GetKeyboardPress(DIK_LEFTARROW) == true)
//	{//���L�[�������ꂽ�Ƃ�(�������ֈړ�)
//		g_aModel[0].pos.x += sinf(pCamera->rot.y - (D3DX_PI / 2)) * MODEL_SPEED;	//���f���̈ʒu�ړ�
//		g_aModel[0].pos.z += cosf(pCamera->rot.y - (D3DX_PI / 2)) * MODEL_SPEED;
//
//		g_aModel[0].rotDestModel = pCamera->rot.y + (D3DX_PI / 2);					//���f���̌����ύX
//	}
//
//	if (GetKeyboardTrigger(DIK_SPACE) == true)
//	{//�X�y�[�X�L�[�������ꂽ��
//
//		SetMoveDisc(D3DXVECTOR3(g_aModel[0].rot),	//�p�x
//			//g_aModel[0].type,		//P1�Ƃ������
//			7.5f, SHOT_NOMAL);		//�f�B�X�N�̃X�s�[�h
//
//		
//		
//		//D3DXVECTOR3(g_aModel[0].rot));	//�p�x
//		
//	}
//
//	if (GetKeyboardTrigger(DIK_N) == true)
//	{
//		SetMoveDisc(D3DXVECTOR3(g_aModel[0].rot),	//�p�x
//			//g_aModel[0].type,	//P1�Ƃ������
//			1.0f, SHOT_CURVE);		//�f�B�X�N�̃X�s�[�h
//	}
//
//	//if (GetKeyboardTrigger(DIK_M) == true)
//	//{
//	//	SetMoveDisc(D3DXVECTOR3(g_aModel[0].rot),	//�p�x
//	//		//g_aModel[0].type,	//P1�Ƃ������
//	//		1.0f, SHOT_CIRCLE);		//�f�B�X�N�̃X�s�[�h
//	//}
//
//	//�p�x�̐��K��
//	if (g_aModel[0].rot.y > D3DX_PI)
//	{
//		g_aModel[0].rot.y -= D3DX_PI * 2;
//	}
//	else if (g_aModel[0].rot.y < -D3DX_PI)
//	{
//		g_aModel[0].rot.y += D3DX_PI * 2;
//	}
//
//	//�����̌v�Z
//	g_aModel[0].diff = (g_aModel[0].rotDestModel - g_aModel[0].rot.y);
//
//	//�����̐��K��
//	if (g_aModel[0].diff > D3DX_PI)
//	{
//		g_aModel[0].diff -= D3DX_PI * 2;
//	}
//	else if (g_aModel[0].diff < -D3DX_PI)
//	{
//		g_aModel[0].diff += D3DX_PI * 2;
//	}
//
//	//���f���̈ړ������炩�ɂ�����
//	g_aModel[0].rot.y += g_aModel[0].diff * 0.1f;
//}
//
////---------------------------------------------------
////	���f���̕`�揈��
////---------------------------------------------------
//void DrawModel(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
//	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
//	D3DXMATERIAL * pMat;			//�}�e���A���f�[�^�ւ̃|�C���^
//
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		if (g_aModel[nCntModel].bUse == true)
//		{
//			//���[���h�}�g���b�N�X�̏�����
//			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);
//
//			//�����𔽉f
//			D3DXMatrixRotationYawPitchRoll(&mtxRot,
//				g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
//			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld,
//				&g_aModel[nCntModel].mtxWorld, &mtxRot);
//
//			//�ʒu�𔽉f
//			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
//			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);
//
//			//���[���h�}�g���b�N�X�̐ݒ�
//			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);
//
//			//���݂̃}�e���A���ێ�
//			pDevice->GetMaterial(&matDef);
//
//			//�}�e���A���f�[�^�ւ̃|�C���^���擾
//			pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
//
//			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
//			{
//				//�}�e���A���̐ݒ�
//				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//				//���f���p�[�c�̕`��
//				g_pMeshModel->DrawSubset(nCntMat);
//
//				//�e�N�X�`���̐ݒ�
//				pDevice->SetTexture(0, NULL);
//			}
//
//			//�ێ����Ă����}�e���A����߂�
//			pDevice->SetMaterial(&matDef);
//		}
//	}
//}
//
////---------------------------------------------------
////	���f���̏��
////---------------------------------------------------
//Model * GetModel(void)
//{
//	return g_aModel;
//}
//
////---------------------------------------------------
////	���f���̐ݒ�
////---------------------------------------------------
//void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
//{
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		if (g_aModel[nCntModel].bUse == false)
//		{// bUse��false��������A
//			g_aModel[nCntModel].pos = pos;
//			g_aModel[nCntModel].rot = rot;
//			g_aModel[nCntModel].bUse = true;
//			//g_aModel[nCntModel].type ;
//
//			break;
//		}
//	}
//}
