//===================================================================
//
//	���f������[motion.cpp]
//	Author:SHUGO KURODA
//
//===================================================================

//======================================================
//	�C���N���[�h
//======================================================
#include "manager.h"
#include "renderer.h"
#include "motion.h"

#include "input.h"
#include "camera.h"
//#include "shadow.h"
#include "bullet.h"
#include "load.h"
#include "enemy.h"

// �ǉ�
#include "x_file_motion.h"

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CMotion::CMotion() :m_pos(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f), m_vtxMax(0.0f, 0.0f, 0.0f), m_vtxMin(0.0f, 0.0f, 0.0f)
{
	//������
	memset(&m_animIdx, 0, sizeof(AnimIdx));
	
	//���[�V�������̏�����
	//memset(&m_motion, 0, sizeof(ModelMotion));
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CMotion::~CMotion()
{
}

//-----------------------------------------------------------------------------
// ����
// const D3DXVECTOR3& pos �� ��������ʒu
// const D3DXVECTOR3& rot �� ��������p�x
// const char* name �� �������閼�O(���)
//-----------------------------------------------------------------------------
CMotion* CMotion::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name)
{
	// �C���X�^���X����
	CMotion *pMotion = new CMotion;

	// �ʒu�ݒ�
	pMotion->SetPosition(pos);

	// �p�x�ݒ�
	pMotion->SetRotation(rot);

	// ���[�V�������̊��蓖��
	pMotion->BindMotion(CManager::GetManager()->GetMotion()->GetMotion(name));

	// ������
	pMotion->Init();

	return pMotion;
}

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
HRESULT CMotion::Init()
{
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------
void CMotion::Uninit()
{
	Release();
}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void CMotion::Update()
{
	//for (int nCntVtx = 0; nCntVtx < MAX_MODEL_TYPE; nCntVtx++)
	//{
	//	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	//	{
	//		//�O��̈ʒu��ۑ�
	//		g_aModel[nCnt].posOld = g_aModel[nCnt].pos;

	//		//�����蔻��
	//		//CollisionPlayer(&g_aModel[nCnt].pos, &g_aModel[nCnt].posOld, &g_aModel[nCnt].Airmove, g_aModel[nCnt].fWidth, g_aModel[nCnt].fHeight);
	//	}
	//}
}

//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
void CMotion::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxWorldParent;		//�e�̃��[���h�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏������i�e�j
	D3DXMatrixIdentity(&mtxWorldParent);

	//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&mtxWorldParent, &mtxWorldParent, &mtxRot);

	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&mtxWorldParent, &mtxWorldParent, &mtxTrans);

	//switch (g_Player.Weapon)
	//{
	//case PLAYERWEAPON_GUN:			//�v���C���[���e���������Ă���ꍇ
	//								//���̕`�����߁A�e��`�悷��
	//	g_Player.aParts[15].bUse = false;
	//	g_Player.aParts[16].bUse = true;
	//	break;
	//case PLAYERWEAPON_SWORD:		//�v���C���[�������������Ă���ꍇ
	//								//�e�̕`�����߁A����`�悷��
	//	g_Player.aParts[15].bUse = true;
	//	g_Player.aParts[16].bUse = false;
	//	break;
	//}

	for (int nCntParts = 0; nCntParts < m_motion.nNumParts; nCntParts++)
	{
		D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
		D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

		//���[���h�}�g���b�N�X�̏������i�q�j
		D3DXMatrixIdentity(&m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			m_motion.aParts[nCntParts].rot.y, m_motion.aParts[nCntParts].rot.x, m_motion.aParts[nCntParts].rot.z);

		D3DXMatrixMultiply(&m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			m_motion.aParts[nCntParts].pos.x, m_motion.aParts[nCntParts].pos.y, m_motion.aParts[nCntParts].pos.z);

		D3DXMatrixMultiply(&m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &mtxTrans);

		//�����̐e���f���̃}�g���b�N�X�Ƃ̊|���Z
		if (m_motion.aParts[nCntParts].nParent < 0)
		{
			//���f���̃}�g���b�N�X �� �e�̃��[���h�}�g���b�N�X
			D3DXMatrixMultiply(&m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &mtxWorldParent);
		}
		else
		{
			//���f���̃}�g���b�N�X �� �e�̃��[���h�}�g���b�N�X
			D3DXMatrixMultiply(&m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld, &m_motion.aParts[m_motion.aParts[nCntParts].nParent].mtxWorld);
		}

		if (m_motion.aParts[m_motion.aParts[nCntParts].nIndex].xFile.pMesh == NULL)
		{//�p�[�c�̃��f����NULL��������
			continue;		//for���̍ŏ��ɖ߂�
		}

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_motion.aParts[m_motion.aParts[nCntParts].nIndex].mtxWorld);

		//���݂̃}�e���A����ێ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_motion.aParts[m_motion.aParts[nCntParts].nIndex].xFile.pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_motion.aParts[m_motion.aParts[nCntParts].nIndex].xFile.nNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//���f���p�[�c�̕`��
			m_motion.aParts[m_motion.aParts[nCntParts].nIndex].xFile.pMesh->DrawSubset(nCntMat);
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//-----------------------------------------------------------------------------
// ���[�V�����Đ�
//-----------------------------------------------------------------------------
void CMotion::Motion()
{
	int nMotion = m_animIdx.nMotionIdx;
	int nKey = m_animIdx.nKeySetIdx;
	int nFrame = m_motion.aMotion[nMotion].aKeyInfo[nKey].nFrame;
	int nNumKey = m_motion.aMotion[nMotion].nNumKey;

	if (nFrame <= 0)
	{//�e�L�X�g�Őݒ肳�ꂽ�t���[������0�ȉ��������ꍇ
		nFrame = 1;
	}

	//���[�V�����Đ�����
	for (int nCntParts = 0; nCntParts < m_motion.nNumParts; nCntParts++)
	{
		//�ʒu�X�V�i���[�J�����W�j
		m_motion.aParts[nCntParts].pos += (m_motion.aMotion[nMotion].aKeyInfo[nKey].aKey[nCntParts].pos - m_motion.aMotion[nMotion].aKeyInfo[((nKey - 1) + nNumKey) % nNumKey].aKey[nCntParts].pos) / (float)m_motion.aMotion[nMotion].aKeyInfo[nKey].nFrame;

		//�p�x�X�V
		m_motion.aParts[nCntParts].rot += (m_motion.aMotion[nMotion].aKeyInfo[nKey].aKey[nCntParts].rot - m_motion.aMotion[nMotion].aKeyInfo[((nKey - 1) + nNumKey) % nNumKey].aKey[nCntParts].rot) / (float)m_motion.aMotion[nMotion].aKeyInfo[nKey].nFrame;
	}

	//�t���[���̉��Z
	m_animIdx.nFrame++;

	if (m_motion.aMotion[nMotion].aKeyInfo[nKey].nFrame <= m_animIdx.nFrame)
	{//�t���[�������ݒ�̒l�𒴂�����

		// ���[�V�����ύX
		Change(nMotion, nKey);

		//�Đ����̃L�[���̉��Z
		m_animIdx.nKeySetIdx++;

		//�t���[���̏�����
		m_animIdx.nFrame = 0;

		if (m_motion.aMotion[nMotion].nNumKey <= m_animIdx.nKeySetIdx)
		{//�Đ����̃L�[�����ݒ�̒l�𒴂�����
			if (m_motion.aMotion[nMotion].nLoop == 1)
			{
				m_animIdx.nKeySetIdx = 0;
			}
			else
			{//���ݍĐ����̃��[�V��������j���[�g�������[�V�����ɕύX
				m_animIdx.nKeySetIdx = 0;
				m_animIdx.nMotionIdx = 0;
			}
		}
	}
}

//-----------------------------------------------------------------------------
// ���[�V�����Đ�
//-----------------------------------------------------------------------------
void CMotion::Change(int nMotion, int nKey)
{
	for (int nCntParts = 0; nCntParts < m_motion.nNumParts; nCntParts++)
	{
		//m_motion.aParts[nCntParts].pos = m_motion.aMotion[nMotion].aKeyInfo[nKey].aKey[nCntParts].pos;
		m_motion.aParts[nCntParts].rot = m_motion.aMotion[nMotion].aKeyInfo[nKey].aKey[nCntParts].rot;
	}
}
