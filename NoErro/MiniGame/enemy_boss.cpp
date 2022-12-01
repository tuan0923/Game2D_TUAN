//-----------------------------------------------------------------------------------------------
//
// �G�{�X�̏���[enemy_boss.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "enemy_boss.h"
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

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// �̗�
const int CEnemyBoss::LIFE = 2000;
// ��
const float CEnemyBoss::SIZE_WIDTH = 300.0f;
// ����
const float CEnemyBoss::SIZE_HEIGHT = 270.0f;
// U���W�̍ő啪����
const int CEnemyBoss::DIVISION_U = 4;
// V���W�̍ő啪����
const int CEnemyBoss::DIVISION_V = 1;
// �U���O�̗\������Ԋu
const int CEnemyBoss::RUSH_OPERATION = 60;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemyBoss::CEnemyBoss() :m_pattern(PATTERN_ENTRY), m_nCounter(0), m_fAttackRot(0.0f), m_bSizeChange(false),
						m_nCountObject(0), m_PosOld(0.0f, 0.0f, 0.0f)
{
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemyBoss::~CEnemyBoss()
{
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CEnemyBoss *CEnemyBoss::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name)
{
	// �|�C���^�N���X��錾
	CEnemyBoss* pEnemy = new CEnemyBoss;

	if (pEnemy != nullptr)
	{
		//�ʒu�ݒ�
		pEnemy->SetPosition(pos);
		// �p�x�ݒ�
		pEnemy->SetRotation(rot);
		// X�t�@�C���̐ݒ�
		pEnemy->BindXFile(CManager::GetManager()->GetXFile()->GetXFile(name));
		// ������
		pEnemy->Init();
	}

	return pEnemy;
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CEnemyBoss::Init()
{
	// ��ނ�ݒ�
	SetType(EObject::OBJ_ENEMYBOSS);
	// ������
	CModel::Init();

	// �U���O�̗\������Ԋu��ݒ�
	m_nCountOperation = RUSH_OPERATION;

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CEnemyBoss::Uninit()
{
	CModel::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CEnemyBoss::Update()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CModel::GetPosition();
	// 
	//// �T�C�Y�̎擾
	//D3DXVECTOR2 size = CEnemy::GetSize();
	//// �ړ��ʂ̎擾
	//D3DXVECTOR3 move = CEnemy::GetMove();

	//// �s���p�^�[���Ǘ�
	//if (Pattern(pos, size, move) == true)
	//{// �j�����ꂽ�ꍇ
	//	return;
	//}

	//// �{�X�̎��S�t���O�擾
	//bool bDie = CGame::GetDieBoss();

	//if (GetLife() <= 0 && bDie == false)
	//{// ���C�t��0

	//	// �ϐ��̃��Z�b�g
	//	StateReset();

	//	//���S�A�j���[�V�������Đ�����
	//	m_pattern = PATTERN_DIE;
	//}

	//// ���S���Ă��Ȃ����
	//if (bDie == false)
	//{

	// �e�s��
	Pattern(pos);
	
	//�����蔻��
	Collision(pos);

	//�ʒu���X�V
	CModel::SetPosition(pos);

	//}

	////�ړ��ʍX�V
	//CEnemy::SetMove(move);
	////�A�j���[�V��������
	//SetAnim();
	////��ԊǗ�
	//State();
	//// �ʒu�̍X�V
	//CObject2D::SetPosition(pos);
	//// �T�C�Y�̍X�V
	//CObject2D::SetSize(size);
	////���_���W�̐ݒ�
	//CObject2D::SetVertex();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CEnemyBoss::Draw()
{
	//�`�揈��
	CModel::Draw();
}

//-----------------------------------------------------------------------------------------------
// �����蔻��
//-----------------------------------------------------------------------------------------------
bool CEnemyBoss::Collision(D3DXVECTOR3 posStart)
{
	//�T�C�Y�擾
	float fLength = GetSizeMax().x;

	// �v���C���[����
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		//�v���C���[���̎擾
		CPlayer *pPlayer = CManager::GetManager()->GetGame()->GetPlayer(nCntPlayer);

		if (pPlayer != nullptr)
		{
			// �v���C���[���ʏ��Ԃ�������
			if (pPlayer->GetState() == CPlayer::STATE_NORMAL)
			{
				// �v���C���[���W�̎擾
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

				//�G�Ɠ���������(���̂̓����蔻��)
				if (LibrarySpace::CylinderCollision3D(posStart, posPlayer, fLength, pPlayer->GetSizeMax().x))
				{//�_���[�W����
					pPlayer->Damage();
					return true;	//��������
				}
			}
		}
	}

	return false;	//�������ĂȂ�
}

//-----------------------------------------------------------------------------------------------
// �_���[�W����
//-----------------------------------------------------------------------------------------------
void CEnemyBoss::Damage(int nDamage, CPlayer* pPlayer)
{
	//// �{�X�̎��S�t���O�擾
	//bool bDie = CGame::GetDieBoss();

	//// �{�X�����S���Ă��Ȃ����
	//if (bDie == false)
	//{
	//	CEnemy::Damage(nDamage, pPlayer);
	//}
}

//-----------------------------------------------------------------------------------------------
// ���
//-----------------------------------------------------------------------------------------------
void CEnemyBoss::State()
{
	//CEnemy::State();
}

//-----------------------------------------------------------------------------------------------
// �G���ƂɃA�j���[�V����,������ݒ�
//-----------------------------------------------------------------------------------------------
void CEnemyBoss::SetAnim()
{
	//switch (GetType())
	//{
	//case CEnemy::TYPE_RING_BOSS:

	//	break;

	//case CEnemy::TYPE_DARK_BOSS:

	//	break;

	//default:
	//	break;
	//}
}
//-----------------------------------------------------------------------------------------------
// �s���p�^�[���Ǘ�
//-----------------------------------------------------------------------------------------------
bool CEnemyBoss::Pattern(D3DXVECTOR3& pos)
{
	//�G���G�������̎擾
	//ParentEnemyInfo *pBossInfo = LoadSpace::GetParentEnemy();

	switch (m_pattern)
	{
		//=================================
		// �o��
		//=================================
	case CEnemyBoss::PATTERN_ENTRY:
		//pos += D3DXVECTOR3(-0.5f, -2.0f, 0.0f);

		//if (pos.y <= 250.0f)
		//{
		//	m_pattern = PATTERN_NORMAL;
		//}

		////�g�k������
		//ChangeSize(&size, 0.5f);
		break;

		//=================================
		// �ʏ�
		//=================================
	case CEnemyBoss::PATTERN_NORMAL:

		pos.z -= 1.0f;

		////�ړ��ʂ̉��Z
		//move += D3DXVECTOR3(0.1f, 0.05f, 0.0f);

		//// �ړ��ʂ̍X�V
		//pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH - 200.0f) - sinf(move.x) * 100,
		//	(CRenderer::SCREEN_HEIGHT / 2) - cosf(move.y) * 100,
		//	0.0f);

		////���̍s���Ɉڂ��܂ł̃J�E���^�[���Z
		//m_nCounter++;

		//if (m_nCounter >= 300)
		//{
		//	//�J�E���^�[���Z�b�g
		//	m_nCounter = 0;
		//	//���̍s���������_���Ō��߂�
		//	m_pattern = (PATTERN)LibrarySpace::GetRandNum(PATTERN_BARRAGE, PATTERN_RUSH);
		//}

		////�g�k������
		//ChangeSize(&size, 0.5f);

		break;

		//=================================
		// �A���ːi�U��
		//=================================
	//case CEnemyBoss::PATTERN_RUSH:

	//	if (m_nCountOperation <= 0)
	//	{
	//		m_nCountOperation--;

	//		// ��ʂ̒��S���W��ۑ�
	//		D3DXVECTOR2 ScreenCenter = D3DXVECTOR2(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2);

	//		if (m_nCounter >= 5)
	//		{
	//			//�ʒu�̕ۑ�
	//			D3DXVECTOR3 vec = m_PosOld - pos;
	//			//�G����v���C���[�ւ̃x�N�g��(�ړ���)�ɕϊ�����
	//			D3DXVec3Normalize(&vec, &vec);
	//			//�ړ��ʂɔ{�����|����
	//			vec.x *= 4.0f;
	//			vec.y *= 4.0f;
	//			//�ړ��ʂ̉��Z
	//			pos += vec;

	//			//�O��̈ʒu�Ɉړ����I������
	//			if (pos.x <= m_PosOld.x)
	//			{
	//				// �ʏ��Ԃɖ߂�(�ϐ��̃��Z�b�g)
	//				StateReset();
	//			}
	//		}
	//		else if (m_nCountOperation == -120)
	//		{
	//			// �ːi����p�x�����߂�
	//			m_fAttackRot = LibrarySpace::GetRandFloat(3, 0, 100);

	//			// �x����
	//			CSound::Play(CSound::SOUND_LABEL_SE_WARNING2);

	//			// �G�̗\���O���͈̓��S
	//			CLogo::Create(D3DXVECTOR3(ScreenCenter.x, ScreenCenter.y, 0.0f), D3DXVECTOR2(ScreenCenter.x * 2.5f, SIZE_HEIGHT),
	//				D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f), m_fAttackRot, CLogo::TYPE_NONE, CLogo::ANIM_NONE, 60);

	//			// ���ӊ��N�W���̃��S
	//			CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(200.0f, 200.0f),
	//				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_REMINDER, CLogo::ANIM_FLASHING, 60);

	//			pos = D3DXVECTOR3(ScreenCenter.x, ScreenCenter.y, 0.0f);
	//			float fLenght = sqrtf((ScreenCenter.x * ScreenCenter.x) + (ScreenCenter.y * ScreenCenter.y));
	//			pos += D3DXVECTOR3(cosf(m_fAttackRot) * (fLenght + SIZE_WIDTH), -sinf(m_fAttackRot) * (fLenght + SIZE_HEIGHT), 0);
	//		}
	//		else if (m_nCountOperation <= -180)
	//		{
	//			if (m_nCountOperation == -180)
	//			{
	//				// �ːi��
	//				CSound::Play(CSound::SOUND_LABEL_SE_RUSH);

	//				// �x�����̃X�g�b�v
	//				CSound::Stop(CSound::SOUND_LABEL_SE_WARNING2);
	//			}

	//			// �G�t�F�N�g����
	//			CEffect::Create(pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT), CEffect::TYPE_AFTERIMAGE, CEffect::TEX_BOSS);
	//			D3DXVECTOR3 vec = D3DXVECTOR3((cosf(m_fAttackRot) * 30.0f), -(sinf(m_fAttackRot) * 30.0f), 0);
	//			pos -= vec;
	//			if (LibrarySpace::OutScreen2D(&pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT)) && m_nCountOperation <= -200)
	//			{
	//				m_nCountOperation = -90;
	//				m_nCounter++;

	//				// 5��ːi������
	//				if (m_nCounter >= 5)
	//				{
	//					pos = D3DXVECTOR3((ScreenCenter.x * 2) + (SIZE_WIDTH / 2), ScreenCenter.y - 110.0f, 0.0f);
	//				}
	//			}
	//		}
	//		else if (!LibrarySpace::OutScreen2D(&pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT)))
	//		{
	//			// �G�t�F�N�g����
	//			CEffect::Create(pos, D3DXVECTOR2(SIZE_WIDTH, SIZE_HEIGHT), CEffect::TYPE_AFTERIMAGE, CEffect::TEX_BOSS);
	//			// ���ɓːi����
	//			pos.x += -30.0f;
	//		}
	//	}
	//	else
	//	{
	//		//�g�k������
	//		ChangeSize(&size, 2.0f);

	//		if (m_nCountOperation == RUSH_OPERATION)
	//		{// �ŏ��݈̂ʒu��ۑ�
	//			m_PosOld = pos;
	//		}

	//		m_nCountOperation--;
	//		pos.x += m_nCountOperation * 0.1f;

	//		if(m_nCountOperation==1)
	//		{
	//			// �ːi��
	//			CSound::Play(CSound::SOUND_LABEL_SE_RUSH);
	//		}
	//	}

	//	break;
	//	//=================================
	//	// �G���G�̐����U��
	//	//=================================
	//case CEnemyBoss::PATTERN_CREATE:

	//	//�g�k������
	//	ChangeSize(&size, 3.0f);

	//	//�U���J�E���^�[�����Z
	//	m_nCounter++;

	//	if (m_nCounter >= 60)
	//	{
	//		m_nCountOperation--;

	//		if (m_nCountOperation <= RUSH_OPERATION - pBossInfo->nInterval)
	//		{
	//			m_nCountOperation = RUSH_OPERATION;
	//			CEnemy::Create(pos, (CEnemy::TYPE)pBossInfo->nType, pBossInfo->nLife, pBossInfo->move);
	//			m_nCountObject++;
	//			if (m_nCountObject >= pBossInfo->nNum)
	//			{
	//				// �ʏ��Ԃɖ߂�(�ϐ��̃��Z�b�g)
	//				StateReset();
	//			}
	//		}
	//	}

	//	break;
	//case CEnemyBoss::PATTERN_BARRAGE:

	//	//�g�k������
	//	ChangeSize(&size, 3.0f);

	//	//�U���J�E���^�[�����Z
	//	m_nCounter++;
	//	//��ɉ�]������
	//	m_fAttackRot += 0.05f;

	//	if (m_nCounter >= 60)
	//	{
	//		//�A���U���J�E���^�[�����Z
	//		m_nCountOperation--;

	//		if (m_nCountOperation <= RUSH_OPERATION - 3)
	//		{
	//			m_nCountOperation = RUSH_OPERATION;
	//			m_nCountObject++;
	//			float fDeg = 0.0f;

	//			while (fDeg <= 330.0f)
	//			{
	//				// �e���~��ɔz�u
	//				float fRad = (fDeg * (D3DX_PI / 180)) + m_fAttackRot;
	//				D3DXVECTOR3 vec = D3DXVECTOR3(sinf(fRad) * 10.0f, cosf(fRad) * 10.0f, 0);
	//				CBullet* pBullet = CBullet::Create(pos, vec, 1, CBullet::TYPE_ENEMY_RED);
	//				pBullet->SetParent(CBullet::PARENT_ENEMY);
	//				pBullet->SetRot(fRad);
	//				fDeg += 60.0f;
	//			}

	//			if (m_nCountObject >= 40)
	//			{
	//				// �ʏ��Ԃɖ߂�(�ϐ��̃��Z�b�g)
	//				StateReset();
	//			}

	//			// �e���ˉ�
	//			CSound::Play(CSound::SOUND_LABEL_SE_SHOT2);
	//		}
	//	}
	//	break;

	//	//=================================
	//	// ���S
	//	//=================================
	//case CEnemyBoss::PATTERN_DIE:
	//	// ���S�J�E���^�[�����Z
	//	m_nCounter++;

	//	if (m_nCounter == 1)
	//	{
	//		// ���t�F�[�h�̐���
	//		CFadeScene::Create(CFadeScene::TYPE_WHITE);

	//		// �G�̎��S�t���O�𗧂Ă�
	//		CGame::SetDieBoss(true);

	//		// �{�X���S��
	//		CSound::Play(CSound::SOUND_LABEL_SE_DIE_BOSS);

	//		// �{�XBGM���~�߂�
	//		CSound::Stop(CSound::SOUND_LABEL_BOSS);
	//	}
	//	else if (m_nCounter == 40)
	//	{
	//		// �|�[�Y����
	//		CManager::SetPause(false);
	//	}
	//	else if (m_nCounter >= 40)
	//	{
	//		// �ʒu�������ɉ�����
	//		pos += D3DXVECTOR3(-1.0f, 2.0f, 0.0f);

	//		if (m_nCounter % 5 == 0)
	//		{
	//			// �����̐���
	//			CExplosion::Create(D3DXVECTOR3((float)LibrarySpace::GetRandNum((int)(pos.x + (size.x / 2)), (int)(pos.x - (size.x / 2))),
	//				(float)LibrarySpace::GetRandNum((int)(pos.y + (size.y / 2)), (int)(pos.y - (size.y / 2))), 0.0f),
	//				D3DXVECTOR2(size.x / 2, size.y / 2));
	//		}

	//		if (LibrarySpace::OutScreen2D(&pos, size) == true)
	//		{
	//			//��ʂ�h�炷
	//			//CObject::SetShake(60);
	//			// �{�X���S��
	//			CSound::Play(CSound::SOUND_LABEL_SE_EXPLOSION_BOSS);
	//			// �j��
	//			Uninit();

	//			// ���b�V���w�i�̔j��
	//			CMeshField *pMesh = CGame::GetMeshField();
	//			if (pMesh != nullptr)
	//			{
	//				pMesh->SetUninit(true);
	//			}

	//			// �Q�[���N���A���S�̐���
	//			CLogo::Create(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, 100.0f),
	//				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_CLEAR, CLogo::ANIM_LENGTHWISE, 420);

	//			CLogo::Create(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH / 4, 150.0f),
	//				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_BONUS, CLogo::ANIM_LENGTHWISE, 420);

	//			// �Q�[���N���A��
	//			CSound::Play(CSound::SOUND_LABEL_SE_CLEAR);

	//			// �{�[�i�X�X�R�A���Z
	//			for (int nCnt = 0; nCnt < CPlayer::PLAYER_MAX; nCnt++)
	//			{
	//				CPlayer *pPlayer = CGame::GetPlayer(nCnt);
	//				if (pPlayer != nullptr)
	//				{
	//					// �X�R�A
	//					CScore* pScore = pPlayer->GetScore();
	//						
	//					if (pScore != nullptr)
	//					{
	//						pScore->Add(30000);
	//					}
	//				}
	//			}
	//			return true;
	//		}
	//	}
	//	break;

	default:
		break;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------
// �g�k����
//-----------------------------------------------------------------------------------------------
void CEnemyBoss::ChangeSize(D3DXVECTOR2 *pSize, const float& fSize)
{
	//if (!m_bSizeChange)
	//{
	//	*pSize -= D3DXVECTOR2(fSize, fSize);
	//	if (pSize->x <= SIZE_WIDTH - 20.0f)
	//	{
	//		m_bSizeChange = true;
	//	}
	//}
	//else if (m_bSizeChange)
	//{
	//	*pSize += D3DXVECTOR2(fSize, fSize);
	//	if (pSize->x >= SIZE_WIDTH)
	//	{
	//		m_bSizeChange = false;
	//	}
	//}
}

//-----------------------------------------------------------------------------------------------
// �����o�ϐ����Z�b�g
//-----------------------------------------------------------------------------------------------
void CEnemyBoss::StateReset()
{
	//m_nCounter = 0;
	//m_nCountObject = 0;
	//m_fAttackRot = 0.0f;
	//m_pattern = PATTERN_NORMAL;
	//m_nCountOperation = RUSH_OPERATION;
}
