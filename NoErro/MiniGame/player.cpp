//=============================================================================
//
//	�v���C���[����[player.cpp]
//	Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "sound.h"
#include "renderer.h"

#include "library.h"

#include "bg.h"
#include "spray.h"
#include "bullet.h"
#include "player.h"
#include "explosion.h"
#include "ui.h"
#include "gauge.h"
#include "life.h"
#include "score.h"

#include "rank.h"

// �ǉ�
#include "model_obstacle.h"
#include "game.h"
#include "camera.h"
#include "x_file_motion.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define PLAYER_UI_SIZE				(D3DXVECTOR2(200.0f, 50.0f))
#define LIFE_UI_SIZE				(D3DXVECTOR2(120.0f, 30.0f))
#define LEVEL_UI_SIZE				(D3DXVECTOR2(50.0f, 50.0f))
#define ATTACK_INTERVAL				(7)
#define JOYKEY_LEFT_STICK_UP		(-0.2f)
#define JOYKEY_LEFT_STICK_DOWN		(0.2f)

#define FIELD_SIZE_WIDTH			(130.0f)
#define FIELD_SIZE_HEIGHT			(250.0f)
#define FIELD_SIZE_HEIGHT_CAMERA	(70.0f)

#define PLAYER_SIZE					(16.0f)

// �d��
#define GRAVITY			(0.1f)
// �W�����v��
#define JUMP_POWER		(2.0f)

//-----------------------------------------------------------------------------
// using�錾
//-----------------------------------------------------------------------------
using namespace LibrarySpace;

//*****************************************************************************
// �萔�錾
//*****************************************************************************
const float CPlayer::SIZE_X = 90.0f;
const float CPlayer::SIZE_Y = 40.0f;
const float CPlayer::MOVE_DEFAULT = 0.35f;
// �A�j���[�V�����Ԋu
const int CPlayer::ANIM_INTERVAL = 5;
// �A�j���[�V�����ő吔
const int CPlayer::MAX_ANIM = 2;
// U���W�̍ő啪����
const int CPlayer::DIVISION_U = 2;
// V���W�̍ő啪����
const int CPlayer::DIVISION_V = 4;
// �v���C���[�̃f�t�H���g�J���[
const D3DXCOLOR CPlayer::DEFAULT_COL = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
// �f�t�H���g�c�@
const int CPlayer::DEFAULT_LIFE = 2;

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CPlayer::CPlayer() :
	m_move(0.0f, 0.0f, 0.0f), m_posOld(0.0f, 0.0f, 0.0f), m_state(STATE_NORMAL), m_nCntState(0), m_nCntAttack(0), m_nCntAnim(0), m_nPatternAnim(0), m_nCntAnimMove(0), m_bControlKeyboard(false), m_nGamePadNum(0),
	m_nTexRotType(TYPE_NEUTRAL), m_nPlayerNum(0), m_bIsJumping(false), m_bControl(false), m_bInSea(false), m_pLife(nullptr), m_pScore(nullptr), m_bDie(false), m_bStart(false)
{
	//�I�u�W�F�N�g�̎�ސݒ�
	SetType(EObject::OBJ_PLAYER);
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

//-----------------------------------------------------------------------------
// �C���X�^���X��������
//-----------------------------------------------------------------------------
CPlayer *CPlayer::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name, int nPlayerNum)
{
	//�C���X�^���X����
	CPlayer *pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		// �ʒu�ݒ�
		pPlayer->SetPosition(pos);
		// �p�x�ݒ�
		pPlayer->SetRotation(rot);
		// X�t�@�C���̐ݒ�
		pPlayer->BindMotion(CManager::GetManager()->GetMotion()->GetMotion(name));
		// ��������
		pPlayer->Init();
		// �v���C���[�ԍ��̐ݒ�
		pPlayer->m_nPlayerNum = nPlayerNum;
	}

	return pPlayer;
}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT CPlayer::Init()
{
	// �X�R�A�̐���
	CScore::Create(D3DXVECTOR3(250.0f, 25.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 20);

	// ����\��Ԃɂ���
	m_bControl = true;

	// ������
	CMotion::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CPlayer::Uninit()
{
	CMotion::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CPlayer::Update()
{
	//�O��̈ʒu��ۑ�
	m_posOld = GetPosition();

	// �ʒu�����擾
	D3DXVECTOR3 pos = CMotion::GetPosition();
	// �T�C�Y�̎擾
 	D3DXVECTOR3 size = GetSizeMax();

	// ����ł����ԂȂ� && ���S���Ă��Ȃ��Ȃ�
	if (m_bControl == true && m_state != STATE_DIE)
	{
		// �ړ�����
		Move();

		// �W�����v���Ă��Ȃ����
		if (m_bIsJumping == false)
		{
			// �L�[�{�[�h���̎擾
			CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
			// �W���C�p�b�h���̎擾
			CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

			// �L�[�{�[�h����̏ꍇ
			if (m_bControlKeyboard == true &&
				pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_ATTACK) == true)
			{// SPACE�L�[����

				// �W�����v�͂̐ݒ�
				m_move.y = JUMP_POWER;

				// �W�����v�t���O�̐ݒ�
				m_bIsJumping = true;
			}
			// �Q�[���p�b�h����̏ꍇ
			else if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_A, m_nGamePadNum) == true)
			{// A�{�^������

				// �W�����v�͂̐ݒ�
				m_move.y = JUMP_POWER;

				// �W�����v�t���O�̐ݒ�
				m_bIsJumping = true;
			}
		}

		// �d�͕��ׂ�������
		m_move.y -= GRAVITY;
	}
	
	//�v���C���[������Ɋ������܂�Ă�����
	if (m_state == STATE_INAVALANCHE)
	{
		// �L�[�{�[�h���̎擾
		CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
		// �W���C�p�b�h���̎擾
		CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

		//�v���C���[����ނ�����
		m_move.z -= 1.0f;

		if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_OK))
		{
			m_nPushButton++;
			if (m_nPushButton >= 1/*���񉟂��������𔲂��邩*/)
			{
				m_state = STATE_NORMAL;
			}
		}
	}

	// �ړ��ʂ̉��Z
	pos += m_move;

	// ��Q���̓����蔻��
	CObstacle::CollisionAll(&pos, m_nPlayerNum);

	// �ړ��ʂ̌���
	m_move.x -= m_move.x * 0.2f;
	m_move.z -= m_move.z * 0.2f;

	//�ǁE���̓����蔻�菈��
	if (pos.x - (size.x / 2) <= -FIELD_SIZE_WIDTH / 2)
	{//����
		pos.x = (-FIELD_SIZE_WIDTH / 2) + (size.x / 2);
	}
	else if (pos.x + (size.x / 2) >= FIELD_SIZE_WIDTH / 2)
	{//�E��
		pos.x = (FIELD_SIZE_WIDTH / 2) - (size.x / 2);
	}
	//if (g_Player.pos.z + (PLAYER_WIDTH / 2) >= 400.0f / 2)
	//{//����
	//	g_Player.pos.z = (400.0f / 2) - (PLAYER_WIDTH / 2);
	//}

	// �Q�[���Q�����ł����
	if (m_bStart == true)
	{
		// �J�����ʒu�̎擾
		D3DXVECTOR3 posCamera = CManager::GetManager()->GetGame()->GetCamera()->GetPosV();

		if (pos.z - (size.z / 2) <= posCamera.z + FIELD_SIZE_HEIGHT_CAMERA)
		{//��O��
			pos.z = (posCamera.z + FIELD_SIZE_HEIGHT_CAMERA) + (size.z / 2);
		}
	}
	// ���r�[�ҋ@���ł����
	else
	{
		if (pos.z - (size.z / 2) <= -FIELD_SIZE_HEIGHT / 2)
		{//��O��
			pos.z = (-FIELD_SIZE_HEIGHT / 2) + (size.z / 2);
		}
	}

	if (pos.y <= 0.0f)
	{//��
		pos.y = 0.0f;
		m_bIsJumping = false;
		m_move.y = 0.0f;			//�ړ���Y�̏�����
	}

	//�ʒu���X�V
	CMotion::SetPosition(pos);

	//��ԊǗ�
	//State();

	// ���[�V�����Đ�
	CMotion::Motion();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void CPlayer::Draw()
{
	//�`��
	CMotion::Draw();
}

//-----------------------------------------------------------------------------
// �ړ�����
//-----------------------------------------------------------------------------
void CPlayer::Move()
{
	// �L�[�{�[�h���̎擾
	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	// �W���C�p�b�h���̎擾
	CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	// �L�[�{�[�h�ő��삵�Ă���Ȃ�
	if (m_bControlKeyboard == true)
	{
		if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_LEFT) == true)
		{//���L�[����
			if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
			{//��L�[����
				//�ړ��ʉ��Z
				m_move.x += GetSinVec(-0.75f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.75f, MOVE_DEFAULT);
				//�A�j���[�V�����ύX
				m_nCntAnimMove++;
			}
			else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
			{//���L�[����
				m_move.x += GetSinVec(-0.25f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.25f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else
			{
				m_move.x += GetSinVec(-0.5f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.5f, MOVE_DEFAULT);
				m_nTexRotType = TYPE_NEUTRAL;
				m_nCntAnimMove = 0;
			}
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_RIGHT) == true)
		{//�E�L�[����
			if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
			{//��L�[����
				m_move.x += GetSinVec(0.75f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.75f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
			{//���L�[����
				m_move.x += GetSinVec(0.25f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.25f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else
			{
				m_move.x += GetSinVec(0.5f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.5f, MOVE_DEFAULT);
				m_nTexRotType = TYPE_NEUTRAL;
				m_nCntAnimMove = 0;
			}
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
		{//��L�[����
			m_move.x += GetSinVec(1.0f, MOVE_DEFAULT);
			m_move.z += GetCosVec(1.0f, MOVE_DEFAULT);
			m_nCntAnimMove++;
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
		{//���L�[����
			m_move.x += GetSinVec(0.0f, MOVE_DEFAULT);
			m_move.z += GetCosVec(0.0f, MOVE_DEFAULT);
			m_nCntAnimMove++;
		}
	}
	// �Q�[���p�b�h����Ȃ�
	else
	{
		if (pJoypad->GetPress(CInputJoypad::JOYKEY_LEFT, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).x <= -0.2f)
		{//���L�[����
			if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
			{//��L�[����
			 //�ړ��ʉ��Z
				m_move.x += GetSinVec(-0.75f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.75f, MOVE_DEFAULT);
				//�A�j���[�V�����ύX
				m_nCntAnimMove++;
			}
			else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
			{//���L�[����
				m_move.x += GetSinVec(-0.25f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.25f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else
			{
				m_move.x += GetSinVec(-0.5f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.5f, MOVE_DEFAULT);
				m_nTexRotType = TYPE_NEUTRAL;
				m_nCntAnimMove = 0;
			}
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_RIGHT, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).x >= 0.2f)
		{//�E�L�[����
			if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
			{//��L�[����
				m_move.x += GetSinVec(0.75f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.75f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
			{//���L�[����
				m_move.x += GetSinVec(0.25f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.25f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else
			{
				m_move.x += GetSinVec(0.5f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.5f, MOVE_DEFAULT);
				m_nTexRotType = TYPE_NEUTRAL;
				m_nCntAnimMove = 0;
			}
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
		{//��L�[����
			m_move.x += GetSinVec(1.0f, MOVE_DEFAULT);
			m_move.z += GetCosVec(1.0f, MOVE_DEFAULT);
			m_nCntAnimMove++;
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
		{//���L�[����
			m_move.x += GetSinVec(0.0f, MOVE_DEFAULT);
			m_move.z += GetCosVec(0.0f, MOVE_DEFAULT);
			m_nCntAnimMove++;
		}
	}
}

//-----------------------------------------------------------------------------
// �W�����v
//-----------------------------------------------------------------------------
void CPlayer::Jump()
{

}

//-----------------------------------------------------------------------------
// ��ԊǗ�
//-----------------------------------------------------------------------------
void CPlayer::State()
{
	switch (m_state)
	{
		// �ʏ�
	case CPlayer::STATE_NORMAL:
		break;

		// ����
	case CPlayer::STATE_RUN:
		break;

		// �W�����v
	case CPlayer::STATE_JUMP:
		break;

		// �U��
	case CPlayer::STATE_ATTACK:
		break;

		// ���S
	case CPlayer::STATE_DIE:
		break;

		// ����Ɋ������܂�Ă�
	case CPlayer::STATE_INAVALANCHE:
		break;

	default:
		break;
	}
}

//-----------------------------------------------------------------------------
// �_���[�W����
//-----------------------------------------------------------------------------
void CPlayer::Damage()
{
	//if (m_BarrierLevel == CBarrier::LEVEL_NONE)
	//{

	// ���S����
	Die();

	// �v���C���[���S��
	//CSound::Play(CSound::SOUND_LABEL_SE_DIE_PLAYER);

	//}
	//else
	//{
	//	m_BarrierLevel = (CBarrier::LEVEL)(m_BarrierLevel - 1);

	//	if (m_BarrierLevel == CBarrier::LEVEL_NONE)
	//	{
	//		if (m_pBarrier != nullptr)
	//		{
	//			m_pBarrier->Uninit();
	//			m_pBarrier = nullptr;
	//		}
	//	}
	//	else
	//	{
	//		m_pBarrier->SetBarrier(m_BarrierLevel);
	//	}
	//	m_state = STATE_RESPAWN;
	//	m_nCntState = 150;
	//}
}

//-----------------------------------------------------------------------------
// ���S����
//-----------------------------------------------------------------------------
void CPlayer::Die()
{
	//CModel::Uninit();

	// ����s�\�ɂ���
	m_bControl = false;
	// �v���C���[�����S��Ԃɂ���
	m_bDie = true;

	//// ���C�t���j������Ă��Ȃ����
	//if (m_pLife != nullptr)
	//{
	//	// ���C�t�����炷
	//	m_pLife->Add(-1);

	//	// ���C�t��0����
	//	if (m_pLife->GetLife() < 0)
	//	{
	//		// �X�R�A�̔j��
	//		if (m_pScore != nullptr)
	//		{
	//			m_pScore->Uninit();
	//			m_pScore = nullptr;
	//		}

	//		// ���C�t�̔j��
	//		m_pLife->Uninit();
	//		m_pLife = nullptr;

	//		// �v���C���[�����S��Ԃɂ���
	//		m_bDie = true;

	//		// �T�C�Y�̎擾
	//		D3DXVECTOR2 size = GetSize();
	//		// �����̐���
	//		CExplosion::Create(CObject2D::GetPosition(), D3DXVECTOR2(size.x, size.y * 2));

	//		return;
	//	}

	//	// ����s�\�ɂ���
	//	m_bControl = false;
	//	// ���X�|�[����Ԃɂ���
	//	m_state = STATE_DIE;
	//	m_nCntState = 60;

	//	// �ϐ��̃��Z�b�g
	//	m_nTexRotType = TYPE_NEUTRAL;		//�A�j���[�V�����ԍ������Z�b�g����

	//										// �o���A�̔j��
	//	if (m_pBarrier != nullptr)
	//	{
	//		m_pBarrier->Uninit();
	//		m_pBarrier = nullptr;
	//	}

	//	// �I�v�V�����̔j��
	//	for (int nCnt = 0; nCnt < MAX_OPTION; nCnt++)
	//	{
	//		if (m_pOption[nCnt] != nullptr)
	//		{
	//			m_pOption[nCnt]->Uninit();
	//			m_pOption[nCnt] = nullptr;
	//		}
	//	}

	//	// �e������Ԃ�����������
	//	m_OptionLevel = CBulletOption::LEVEL_NONE;
	//	m_BarrierLevel = CBarrier::LEVEL_NONE;
	//	m_BulletLevel = CPlayer::LEVEL_1;

	//	// �T�C�Y�̎擾
	//	D3DXVECTOR2 size = GetSize();
	//	// �����̐���
	//	CExplosion::Create(CObject2D::GetPosition(), D3DXVECTOR2(size.x, size.y * 2));

	//	//�v���C���[�̈ʒu�����[�ɐݒ肷��
	//	if (m_nPlayerNum == PLAYER_1)
	//	{// 1P�̏ꍇ
	//		CObject2D::SetPosition(D3DXVECTOR3(-SIZE_X, CRenderer::SCREEN_HEIGHT / 2, 0.0f));
	//	}
	//	else
	//	{// 2P�̏ꍇ
	//		CObject2D::SetPosition(D3DXVECTOR3(-SIZE_X, CRenderer::SCREEN_HEIGHT / 2 + SIZE_Y, 0.0f));
	//	}

	//}
}
