//=============================================================================
//
// �����N���� [rank.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include "rank.h"

#include "manager.h"
#include "renderer.h"
#include "load.h"

#include "score.h"
#include "input_joypad.h"
#include "input_keyboard.h"
#include "sound.h"
#include "fade.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define SCORE_POS				(D3DXVECTOR3(470.0f,150.0f,0.0f))
#define PLAYER_SCORE_POS		(D3DXVECTOR3(220.0f,CRenderer::SCREEN_HEIGHT - 50.0f,0.0f))
#define SCORE_SIZE				(D3DXVECTOR2(70.0f,90.0f))
#define PLAYER_SCORE_SIZE		(D3DXVECTOR2(50.0f,60.0f))
#define SCORE_SPACE				(50)
#define PLAYER_SCORE_SPACE		(40)

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CRank::m_apTexture[TYPE_MAX] = {};
// �v���C���[�̃X�R�A
int CRank::m_nScorePlayer[MAX_PLAYER_SCORE] = { 0 };

//=============================================================================
// CRank�̃R���X�g���N�^
//=============================================================================
CRank::CRank() :m_pScore{ nullptr }, m_apObject2D{ nullptr }, m_aScore{ 0 }, m_bMyScoreFade{ 0 }, m_bNextMode(false)
{
	SetType(CObject::OBJ_UI);
}

//=============================================================================
// CRank�̃f�X�g���N�^
//=============================================================================
CRank::~CRank()
{
}

//=============================================================================
// ��������
//=============================================================================
CRank *CRank::Create()
{
	// �|�C���^�ϐ��̐���
	CRank *pRank = new CRank;

	// ����������
	pRank->Init();

	return pRank;
}

//-----------------------------------------------------------------------------------------------
//	�e�N�X�`���ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CRank::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/CustomBg001.jpg", &m_apTexture[TYPE_BG]);	// �w�i
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/rank000.png", &m_apTexture[TYPE_RANK]);	// �����L���OUI
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI001.png", &m_apTexture[TYPE_PLAYER1]);	// �v���C���[1
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/UI002.png", &m_apTexture[TYPE_PLAYER2]);	// �v���C���[2

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//	�e�N�X�`���j��
//-----------------------------------------------------------------------------------------------
void CRank::Unload()
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRank::Init()
{
	for (int nCnt = TYPE_BG; nCnt < TYPE_MAX; nCnt++)
	{// ����
		m_apObject2D[nCnt] = new CObject2D;
		m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f));
		m_apObject2D[nCnt]->SetSize(D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT));
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	//�I�u�W�F�N�g�̎�ސݒ�
	m_apObject2D[TYPE_BG]->SetType(EObject::OBJ_BG);
	m_apObject2D[TYPE_RANK]->SetType(EObject::OBJ_UI);

	// �X�R�A�̐���
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_pScore[nCnt] = CScore::Create(D3DXVECTOR3(SCORE_POS.x, SCORE_POS.y + (nCnt * 100.0f), SCORE_POS.z),
			SCORE_SIZE, SCORE_SPACE);
	}

	//// �v���C���[�X�R�A�̐���
	//for (int nCnt = 0; nCnt < MAX_PLAYER_SCORE; nCnt++)
	//{
	//	// �v���C���[ENTRY���̎擾
	//	bool bEntry = CManager::GetManager()->GetEntry(nCnt);

	//	// �G���g���[���Ă����
	//	if (bEntry == true)
	//	{// �v���C���[�X�R�A����
	//		m_pScore[nCnt + MAX_RANKING] = CScore::Create(D3DXVECTOR3(PLAYER_SCORE_POS.x + (nCnt * 650.0f), PLAYER_SCORE_POS.y, SCORE_POS.z),
	//			PLAYER_SCORE_SIZE, PLAYER_SCORE_SPACE);

	//		// �X�R�A�̐ݒ�
	//		m_aScore[nCnt + MAX_RANKING] = m_nScorePlayer[nCnt];

	//		// UI�̐���
	//		m_apObject2D[nCnt] = new CObject2D;
	//		m_apObject2D[nCnt]->SetType(EObject::OBJ_UI);
	//		m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(100.0f + (nCnt * 650.0f), CRenderer::SCREEN_HEIGHT - 50.0f, 0.0f));
	//		m_apObject2D[nCnt]->SetSize(D3DXVECTOR2(200.0f, 100.0f));
	//		m_apObject2D[nCnt]->Init();
	//		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	//	}
	//}

	// �e�L�X�g����X�R�A�����[�h
	int *pScore = LoadSpace::LoadScore();

	// �X�R�A�����i�[
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_aScore[nCnt] = pScore[nCnt];
	}

	//�����L���O�̍X�V
	int nData = 0;
	for (int nCnt1 = 0; nCnt1 < MAX_RANKING; nCnt1++)
	{
		for (int nCnt2 = (nCnt1 + 1); nCnt2 < MAX_RANKING + MAX_PLAYER_SCORE; nCnt2++)
		{
			if (m_aScore[nCnt1] <= m_aScore[nCnt2])
			{
				nData = m_aScore[nCnt2];
				m_aScore[nCnt2] = m_aScore[nCnt1];
				m_aScore[nCnt1] = nData;
			}
		}
	}

	m_aScore[5] = m_nScorePlayer[0];
	m_aScore[6] = m_nScorePlayer[1];

	// �e�L�X�g�ɃX�R�A���Z�[�u
	LoadSpace::SaveScore(&m_aScore[0]);

	// Top3�̃X�R�A�F��ݒ�
	m_pScore[0]->SetColor(D3DXCOLOR(0.8f, 0.8f, 0.1f, 1.0f));
	m_pScore[1]->SetColor(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
	m_pScore[2]->SetColor(D3DXCOLOR(0.8f, 0.6f, 0.3f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRank::Uninit()
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRank::Update()
{
	// �e�N�X�`���̒��_���W��ύX
	m_apObject2D[TYPE_BG]->SetAnimBgLeftUp(1, 400, true);

	// �L�[�{�[�h���̎擾
	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	// �Q�[���p�b�h���̎擾
	CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	for (int nCnt = CInputKeyboard::KEYINFO_OK; nCnt < CInputKeyboard::KEYINFO_MAX; nCnt++)
	{
		// �L�[�{�[�h��ENTRY����
		if (pKeyboard->GetTrigger(nCnt))
		{
			for (int nCnt = 0; nCnt < MAX_RANKING + MAX_PLAYER_SCORE; nCnt++)
			{
				if (m_pScore[nCnt] != nullptr)
				{// �X�R�A�ݒ�
					if (m_aScore[nCnt] > m_pScore[nCnt]->GetScore())
					{
						m_pScore[nCnt]->Set(m_aScore[nCnt]);
					}
				}
			}

			if (m_bNextMode == true)
			{
				// ���艹
				CSound::Play(CSound::SOUND_LABEL_SE_MENU_OK);

				// ���[�h�̐ݒ�
				CManager::GetManager()->GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_TITLE);
				return;
			}

			m_bNextMode = true;
			break;
		}
	}

	// �v���C���[�̃G���g���[����
	for (int nCntController = 0; nCntController < CPlayer::PLAYER_MAX; nCntController++)
	{
		for (int nCnt = CInputJoypad::JOYKEY_UP; nCnt < CInputJoypad::JOYKEY_MAX; nCnt++)
		{
			if (pJoypad->GetTrigger((CInputJoypad::JOYKEY)nCnt, nCntController))
			{
				// ���艹
				CSound::Play(CSound::SOUND_LABEL_SE_MENU_OK);

				for (int nCnt = 0; nCnt < MAX_RANKING + MAX_PLAYER_SCORE; nCnt++)
				{
					if (m_pScore[nCnt] != nullptr)
					{// �X�R�A�ݒ�
						if (m_aScore[nCnt] > m_pScore[nCnt]->GetScore())
						{
							m_pScore[nCnt]->Set(m_aScore[nCnt]);
						}
					}
				}

				if (m_bNextMode == true)
				{
					// ���[�h�̐ݒ�
					CManager::GetManager()->GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_TITLE);
					return;
				}

				m_bNextMode = true;
				break;
			}
		}
	}

	// �X�R�A�����i�[
	for (int nCnt = 0; nCnt < MAX_RANKING + MAX_PLAYER_SCORE; nCnt++)
	{
		if (m_pScore[nCnt] != nullptr)
		{// ���b�X�R�A���Z
			if (m_aScore[nCnt] > m_pScore[nCnt]->GetScore())
			{
				m_pScore[nCnt]->Add(200);
			}
			else if (m_nScorePlayer[0] == m_pScore[nCnt]->GetScore() ||
				m_nScorePlayer[1] == m_pScore[nCnt]->GetScore())
			{
				// PRESS���S�̐F���擾
				D3DXCOLOR col = m_pScore[nCnt]->GetColor();

				// PRESS���S��_�ł�����
				if (m_bMyScoreFade[nCnt] == false)
				{
					// a�l�����Z
					col.a += 0.02f;
					// a�l�̉��Z���I�������
					if (col.a >= 1.0f)
					{// a�l�̌��Z���n�߂�
						m_bMyScoreFade[nCnt] = true;
					}
				}
				else if (m_bMyScoreFade[nCnt] == true)
				{
					// a�l�����Z
					col.a -= 0.02f;
					// a�l�̌��Z���I�������
					if (col.a <= 0.0f)
					{// a�l�̉��Z���n�߂�
						m_bMyScoreFade[nCnt] = false;
					}
				}

				// �F�̐ݒ�
				m_pScore[nCnt]->SetColor(col);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRank::Draw()
{
}
