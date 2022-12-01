//-----------------------------------------------------------------------------------------------
//
// ��Q������[model_obstacle.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"

#include "load.h"
#include "sound.h"

#include "game.h"
#include "library.h"
#include "effect.h"
#include "logo.h"
#include "score.h"
#include "fade_scene.h"

#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "logo.h"

// �ǉ�
#include "x_file.h"
#include "model_obstacle.h"

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CObstacle::CObstacle() :m_PosOld(0.0f, 0.0f, 0.0f)
{
	//�I�u�W�F�N�g�̎�ސݒ�
	SetType(EObject::OBJ_OBSTACLE);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CObstacle::~CObstacle()
{
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CObstacle *CObstacle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name)
{
	// �|�C���^�N���X��錾
	CObstacle* pObstacle = new CObstacle;

	if (pObstacle != nullptr)
	{
		// �ʒu�ݒ�
		pObstacle->SetPosition(pos);
		// �p�x�ݒ�
		pObstacle->SetRotation(rot);
		// X�t�@�C���̐ݒ�
		pObstacle->BindXFile(CManager::GetManager()->GetXFile()->GetXFile(name));
		// ������
		pObstacle->Init();
	}

	return pObstacle;
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CObstacle::Init()
{
	// ������
	CModel::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CObstacle::Uninit()
{
	CModel::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CObstacle::Update()
{
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CObstacle::Draw()
{
	//�`�揈��
	CModel::Draw();
}

//-----------------------------------------------------------------------------------------------
// �S�Ă̏�Q���̓����蔻��
//-----------------------------------------------------------------------------------------------
void CObstacle::CollisionAll(D3DXVECTOR3* pPosIn, int nNumPlayer)
{
	for (int nCntObject = 0; nCntObject < CObject::MAX_OBJECT; nCntObject++)
	{
		// �I�u�W�F�N�g�̃|�C���^�擾
		CObject *pObject = CObject::GetObject(nCntObject);

		if (pObject != nullptr)
		{
			// �I�u�W�F�N�g�̎�ގ擾
			CObject::EObject objType = pObject->GetObjType();

			//�v���C���[�̒e�ƓG�̔���
			if (objType == OBJ_OBSTACLE)
			{
				//�I�u�W�F�N�g�|�C���^���L���X�g
				CObstacle *pObstacle = (CObstacle*)pObject;

				// �����蔻��
				pObstacle->Collision(pPosIn, nNumPlayer);
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// �����蔻��
//-----------------------------------------------------------------------------------------------
bool CObstacle::Collision(D3DXVECTOR3* pPosPlayer, int nNumPlayer)
{
	bool bPush = false;

	// �v���C���[���̎擾
	CPlayer *pPlayer = CManager::GetManager()->GetGame()->GetPlayer(nNumPlayer);

	if (pPlayer != nullptr)
	{
		// �v���C���[�̉ߋ��̈ʒu�擾
		D3DXVECTOR3 posPlayerOld = pPlayer->GetPositionOld();
		// �v���C���[�̃T�C�Y�擾
		D3DXVECTOR3 sizePlayer = pPlayer->GetSizeMax();

		// �ʒu�擾
		D3DXVECTOR3 pos = GetPosition();
		//�T�C�Y�擾
		D3DXVECTOR3 size = GetSizeMax();

		// �����o������
		switch (LibrarySpace::BoxCollisionUnder3D(pPosPlayer, &posPlayerOld, &pos, &sizePlayer, &size))
		{
		case LibrarySpace::PUSH_X:
			pPlayer->SetMoveX(0.0f);
			break;

		case LibrarySpace::PUSH_Z:
			pPlayer->SetMoveZ(0.0f);
			break;

		case LibrarySpace::PUSH_Y:
			pPlayer->SetMoveY(0.0f);
			break;

		case LibrarySpace::PUSH_JUMP:
			pPlayer->SetMoveY(0.0f);
			pPlayer->SetJumping(false);
			break;

		default:
			break;
		}
	}

	return bPush;	//�������ĂȂ�
}