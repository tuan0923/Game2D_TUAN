

//----------------------------------------
//�@�v���C���[�̏���
//�@Author�F���슲��
//----------------------------------------
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "bullet.h"
#include "effect.h"
#include "line.h"
#include "model.h"
#include "fade.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;	//�e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshPlayer = NULL;			//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer = NULL;		//�}�e���A�����ւ̃|�C���^
DWORD g_nNumMatPlayer = 0;					//�}�e���A�����̐�
Player g_Player;							//�v���C���[�̕ϐ��錾

int nNowFrame = 0;		//���݂̃t���[����
int nCntFrame = 0;		//���Đ��t���[����
int nNowKeySet = 0;					//���ݍĐ�����KeySet�ԍ�
int nNextKeySet = nNowKeySet + 1;	//���ɍĐ�����KeySet�ԍ�
int nPlayMotion = 0;	//���ݍĐ����̃��[�V�����ԍ�
int g_MaxSetMotion;

//�p�[�c�Z�b�g�̍\����
typedef struct
{
	int nIndex;
	int nParent;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
}PartsSet;

//���[�V�����Z�b�g�̍\����
typedef struct
{
	int nLoop;				//���[�v���邩�ǂ���
	int nNumKey;			//�ő�L�[��
	int nFrame;				//�t���[����
	D3DXVECTOR3 pos[20];
	D3DXVECTOR3 rot[20];
}MotionSet;

FILE * pFile;
int g_nNumModel = 0;
int g_nNumParts = 0;
char g_aModelPas[20][256];
PartsSet g_PartsSet[20];
MotionSet g_MotionSet[10][10];
D3DXVECTOR3 MotionDiff[20];
D3DXVECTOR3 PosDiff[20];
int nMaxFram[20];			//���v�t���[����

							//---------------------------------------------------
							//	�v���C���[�̃��[�V�����ǂݍ���
							//---------------------------------------------------
void Load(void)
{
	char nData111[256];
	int nData;
	float fData;
	int nCntModel = 0;
	int nCntParts = 0;
	int nCntMotion = 0;
	int nCntKeyParts = 0;
	int nCntKey = 0;

	pFile = fopen("data\\motion.txt", "r");

	// strncmp : �w�肵����������r����
	// sscanf : �w�肵������ϐ��ɓ����
	// fgetc : ��s��ǂݍ���

	if (pFile != NULL)
	{//�t�@�C�����J������
		do
		{//"SCRIPT"�ƈ�v����܂ŉ�
			fscanf(pFile, "%s", &nData111[0]);
		} while (strcmp(&nData111[0], "SCRIPT") != 0);

		do
		{//"END_SCRIPT"�ƈ�v����܂ŉ�
			fscanf(pFile, "%s", &nData111[0]);

			if (strcmp(&nData111[0], "NUM_MODEL") == 0)
			{
				fscanf(pFile, "%s", &nData111[0]);
				fscanf(pFile, "%d", &g_nNumModel);

				for (int i = 0; i < g_nNumModel; i++, nCntModel++)
				{
					do
					{//"MODEL_FILENAME"�ƈ�v����܂ŉ�
						fscanf(pFile, "%s", &nData111[0]);
					} while (strcmp(&nData111[0], "MODEL_FILENAME") != 0);

					if (strcmp(&nData111[0], "MODEL_FILENAME") == 0)
					{
						fscanf(pFile, "%s", &nData111[0]);
						fscanf(pFile, "%s", &g_aModelPas[nCntModel][0]);
					}
				}
			}
			if (strcmp(&nData111[0], "CHARACTERSET") == 0)
			{
				do
				{//"END_CHARACTERSET"�ƈ�v����܂ŉ�
					fscanf(pFile, "%s", &nData111[0]);

					if (strcmp(&nData111[0], "NUM_PARTS") == 0)
					{
						fscanf(pFile, "%s", &nData111[0]);
						fscanf(pFile, "%d", &g_nNumParts);

						for (int i = 0; i < g_nNumParts; i++, nCntParts++)
						{
							do
							{//"PARTSSET"�ƈ�v����܂ŉ�
								fscanf(pFile, "%s", &nData111[0]);
							} while (strcmp(&nData111[0], "PARTSSET") != 0);

							if (strcmp(&nData111[0], "PARTSSET") == 0)
							{
								do
								{//"END_PARTSSET"�ƈ�v����܂ŉ�
									fscanf(pFile, "%s", &nData111[0]);

									if (strcmp(&nData111[0], "INDEX") == 0)
									{
										fscanf(pFile, "%s", &nData111[0]);
										fscanf(pFile, "%d", &nData);
										g_PartsSet[nCntParts].nIndex = nData;
									}
									if (strcmp(&nData111[0], "PARENT") == 0)
									{
										fscanf(pFile, "%s", &nData111[0]);
										fscanf(pFile, "%d", &nData);
										g_PartsSet[nCntParts].nParent = nData;
									}
									if (strcmp(&nData111[0], "POS") == 0)
									{
										fscanf(pFile, "%s", &nData111[0]);
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].pos.x = fData;
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].pos.y = fData;
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].pos.z = fData;
									}
									if (strcmp(&nData111[0], "ROT") == 0)
									{
										fscanf(pFile, "%s", &nData111[0]);
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].rot.x = fData;
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].rot.y = fData;
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].rot.z = fData;
									}
								} while (strcmp(&nData111[0], "END_PARTSSET") != 0);
							}
						}
					}
				} while (strcmp(&nData111[0], "END_CHARACTERSET") != 0);
			}
			if (strcmp(&nData111[0], "MOTIONSET") == 0)
			{
				do
				{//"END_MOTIONSET"�ƈ�v����܂ŉ�
					fscanf(pFile, "%s", &nData111[0]);

					if (strcmp(&nData111[0], "LOOP") == 0)
					{// "LOOP"�ƈ�v�����Ƃ�
						fscanf(pFile, "%s", &nData111[0]);		// "="
						fscanf(pFile, "%d", &g_MotionSet[g_MaxSetMotion][nCntKey].nLoop);	//���[�v
					}
					if (strcmp(&nData111[0], "NUM_KEY") == 0)
					{// "NUM_KEY"�ƈ�v�����Ƃ�
						fscanf(pFile, "%s", &nData111[0]);		// "="
						fscanf(pFile, "%d", &g_MotionSet[g_MaxSetMotion][nCntKey].nNumKey);		//�L�[��
					}
					if (strcmp(&nData111[0], "KEYSET") == 0)
					{// "KEYSET"�ƈ�v�����Ƃ�
						do
						{//"END_KEYSET"�ƈ�v����܂ŉ�
							fscanf(pFile, "%s", &nData111[0]);

							if (strcmp(&nData111[0], "FRAME") == 0)
							{// "FRAME"�ƈ�v�����Ƃ�
								fscanf(pFile, "%s", &nData111[0]);		// "="
								fscanf(pFile, "%d", &g_MotionSet[g_MaxSetMotion][nCntKey].nFrame);		//�t���[����

																										//�t���[���������v����
								nMaxFram[nCntKey] += g_MotionSet[g_MaxSetMotion][nCntKey].nFrame;
							}
							if (strcmp(&nData111[0], "KEY") == 0)
							{// "KEY"�ƈ�v�����Ƃ�
								do
								{//"END_KEY"�ƈ�v����܂ŉ�
									fscanf(pFile, "%s", &nData111[0]);

									if (strcmp(&nData111[0], "POS") == 0)
									{// "POS"�ƈ�v�����Ƃ�
										fscanf(pFile, "%s", &nData111[0]);		// "="
										fscanf(pFile, "%f", &fData);			// x���W
										g_MotionSet[g_MaxSetMotion][nCntKey].pos[nCntKeyParts].x = fData;
										fscanf(pFile, "%f", &fData);			// x���W
										g_MotionSet[g_MaxSetMotion][nCntKey].pos[nCntKeyParts].y = fData;
										fscanf(pFile, "%f", &fData);			// x���W
										g_MotionSet[g_MaxSetMotion][nCntKey].pos[nCntKeyParts].z = fData;
									}
									if (strcmp(&nData111[0], "ROT") == 0)
									{// "ROT"�ƈ�v�����Ƃ�
										fscanf(pFile, "%s", &nData111[0]);		// "="
										fscanf(pFile, "%f", &fData);			// x���W
										g_MotionSet[g_MaxSetMotion][nCntKey].rot[nCntKeyParts].x = fData;
										fscanf(pFile, "%f", &fData);			// x���W
										g_MotionSet[g_MaxSetMotion][nCntKey].rot[nCntKeyParts].y = fData;
										fscanf(pFile, "%f", &fData);			// x���W
										g_MotionSet[g_MaxSetMotion][nCntKey].rot[nCntKeyParts].z = fData;
									}
								} while (strcmp(&nData111[0], "END_KEY") != 0);

								//�p�[�c��+1
								nCntKeyParts++;
							}
						} while (strcmp(&nData111[0], "END_KEYSET") != 0);
						//�L�[���� +1 ����
						nCntKey++;
						nCntKeyParts = 0;
					}
				} while (strcmp(&nData111[0], "END_MOTIONSET") != 0);
				g_MaxSetMotion++;
				nCntKey = 0;
			}
		} while (strcmp(&nData111[0], "END_SCRIPT") != 0);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ

	}

	//�m�F�p
	//�t�@�C�����J��
	pFile = fopen("data\\teswt.txt", "w");		//(�e�L�X�g�����w��, ���[�h���w��)

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
	 //for (int i = 0; i < g_nNumParts; i++)
	 //{
	 //	fprintf(pFile, "%s\n", &g_aModelPas[i][0]);
	 //}

		for (int i = 0; i < nCntKey; i++)
		{
			for (int i2 = 0; i2 < g_nNumParts; i2++)
			{
				fprintf(pFile, "%f\n", g_MotionSet[g_MaxSetMotion][i].pos[i2].x, g_MotionSet[g_MaxSetMotion][i].pos[i2].y, g_MotionSet[g_MaxSetMotion][i].pos[i2].z);
				fprintf(pFile, "\n");	//���s
				fprintf(pFile, "%f�@%f�@%f", g_MotionSet[g_MaxSetMotion][i].rot[i2].x, g_MotionSet[g_MaxSetMotion][i].rot[i2].y, g_MotionSet[g_MaxSetMotion][i].rot[i2].z);
				fprintf(pFile, "\n\n");	//���s
			}
			fprintf(pFile, "\n\n");	//���s
		}
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("\n***�@�t�@�C�����J���܂���ł����@***\n");
	}
}

//---------------------------------------------------
//	�v���C���[�̏���������
//---------------------------------------------------
void InitPlayer(void)
{
	Load();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//�f�o�C�X�����擾

														//�p�[�c�̊e�l�̏�����
	for (int nCntParts = 0; nCntParts < g_nNumParts; nCntParts++)
	{
		g_Player.aModel[nCntParts].pos = g_PartsSet[nCntParts].pos;
		g_Player.aModel[nCntParts].rot = g_PartsSet[nCntParts].rot;
		g_Player.aModel[nCntParts].nIdxModelParent = g_PartsSet[nCntParts].nParent;
	}

	//�v���C���[�̊e�l�̏�����
	{
		g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���݂̈ʒu
		g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
		g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
		g_Player.diff = 0.0f;								//�����v�Z�p
		g_Player.rotDest = 0.0f;							//�ړI�̊p�x
		g_Player.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_�̍ŏ��l���擾�p
		g_Player.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_�̍ő�l���擾�p
		g_Player.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�T�C�Y�ۑ��p
	}

	//�e��ݒ�
	g_Player.IdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 0.1f, g_Player.pos.z), g_Player.rot);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\uroko_red.jpg",
		&g_pTexturePlayer);

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE * pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

						//�]�t�@�C���̓ǂݍ���
	for (int nCntParts = 0; nCntParts < g_nNumParts; nCntParts++)
	{
		D3DXLoadMeshFromX(&g_aModelPas[nCntParts][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aModel[nCntParts].pBuffMat,
			NULL,
			&g_Player.aModel[nCntParts].nNumMat,
			&g_Player.aModel[nCntParts].pMesh);
	}

	g_Player.vtxMin = D3DXVECTOR3(-30.0f, 0.0f, -30.0f);
	g_Player.vtxMax = D3DXVECTOR3(30.0f, 110.0f, 30.0f);

	g_Player.size.x = g_Player.vtxMax.x - g_Player.vtxMin.x;
	g_Player.size.y = g_Player.vtxMax.y - g_Player.vtxMin.y;
	g_Player.size.z = g_Player.vtxMax.z - g_Player.vtxMin.z;

	//����Ƀ��C��������
	/**/
	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//---------------------------------------------------
//	�v���C���[�̏I������
//---------------------------------------------------
void UninitPlayer(void)
{
	//�v���C���[�̃��b�V���j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//���f���̃��b�V���j��
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (g_Player.aModel[nCntParts].pMesh != NULL)
		{
			g_Player.aModel[nCntParts].pMesh->Release();
			g_Player.aModel[nCntParts].pMesh = NULL;
		}
	}

	//�v���C���[�̃}�e���A���j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}

	//���f���̃}�e���A���j��
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (g_Player.aModel[nCntParts].pBuffMat != NULL)
		{
			g_Player.aModel[nCntParts].pBuffMat->Release();
			g_Player.aModel[nCntParts].pBuffMat = NULL;
		}
	}

	//�e�N�X�`���j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//---------------------------------------------------
//	�v���C���[�̍X�V����
//---------------------------------------------------
void UpdatePlayer(void)
{
	//�d��
	g_Player.move.y -= 0.3f;

	//���݂̍��W��ۑ�
	g_Player.posOld = g_Player.pos;

	//�v���C���[�̈ړ�����
	MovePlayer();

	//�d�͂����Z
	g_Player.pos.y += g_Player.move.y;

	//���f���̓����蔻��
	CollisionModel(&g_Player.pos, &g_Player.posOld, g_Player.size, &g_Player.move);

	if (g_Player.pos.y <= 0.0f)
	{//���ɂ���Ƃ�
		g_Player.pos.y = 0.0f;
		g_Player.move.y = 0.0f;
	}

	//�v���C���[���ړ����Ă���ꍇ�A�G�t�F�N�g��t�^
	if (g_Player.pos != g_Player.posOld)
	{
		SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z), g_Player.rot, D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f), 40, D3DXVECTOR3(3.0f, 3.0f, 0.0f));
		SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z), g_Player.rot, D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f), 40, D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	}

	//�e�̈ʒu���X�V
	SetPositionShadow(0, D3DXVECTOR3(g_Player.pos.x, 0.1f, g_Player.pos.z));

	//MotionPlayer();		//���[�V�����ݒ�

	if (GetKeyboardTrigger(DIK_M) == true)
	{
		SetPlayer();		//���[�V�����؂�ւ�
	}
}

//---------------------------------------------------
//	�v���C���[�̃��[�V��������
//---------------------------------------------------
void MotionPlayer(void)
{
	if (GetKeyboardTrigger(DIK_9) == true)
	{
		if (nCntFrame < nMaxFram[nPlayMotion])
		{
			//rot(�p�x)
			for (int i = 0; i < g_nNumParts; i++)
			{// �p�[�c������
				MotionDiff[i].x = (g_MotionSet[nPlayMotion][nNextKeySet].rot[i].x - g_MotionSet[nPlayMotion][nNowKeySet].rot[i].x) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;
				MotionDiff[i].y = (g_MotionSet[nPlayMotion][nNextKeySet].rot[i].y - g_MotionSet[nPlayMotion][nNowKeySet].rot[i].y) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;
				MotionDiff[i].z = (g_MotionSet[nPlayMotion][nNextKeySet].rot[i].z - g_MotionSet[nPlayMotion][nNowKeySet].rot[i].z) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;

				g_Player.aModel[i].rot.x += (MotionDiff[i].x);
				g_Player.aModel[i].rot.y += (MotionDiff[i].y);
				g_Player.aModel[i].rot.z += (MotionDiff[i].z);
			}

			//pos(�ʒu)
			for (int i = 0; i < g_nNumParts; i++)
			{// �p�[�c������
				PosDiff[i].x = (g_MotionSet[nPlayMotion][nNextKeySet].pos[i].x - g_MotionSet[nPlayMotion][nNowKeySet].pos[i].x) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;
				PosDiff[i].y = (g_MotionSet[nPlayMotion][nNextKeySet].pos[i].y - g_MotionSet[nPlayMotion][nNowKeySet].pos[i].y) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;
				PosDiff[i].z = (g_MotionSet[nPlayMotion][nNextKeySet].pos[i].z - g_MotionSet[nPlayMotion][nNowKeySet].pos[i].z) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;

				g_Player.aModel[i].pos.x += (PosDiff[i].x);
				g_Player.aModel[i].pos.y += (PosDiff[i].y);
				g_Player.aModel[i].pos.z += (PosDiff[i].z);
			}

			if (nNowFrame >= g_MotionSet[nPlayMotion][nNowKeySet].nFrame)
			{// Frame���������
				nNowFrame = 0;		//�t���[������0(�����l)�ɖ߂�
				nNowKeySet++;		//���̃L�[�ɐi��
				nNextKeySet++;		//�Đ����̃L�[�̎��̃L�[�ɐi��

				if (nNextKeySet >= g_MotionSet[nPlayMotion][nPlayMotion].nNumKey)
				{
					nNextKeySet = 0;
				}
			}

			if (nNowKeySet >= g_MotionSet[nPlayMotion][0].nNumKey)
			{//�L�[���S���������

				nNowKeySet = 0;	//�ŏ��̃L�[�ɂ���
				nNextKeySet = nNowKeySet + 1;	//�ŏ��̃L�[�ɂ���
												//break;
			}

			//�t���[������1�i�߂�
			nNowFrame++;
			nCntFrame++;
		}
		else if (g_MotionSet[nPlayMotion][0].nLoop == 1)
		{
			nCntFrame = 0;
		}
	}
}

//---------------------------------------------------
//	���[�V�����؂�ւ�
//---------------------------------------------------
void SetPlayer()
{
	for (int i = 0; i < g_nNumParts; i++)
	{// �p�[�c������
	 //rot(�p�x)
		g_Player.aModel[i].rot.x = 0.0f;
		g_Player.aModel[i].rot.y = 0.0f;
		g_Player.aModel[i].rot.z = 0.0f;
		//pos(�ʒu)
		g_Player.aModel[i].pos.x = 0.0f;
		g_Player.aModel[i].pos.y = 0.0f;
		g_Player.aModel[i].pos.z = 0.0f;
	}
	nNowFrame = 0;
	nNowKeySet = 0;
	nNextKeySet = nNowKeySet + 1;
	nCntFrame = 0;

	nPlayMotion++;

	if (nPlayMotion >= g_MaxSetMotion)
	{
		nPlayMotion = 0;
	}
}

//---------------------------------------------------
//	�v���C���[�̈ړ�����
//---------------------------------------------------
void MovePlayer(void)
{
	Camera * pCamera = GetCamera();		//�J�����̏��擾

	if (GetKeyboardPress(DIK_UPARROW) == true)
	{//���L�[�������ꂽ�Ƃ�
		if (GetKeyboardPress(DIK_RIGHTARROW) == true)
		{//���L�[�Ɖ����ꂽ�Ƃ�(���΂ߏ����)
			g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4)) * PLAYER_SPEED;	//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4)) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 4 * 3.0f);
		}
		else if (GetKeyboardPress(DIK_LEFTARROW) == true)
		{//���L�[�Ɖ����ꂽ�Ƃ�(�E�΂ߏ����)
			g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4)) * PLAYER_SPEED;	//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4)) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 4 * 3.0f);
		}
		else
		{//���L�[�̂�(������ֈړ�)
			g_Player.pos.x += sinf(pCamera->rot.y) * PLAYER_SPEED;	//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_DOWNARROW) == true)
	{//���L�[�������ꂽ�Ƃ�
		if (GetKeyboardPress(DIK_RIGHTARROW) == true)
		{//���L�[�Ɖ����ꂽ�Ƃ�(���΂߉�����)
			g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;		//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 4);
		}
		else if (GetKeyboardPress(DIK_LEFTARROW) == true)
		{//���L�[�Ɖ����ꂽ�Ƃ�(�E�΂߉�����)
			g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;		//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 4);
		}
		else
		{//���L�[�̂�(�������ֈړ�)
			g_Player.pos.x += sinf(pCamera->rot.y + D3DX_PI) * PLAYER_SPEED;		//�v���C���[�̈ʒu�ړ�
			g_Player.pos.z += cosf(pCamera->rot.y + D3DX_PI) * PLAYER_SPEED;
			//�v���C���[�̖ړI�̌�����ݒ�
			g_Player.rotDest = pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHTARROW) == true)
	{//���L�[�������ꂽ�Ƃ�(�E�����ֈړ�)
		g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 2)) * PLAYER_SPEED;	//�v���C���[�̈ʒu�ړ�
		g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 2)) * PLAYER_SPEED;
		//�v���C���[�̖ړI�̌�����ݒ�
		g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 2);
	}
	else if (GetKeyboardPress(DIK_LEFTARROW) == true)
	{//���L�[�������ꂽ�Ƃ�(�������ֈړ�)
		g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 2)) * PLAYER_SPEED;	//�v���C���[�̈ʒu�ړ�
		g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 2)) * PLAYER_SPEED;
		//�v���C���[�̖ړI�̌�����ݒ�
		g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 2);
	}

	//�W�����v
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//�G���^�[�L�[�������ꂽ
		g_Player.move.y += 5.0f;
	}

	//�p�x�̐��K��
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2;
	}
	else if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2;
	}

	//�����̌v�Z
	g_Player.diff = (g_Player.rotDest - g_Player.rot.y);

	//�����̐��K��
	if (g_Player.diff > D3DX_PI)
	{
		g_Player.diff -= D3DX_PI * 2;
	}
	else if (g_Player.diff < -D3DX_PI)
	{
		g_Player.diff += D3DX_PI * 2;
	}

	//�v���C���[�̈ړ�����
	g_Player.rot.y += g_Player.diff * 0.1f;
}

//---------------------------------------------------
//	�v���C���[�̕`�揈��
//---------------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL * pMat;			//�}�e���A���f�[�^�ւ̃|�C���^

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld,
		&g_Player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		D3DXMATRIX mtxRotChild, mtxTransChild;	//�v�Z�p�}�g���b�N�X

		D3DXMatrixIdentity(&g_Player.aModel[nCntParts].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotChild,
			g_Player.aModel[nCntParts].rot.y, g_Player.aModel[nCntParts].rot.x, g_Player.aModel[nCntParts].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld,
			&g_Player.aModel[nCntParts].mtxWorld, &mtxRotChild);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransChild, g_Player.aModel[nCntParts].pos.x, g_Player.aModel[nCntParts].pos.y, g_Player.aModel[nCntParts].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld, &g_Player.aModel[nCntParts].mtxWorld, &mtxTransChild);

		D3DXMATRIX mtxParent;	//�e�̃}�g���N�X����p

		if (g_Player.aModel[nCntParts].nIdxModelParent == -1)
		{
			//�v���C���[�̃}�g���N�X���
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			//�����̐e���f���̃}�g���N�X���
			mtxParent = g_Player.aModel[g_Player.aModel[nCntParts].nIdxModelParent].mtxWorld;
		}

		//�����̐e���f���}�g���N�X�Ƃ̊|�Z�i�����̃}�g���N�X * �e�̃}�g���N�X = �����̃��[���h�}�g���N�X�j
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld,
			&g_Player.aModel[nCntParts].mtxWorld,		//�����̃}�g���N�X
			&mtxParent);								//�e�̃}�g���N�X

														//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntParts].mtxWorld);

		//���݂̃}�e���A���ێ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//X�t�@�C���̕`��
			g_Player.aModel[nCntParts].pMesh->DrawSubset(nCntMat);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//---------------------------------------------------
//	�v���C���[�̏��
//---------------------------------------------------
Player * GetPlayer(void)
{//�v���C���[�̏��𑗂�
	return &g_Player;
}


////=======================================
////����������
////=======================================
//
//void InitModel2(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	g_aModel2[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	g_aModel2[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	g_aModel2[0].rotDestModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	g_aModel2[0].vtxMaxModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���_�̍ő�l�擾
//	g_aModel2[0].vtxMinModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���_�̍ŏ��l�擾
//	g_aModel2[0].bUse = false;
//	g_aModel2[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	//Xfile �ǂݍ���
//	D3DXLoadMeshFromX("data//MODEL//3DGame_bus.x",
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&g_pBuffMatModel2,
//		NULL,
//		&g_nNumMatModel2,
//		&g_pMeshModel2);
//
//	int nNumVtx;     //���_��
//	DWORD sizeFVF;   //���_�t�H�[�}�b�g�̃T�C�Y
//	BYTE*pVtxBuff;   //���_�o�b�t�@�ւ̃|�C���^
//					 //���_���̎擾
//	nNumVtx = g_pMeshModel2->GetNumVertices();
//
//	//���_�t�H�[�}�b�g�̃T�C�Y���擾
//	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel2->GetFVF());
//
//	//���_�o�b�t�@�̃��b�N
//	g_pMeshModel2->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
//	{
//		for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
//		{
//			//���_���W�̑��
//			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
//
//			// �ŏ��l�v�Z
//			if (vtx.x < g_aModel2[nCntModel].vtxMinModel.x)
//			{// ��r�����l�������Ă铖�������������������u��������
//				g_aModel2[nCntModel].vtxMinModel.x = (int)vtx.x;
//			}
//
//			if (vtx.z < g_aModel2[nCntModel].vtxMinModel.z)
//			{// ��r�����l�������Ă铖�������������������u��������
//				g_aModel2[nCntModel].vtxMinModel.z = (int)vtx.z;
//			}
//
//			// �ő�l���v�Z
//			if (vtx.x > g_aModel2[nCntModel].vtxMaxModel.x)
//			{// ��r�����l�������Ă铖��������傫��������u��������
//				g_aModel2[nCntModel].vtxMaxModel.x = (int)vtx.x;
//			}
//
//			if (vtx.z > g_aModel2[nCntModel].vtxMaxModel.z)
//			{// ��r�����l�������Ă铖��������傫��������u��������
//				g_aModel2[nCntModel].vtxMaxModel.z = (int)vtx.z;
//			}
//		}
//
//		//���_�t�H�[�}�b�g�̃|�C���^���i�߂�
//		pVtxBuff += sizeFVF;
//	}
//
//	//���_�o�b�t�@���A�����b�N
//	g_pMeshModel2->UnlockVertexBuffer();
//	SetModel2(D3DXVECTOR3(0.0f, 0.0f,250.0f), D3DXVECTOR3(0.0f, -D3DX_PI/2, 0.0f), MODEL_TYPE_BUS);
//	/*SetModel2(D3DXVECTOR3(0.0f, 0.0f, 230.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_TYPE_BUS);*/
//}
////=======================================
////�I������
////======================================= 
//void UninitModel2(void)
//{
//	//���b�V���j��
//	if (g_pMeshModel2 != NULL)
//	{
//		g_pMeshModel2->Release();
//		g_pMeshModel2 = NULL;
//	}
//	//�}�e���A���̔j��
//	if (g_pBuffMatModel2 != NULL)
//	{
//		g_pBuffMatModel2->Release();
//		g_pBuffMatModel2 = NULL;
//	}
//}
////=======================================
////�X�V����
////=======================================    
//void UpdateModel2(void)
//{	//�ʒu���X�V
//	g_aModel2[0].pos.x += g_aModel2[0].move.x;
//
//	g_aModel2[0].move.x = +2;
//	if (g_aModel2[0].pos.x == 700)
//	{
//		g_aModel2[0].pos.x = -470;
//	}
//
//}
////=======================================
////�`��̏���
////=======================================       
//void DrawModel2(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̎擾
//	D3DXMATRIX mtxRot, mtxTrans, scale;     //�v�Z�p�}�g���b�N�X
//
//	D3DMATERIAL9 matDef;                  //���݂̃}�e���A���ۑ��p
//	D3DXMATERIAL *pMat;                  //�}�e���A���f�[�^�ւ̃|�C���^
//	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
//	{
//		if (g_aModel2[nCnt].bUse == true)
//		{
//			//���[���h�}�g���b�N�X�̏�����
//			D3DXMatrixIdentity(&g_aModel2[nCnt].mtxWorld);
//
//			//���f���̃T�C�Y
//			D3DXMatrixScaling(&scale,
//				scaleVector2.x,
//				scaleVector2.y,
//				scaleVector2.z);
//			D3DXMatrixMultiply(&g_aModel2[nCnt].mtxWorld, &g_aModel2[nCnt].mtxWorld, &scale);
//
//			//�����𔽉f
//			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel2[nCnt].rot.y, g_aModel2[nCnt].rot.x, g_aModel2[nCnt].rot.z);
//			D3DXMatrixMultiply(&g_aModel2[nCnt].mtxWorld, &g_aModel2[nCnt].mtxWorld, &mtxRot);
//
//			////�ʒu�𔽉f
//			D3DXMatrixTranslation(&mtxTrans, g_aModel2[nCnt].pos.x, g_aModel2[nCnt].pos.y, g_aModel2[nCnt].pos.z);
//			D3DXMatrixMultiply(&g_aModel2[nCnt].mtxWorld, &g_aModel2[nCnt].mtxWorld, &mtxTrans);
//
//			//���[���h�}�g���b�N�X�̐ݒ�
//			pDevice->SetTransform(D3DTS_WORLD, &g_aModel2[nCnt].mtxWorld);
//
//			//���݂̃}�e���A����ۓ�
//			pDevice->GetMaterial(&matDef);
//
//			//�}�e���A���f�[�^�ւ̃|�C���^���擾
//			pMat = (D3DXMATERIAL*)g_pBuffMatModel2->GetBufferPointer();
//
//			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel2; nCntMat++)
//			{
//				//�}�e���A���̐ݒ�
//				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//				//���f���p�[�c�̕`��
//				g_pMeshModel2->DrawSubset(nCntMat);
//			}
//			// �ۓ����Ă����}�e���A����߂�
//			pDevice->SetMaterial(&matDef);
//		}
//	}
//
//}
//void SetModel2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL_TYPE2 type)
//{
//
//	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
//	{
//		//bUse ��false�̏ꍇ, pos,rot������bUse��true�ɂ���
//		if (g_aModel2[nCntModel].bUse == false)
//		{
//			g_aModel2[nCntModel].pos = pos;
//			g_aModel2[nCntModel].rot = rot;
//			g_aModel2[nCntModel].bUse = true;
//
//			break;
//		}
//	}
//}
//
////-------------------------------------------
////���f���̓����蔻��
////-------------------------------------------
//void CollisionModel2(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size)
//{
//	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
//	{
//		if (g_aModel2[nCntModel].bUse == true)
//		{
//			if (pos->z - (size.z / 2) < g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMaxModel.z*SIZE_Z &&
//				pos->z + (size.z / 2) > g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMinModel.z*SIZE_Z)
//			{ //������(x)
//				if (posOld->x + (size.x / 2.f) <= g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMinModel.x*SIZE_X &&
//					pos->x + (size.x / 2.f) > g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMinModel.x*SIZE_X)
//				{
//
//					pos->x = g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMinModel.x*SIZE_X - (size.x / 2.f);
//				}
//				//�E����(x)
//				else if (posOld->x - (size.x / 2) >= g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMaxModel.x*SIZE_X &&
//					pos->x - (size.x / 2) < g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMaxModel.x*SIZE_X)
//				{
//					pos->x = g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMaxModel.x*SIZE_X + (size.x / 2.f);
//				}
//			}
//			if (pos->x - (size.x / 2) < g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMaxModel.x*SIZE_X &&
//				pos->x + (size.x / 2) > g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMinModel.x*SIZE_X)
//			{ // ��(z)
//
//				if (posOld->z + (size.z / 2) <= g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMinModel.z*SIZE_Z &&
//					pos->z + (size.z / 2) >  g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMinModel.z*SIZE_Z)
//				{
//					pos->z = g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMinModel.z*SIZE_Z - (size.z / 2);
//				}
//
//				// ��(z)
//				else if (posOld->z - (size.z / 2) >= g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMaxModel.z*SIZE_Z &&
//					pos->z - (size.z / 2) <  g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMaxModel.z*SIZE_Z)
//				{
//					pos->z = g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMaxModel.z*SIZE_Z + (size.z / 2);
//				}
//			}
//		}
//	}
//}
//
//MODEL2*GetModel2(void)
//{
//	return g_aModel2;
//}