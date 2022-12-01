//=============================================================================
//
// X�t�@�C���}�l�[�W���[ [x_file.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include <stdio.h>

#include "x_file.h"
#include "renderer.h"
#include "manager.h"

//================================================
// �}�N����`
//================================================
#define MAX_CHAR		(128)		// �ő�ǂݎ�蕶����

//================================================
// �ÓI�����o�ϐ��錾
//================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXFile::CXFile()
{
	// �ϐ��̏�����
	m_texType.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CXFile::~CXFile()
{
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CXFile::Init()
{
	//�t�@�C���ǂݍ���
	FILE *pFile = fopen("data/TEXT/XFilePas.txt", "r");

	if (pFile != NULL)
	{
		char cString[MAX_CHAR];

		//��s���ۑ�
		while (fgets(cString, MAX_CHAR, pFile) != NULL)
		{
			//�������ۑ�
			fscanf(pFile, "%s", cString);
			//������̒���TEX_NUM����������
			if (strncmp("XFILE_NUM", cString, 8) == 0)
			{
				//�e�N�X�`���ő吔�ǂݍ���
				fscanf(pFile, "%*s%d", &m_nNumXFile);

				int nNum = 0;
				//��s���ۑ�
				while (fgets(cString, MAX_CHAR, pFile) != NULL)
				{
					//�������ۑ�
					fscanf(pFile, "%s", cString);
					//������̒���PAS����������
					if (strncmp("PAS", cString, 4) == 0)
					{
						//�p�X�̎擾
						fscanf(pFile, "%*s%s", &cString[0]);
						m_aPas.push_back(&cString[0]);

						//���O�̎擾
						fscanf(pFile, "%*s%*s%s", cString);
						//���O�Ɛ��̊��蓖��
						m_texType[cString] = nNum;
						nNum++;
					}
				}
			}
			else if (strncmp("END_SCRIPT", cString, 11) == 0)
			{//�e�L�X�g�t�@�C����ǂݐ؂�����
				break;
			}
		}
	}
	else
	{
		printf("�e�N�X�`���t�@�C�����J���܂���ł���\n");
	}

	// �t�@�C�������
	fclose(pFile);

	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	for (int nCntXFile = 0; nCntXFile < m_nNumXFile; nCntXFile++)
	{
		// �e�N�X�`���ۑ��p
		SModelInfo XFile;

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_aPas[nCntXFile].c_str(),
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&XFile.pBuffMat,
			NULL,
			&XFile.nNumMat,
			&XFile.pMesh);

		// �e�N�X�`���̓ǂݍ��ݏ���
		LoadXFileTexture(XFile);

		// X�t�@�C�����̕ۑ�
		m_aXFile.push_back(XFile);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CXFile::Uninit()
{
	for (int nCnt = 0; nCnt < m_nNumXFile; nCnt++)
	{
		//���b�V���̔j��
		if (m_aXFile[nCnt].pMesh != NULL)
		{
			m_aXFile[nCnt].pMesh->Release();
			m_aXFile[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (m_aXFile[nCnt].pBuffMat != NULL)
		{
			m_aXFile[nCnt].pBuffMat->Release();
			m_aXFile[nCnt].pBuffMat = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �e�N�X�`���ǂݍ���
//-----------------------------------------------------------------------------
void CXFile::LoadXFileTexture(SModelInfo& XFile)
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)XFile.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)XFile.nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`�����������ꍇ
		if ((pMat[nCntMat].pTextureFilename != NULL) && (strcmp(pMat[nCntMat].pTextureFilename, "") != 0))
		{//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &XFile.pTexture[nCntMat]);
		}
	}
}
