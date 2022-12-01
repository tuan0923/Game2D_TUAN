//===============================================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : SHUGO KURODA
//
//===============================================================================================
#include "manager.h"
#include "game.h"
#include "object.h"
#include "sound.h"

#include "library.h"
#include "load.h"
#include "fade_scene.h"
#include "input_keyboard.h"
#include "input_joypad.h"

#include "score.h"
#include "life.h"
#include "number.h"
#include "logo.h"
#include "pause.h"
#include "rank.h"
#include "score.h"

#include "bg.h"
#include "cloud.h"
#include "enemy.h"
#include "enemy_boss.h"
#include "bullet.h"
#include "bullet_option.h"
#include "item.h"
#include "barrier.h"
#include "explosion.h"
#include "spray.h"
#include "bubble.h"
#include "effect.h"
#include "bg_move.h"
#include "ui.h"
#include "gauge.h"
#include "continue.h"

// �ǉ�
#include "object3D.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "enemy_boss.h"
#include "item.h"
#include "model_obstacle.h"
#include "model_manager.h"
#include "logo_countdown.h"
#include "logo_extend.h"
#include "mesh_sphere.h"
//#include "avalanche.h"

//-----------------------------------------------------------------------------------------------
// using�錾
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CGame::CGame() :m_pPlayer{}, m_pEnemyBoss(), m_pItem(), m_pCamera(), m_bStart(false), m_bEnd(false)
{
	//�G�̐�������������
	ZeroMemory(&m_EnemyInfo, sizeof(m_EnemyInfo));
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CGame::~CGame()
{
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CGame::Init()
{
	//���̃��b�V���̔z�u
	CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR2(3000.0f, 3000.0f), 10, 10, "TEX_TYPE_GAME_BG");

	// �|������
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// �|������
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f));
	// �|������
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, -400.0f));
	// �|������
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, -600.0f));
	// �|������
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, -800.0f));

	// ���C�g����
	CLight::Create(D3DXVECTOR3(-0.2f, -0.8f, 0.4f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CLight::Create(D3DXVECTOR3(0.2f, -0.1f, -0.8f), D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));

	// ���f������
	CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_ITEM_METAL");

	// �G�{�X����
	m_pEnemyBoss = CEnemyBoss::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WASIZU");

	// �J��������
	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 130.0f, -230.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// �Ǐ]�Ώۂ̐ݒ�
	m_pCamera->SetTracking(true);
	m_pCamera->SetPosTracking(m_pEnemyBoss->GetpPosition());

	// Item����
	m_pItem = CItem::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), CItem::TYPE_NONE, "XFILE_TYPE_SHOE");

	// �؂̂Q��𐶐�
	for (int nCnt = -2; nCnt < 0; nCnt++)
	{
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (50.0f*(nCnt ))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��1");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (200.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��2");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (300.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��3");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (400.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��4");

		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (100.0f*(nCnt ))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��1");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (200.0f*(nCnt ))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��2");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (300.0f*(nCnt ))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��3");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (400.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��4");

	}
	for (int nCnt = 1; nCnt < 5; nCnt++)
	{
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (50.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��1");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (200.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��2");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (300.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��3");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (400.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��4");

		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (50.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��1");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (200.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��2");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (300.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��3");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (400.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_��4");

	}
	

	// ���f���}�l�[�W���[����
	CModelManager::Create();

	// ���f������
	CModel::Create(D3DXVECTOR3(0.0f, -55.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_CREVASSE");

	// �J�E���g�_�E���̊J�n
	CLogoCountDown::Create(5);

	// �v���C���[�Q�����̎擾
	CManager::SEntryInfo *pEntry = CManager::GetManager()->GetEntry();

	// �v���C���[����
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		// ���݂̔ԍ����Q�����Ă���Ȃ�
		if (pEntry[nCntPlayer].bEntry == true)
		{
			// �L�[�{�[�h�ŎQ�����Ă���Ȃ�
			if (pEntry[nCntPlayer].bEntryKeyboard == true)
			{
				// �v���C���[����
				m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_STAR", nCntPlayer);
				m_pPlayer[nCntPlayer]->SetKeyboard(pEntry[nCntPlayer].bEntryKeyboard);
			}
			else
			{
				// �v���C���[����
				m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_STAR", nCntPlayer);
				m_pPlayer[nCntPlayer]->SetGamePadNum(pEntry[nCntPlayer].nGamePadNum);
			}

			// �Q�[���ɎQ�����Ă����Ԃɂ���
			m_pPlayer[nCntPlayer]->SetStart(true);
		}
	}

	////�G���ǂݍ���
	//m_EnemyInfo.pCreate = LoadSpace::GetEnemy();
	////�E�F�[�u���̓ǂݍ���
	//m_EnemyInfo.nWave = LoadSpace::GetWave();
	//// �e�N�X�`���ǂݍ���
	//LoadAll();
	//// UI�̐���
	//CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 50.0f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), 
	//	CUi::TYPE_AREA_A, CUi::ANIM_NONE, CUi::PLAYER_NONE);

	//// �v���C���[����
	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	// �v���C���[ENTRY���̎擾
	//	bool bEntry = CManager::GetEntry(nCntPlayer);

	//	// �G���g���[���Ă����
	//	if (bEntry == true)
	//	{// �v���C���[����
	//		m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(-630.0f, (float)CRenderer::SCREEN_HEIGHT, 0.0f), nCntPlayer);
	//	}
	//	// �G���g���[���Ă��Ȃ����
	//	else if (bEntry == false)
	//	{
	//		switch (nCntPlayer)
	//		{
	//		case CPlayer::PLAYER_1:
	//			// �G���g���[�҂���UI1�𐶐�
	//			CUi::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 4) - 50.0f, 40.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f),
	//				CUi::TYPE_PRESS_ANY_BUTTON, CUi::ANIM_FLASHING, CUi::PLAYER_1_NOT_ENTRY);
	//			// �G���g���[�҂���UI2�𐶐�
	//			CUi::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 4) - 50.0f, 80.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f),
	//				CUi::TYPE_TO_START, CUi::ANIM_NONE, CUi::PLAYER_1_NOT_ENTRY);
	//			break;

	//		case CPlayer::PLAYER_2:
	//			// �G���g���[�҂���UI1�𐶐�
	//			CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH - 300.0f, 40.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f),
	//				CUi::TYPE_PRESS_ANY_BUTTON, CUi::ANIM_FLASHING, CUi::PLAYER_2_NOT_ENTRY);
	//			// �G���g���[�҂���UI2�𐶐�
	//			CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH - 300.0f, 80.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f),
	//				CUi::TYPE_TO_START, CUi::ANIM_NONE, CUi::PLAYER_2_NOT_ENTRY);
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	//// �w�i�̐���
	//CBg::Create(CBg::SET_A);

	////�|�C���^�̏�����
	//m_pPlayer[CPlayer::PLAYER_MAX] = { nullptr };
	//m_pMeshField = nullptr;
	//m_bCreateCloud = true;
	//m_bCreateBubble = false;
	//m_bDieBoss = false;

	//// ���艹
	//CSound::Play(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CGame::Uninit()
{
	//�e�N�X�`���̔j��
	//UnloadAll();

	// �|�[�Y��Ԃ�����
	CManager::GetManager()->SetPause(false);

	// ���艹
	CSound::Stop();

	// �v���C���[�j��
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] != nullptr)
		{
			m_pPlayer[nCntPlayer] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CGame::Update()
{
	// �Q�[�����I�����Ă��Ȃ��Ȃ�
	if (m_bEnd == false)
	{
		// �Q�[�����I���������ǂ����𔻒�
		CheckGameEnd();
	}
	//// �L�[�{�[�h���̎擾
	//CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();
	//// �Q�[���p�b�h���̎擾
	//CInputJoypad *pJoypad = CManager::GetInputJoypad();

	//// �|�[�Y����
	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	// �{�X���S�t���O�������Ă��Ȃ����
	//	if (m_bDieBoss == false)
	//	{
	//		// �v���C���[ENTRY���̎擾
	//		bool bEntry = CManager::GetEntry(nCntPlayer);

	//		// �G���g���[���Ă����
	//		if (bEntry == true)
	//		{// �|�[�Y����
	//			if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_PAUSE) == true || pJoypad->GetTrigger(CInputJoypad::JOYKEY_START, nCntPlayer) == true)
	//			{
	//				// �|�[�Y��Ԃ̎擾
	//				bool bPause = CManager::GetPause();
	//				// �|�[�Y���łȂ����
	//				if (bPause == false)
	//				{//�|�[�Y��ʂ𐶐�
	//					CPause::Create(nCntPlayer);
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}

	//// �v���C���[ENTRY���̎擾
	//bool bEntry1P = CManager::GetEntry(CPlayer::PLAYER_1);
	//bool bEntry2P = CManager::GetEntry(CPlayer::PLAYER_2);

	//if (bEntry1P == false && bEntry2P == false)
	//{
	//	// �R���e�B�j���[���o�̐���
	//	CContinue::Create(D3DXVECTOR3(750.0f, 300.0f, 0.0f), D3DXVECTOR2(40.0f, 30.0f))->Add(15);
	//}

	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	// �v���C���[����
	//	if (m_pPlayer[nCntPlayer] == nullptr)
	//	{
	//		// �v���C���[ENTRY���̎擾
	//		bool bEntry = CManager::GetEntry(nCntPlayer);

	//		// �G���g���[���Ă����
	//		if (bEntry == true)
	//		{// �v���C���[����
	//			m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(-630.0f, (float)CRenderer::SCREEN_HEIGHT, 0.0f), nCntPlayer);
	//		}
	//	}
	//	// �v���C���[�j��
	//	else if (m_pPlayer[nCntPlayer] != nullptr)
	//	{
	//		// �v���C���[���S��Ԃ̎擾
	//		bool bDie = m_pPlayer[nCntPlayer]->GetDie();

	//		// ���S���Ă����
	//		if (bDie == true)
	//		{// �v���C���[�j��

	//			if (CContinue::GetContinue() == false)
	//			{
	//				m_pPlayer[nCntPlayer]->Uninit();
	//				m_pPlayer[nCntPlayer] = nullptr;

	//				switch (nCntPlayer)
	//				{
	//				case CPlayer::PLAYER_1:
	//					// �G���g���[�҂���UI1�𐶐�
	//					CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 4, 40.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f), CUi::TYPE_PRESS_ANY_BUTTON, CUi::ANIM_FLASHING, CUi::PLAYER_1_NOT_ENTRY);
	//					// �G���g���[�҂���UI2�𐶐�
	//					CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 4, 80.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f), CUi::TYPE_TO_START, CUi::ANIM_NONE, CUi::PLAYER_1_NOT_ENTRY);
	//					break;

	//				case CPlayer::PLAYER_2:
	//					// �G���g���[�҂���UI1�𐶐�
	//					CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH - 300.0f, 40.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f), CUi::TYPE_PRESS_ANY_BUTTON, CUi::ANIM_FLASHING, CUi::PLAYER_2_NOT_ENTRY);
	//					// �G���g���[�҂���UI2�𐶐�
	//					CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH - 300.0f, 80.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f), CUi::TYPE_TO_START, CUi::ANIM_NONE, CUi::PLAYER_2_NOT_ENTRY);
	//					break;
	//				default:
	//					break;
	//				}

	//				// �s�Q����Ԃɂ���
	//				CManager::SetEntry(nCntPlayer, false);
	//			}
	//		}
	//	}
	//}

	////�_�𐶐����邩�ǂ���
	//if (m_bCreateCloud == true)
	//{
	//	//�_�̐�������
	//	CreateCloud();
	//}
	////�A�G�t�F�N�g�𐶐����邩�ǂ���
	//if (m_bCreateBubble == true)
	//{
	//	//�A�G�t�F�N�g�̐�������
	//	CreateBubble();
	//}

	////�G�̐�������	
	//CreateEnemy();
}

//-----------------------------------------------------------------------------------------------
// �Q�[�����I�����邩�ǂ����𔻒�
//-----------------------------------------------------------------------------------------------
bool CGame::CheckGameEnd()
{
	// �v���C���[�̎��S��
	int nNumDie = 0;

	// �v���C���[����
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		// ���݂̃v���C���[���Q�����Ă���Ȃ�
		if (m_pPlayer[nCntPlayer] != nullptr)
		{
			// ���S���Ă�����
			if (m_pPlayer[nCntPlayer]->GetDie() == true)
			{// �v���C���[�̎��S�������Z
				nNumDie++;
			}
		}
		else
		{// �v���C���[�̎��S�������Z
			nNumDie++;
		}
	}

	// �v���C���[���S�����S���Ă�����
	if (CPlayer::PLAYER_MAX <= nNumDie)
	{
		// �Q�[���I���t���O�𗧂Ă�
		m_bEnd = true;
		// �Q�[���I�����S�̐���
		CLogoExtend::Create(D3DXVECTOR2(250.0f, 80.0f), "TEX_TYPE_END_UI", 180);
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------
// �G�̐���(�O���X�N���v�g�g�p)
//-----------------------------------------------------------------------------------------------
void CGame::CreateEnemy()
{
	// �G�����J�E���^�[�̉��Z
	m_EnemyInfo.nCreatenCount++;

	//�G�̃E�F�[�u��������������
	for (int nCntEnemy = 0; nCntEnemy < m_EnemyInfo.nWave; nCntEnemy++)
	{
		// �G���o������t���[�����ɒB������ && �G�̏o�����I����Ă��Ȃ��Ȃ�
		if (m_EnemyInfo.pCreate[nCntEnemy].nFrame <= m_EnemyInfo.nCreatenCount && m_EnemyInfo.count[nCntEnemy].bCreate == false)
		{
			//�G���A���ŏo������܂ł̃J�E���^�[�����Z
			m_EnemyInfo.count[nCntEnemy].nCreate++;
			//�G�̘A���o���Ԋu�J�E���^�[���ő�ɒB������
			if (m_EnemyInfo.count[nCntEnemy].nCreate >= m_EnemyInfo.pCreate[nCntEnemy].nInterval)
			{
				//�G�̐���(�ʒu�A��ށA�̗́A�ړ����������ɐݒ�)
				CEnemy *pEnemy = CEnemy::Create(m_EnemyInfo.pCreate[nCntEnemy].pos, (CEnemy::TYPE)m_EnemyInfo.pCreate[nCntEnemy].nType, m_EnemyInfo.pCreate[nCntEnemy].nLife, &m_EnemyInfo.pCreate[nCntEnemy].move[0]);

				//�G�̐������J�E���^�[�����Z
				m_EnemyInfo.count[nCntEnemy].nNum++;
				//�G�̘A���o���Ԋu�J�E���^�[�̃��Z�b�g
				m_EnemyInfo.count[nCntEnemy].nCreate = 0;

				//�G���ő吔�܂Ő���������
				if (m_EnemyInfo.pCreate[nCntEnemy].nNum <= m_EnemyInfo.count[nCntEnemy].nNum)
				{
					// �F�̐ݒ肪����Ă�����
					if (m_EnemyInfo.pCreate[nCntEnemy].nColor > 0)
					{// �Ō���̓G�̐F��ݒ�
						pEnemy->SetItemColor((CEnemy::COLORITEM)m_EnemyInfo.pCreate[nCntEnemy].nColor);
					}
					// ���̃E�F�[�u�̐�������߂�
					m_EnemyInfo.count[nCntEnemy].bCreate = true;
				}
			}
		}
	}

	// �{�X���o��������
	if (m_EnemyInfo.nCreatenCount == 5260)
	{
		//CEnemyBoss::Create(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT + CEnemyBoss::SIZE_HEIGHT, 0.0f), CEnemy::TYPE_DARK_BOSS);
		// �x����
		CSound::Play(CSound::SOUND_LABEL_BOSS);
	}

	//���S�̐���
	CreateLogo(m_EnemyInfo.nCreatenCount);
}

//-----------------------------------------------------------------------------------------------
// ���S�̐���
//-----------------------------------------------------------------------------------------------
void CGame::CreateLogo(int nCounter)
{
	//if (nCounter == 4800)
	//{
	//	// �{�X�ڋߒ��̃��S
	//	CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR2(CRenderer::SCREEN_WIDTH - 400.0f, 90.0f),
	//		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_WARNING, CLogo::ANIM_LENGTHWISE, 420);

	//	// �Q�[��BGM���X�g�b�v
	//	CSound::Stop(CSound::SOUND_LABEL_GAME);
	//	// �x����
	//	CSound::Play(CSound::SOUND_LABEL_SE_WARNING);
	//}

	//if (nCounter == 4920)
	//{
	//	// �{�X�ڋߒ��̐������S
	//	CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(CRenderer::SCREEN_WIDTH - 760.0f, 270.0f),
	//		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_WARNING_SUB, CLogo::ANIM_HORIZONTALLY, 300);
	//}

	//if (nCounter == 4800)
	//{
	//	// �{�X�ڋߎ��̔��Â��t�F�[�h
	//	CFadeScene::Create(CFadeScene::TYPE_BLACK);
	//}
}

//-----------------------------------------------------------------------------------------------
// �����L���O�X�R�A�̐ݒ�
//-----------------------------------------------------------------------------------------------
void CGame::SetPlayerScore()
{
	//// �v���C���[�̃X�R�A��ۑ�
	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	if (m_pPlayer[nCntPlayer] != nullptr)
	//	{
	//		// �v���C���[ENTRY���̎擾
	//		bool bEntry = CManager::GetManager()->GetEntry(nCntPlayer);

	//		// �G���g���[���Ă����
	//		if (bEntry == true)
	//		{// �v���C���[����
	//			// �v���C���[�X�R�A�̏�����
	//			CRank::SetScore(0, nCntPlayer);

	//			CScore* pScore = m_pPlayer[nCntPlayer]->GetScore();
	//			if (pScore != nullptr)
	//			{
	//				int nSocre = pScore->GetScore();
	//				CRank::SetScore(nSocre, nCntPlayer);
	//			}
	//		}
	//	}
	//}
}
