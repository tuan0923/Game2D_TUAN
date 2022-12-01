//=============================================================================
//
// �|�[�Y��ʏ�� [pause.cpp]
// Author:SHUGO KURODA
//
//=============================================================================
#include "pause.h"
#include "game.h"
#include "fade.h"
#include "input_keyboard.h"
#include "sound.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "input_joypad.h"

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CPause::m_apTexture[TYPE_MAX] = {};
CObject2D *CPause::m_apObject2D[TYPE_MAX] = {};

//=============================================================================
// CBullet�̃R���X�g���N�^
//=============================================================================
CPause::CPause() :m_bPause(false), m_nPauseSelect(0), m_bWait(false), m_nNumPlayer(0)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetType(OBJ_PAUSE);
}

//=============================================================================
// CPlayer�̃f�X�g���N�^
//=============================================================================
CPause::~CPause()
{

}

//-----------------------------------------------------------------------------------------------
//	�e�N�X�`���ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CPause::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause000.jpg", &m_apTexture[TYPE_FRAME]);		// �|�[�Y��ʘg
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause001.png", &m_apTexture[TYPE_RESUME]);		// �ĊJ
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause002.png", &m_apTexture[TYPE_RESTART]);	// ��蒼��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause003.png", &m_apTexture[TYPE_EXIT]);		// �^�C�g���ɖ߂�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/option000.png", &m_apTexture[TYPE_SELECTOR]);	// �I���J�[�\��

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//	�e�N�X�`���j��
//-----------------------------------------------------------------------------------------------
void CPause::Unload()
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
// ��������
//=============================================================================
CPause *CPause::Create(int nNumPlayer)
{
	// �|�C���^�ϐ��̐���
	CPause *pPause = new CPause;

	// NULL�`�F�b�N
	if (pPause != nullptr)
	{
		// �|�[�Y���j���[���J�����v���C���[
		pPause->m_nNumPlayer = nNumPlayer;

		// ����������
		pPause->Init();
	}

	return pPause;
}

//=============================================================================
// �|�[�Y�̏���������
//=============================================================================
HRESULT CPause::Init()
{
	SetPause();

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{// ����
		m_apObject2D[nCnt] = new CObject2D;
		// �I�u�W�F�N�g�^�C�v�̐ݒ�
		m_apObject2D[nCnt]->SetType(OBJ_PAUSE_MENU);
	}
	m_apObject2D[TYPE_FRAME]->SetType(OBJ_PAUSE);

	// �X�N���[���T�C�Y�̕ۑ�
	D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	// 
	m_nPauseSelect = TYPE_RESUME;

	// �|�[�Y��ʘg
	m_apObject2D[TYPE_FRAME]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	m_apObject2D[TYPE_FRAME]->SetSize(D3DXVECTOR2(ScreenSize.x - 350.0f, ScreenSize.y - 200.0f));
	// �ĊJ
	m_apObject2D[TYPE_RESUME]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, 200.0f, 0.0f));
	m_apObject2D[TYPE_RESUME]->SetSize(D3DXVECTOR2(ScreenSize.x / 2, 80.0f));
	// ��蒼��
	m_apObject2D[TYPE_RESTART]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, 350.0f, 0.0f));
	m_apObject2D[TYPE_RESTART]->SetSize(D3DXVECTOR2(ScreenSize.x / 2, 80.0f));
	// �^�C�g���ɖ߂�
	m_apObject2D[TYPE_EXIT]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, 500.0f, 0.0f));
	m_apObject2D[TYPE_EXIT]->SetSize(D3DXVECTOR2(ScreenSize.x / 2, 80.0f));
	// �I���J�[�\��
	m_apObject2D[TYPE_SELECTOR]->SetPosition(D3DXVECTOR3((ScreenSize.x / 2)- 380.0f, 200.0f, 0.0f));
	m_apObject2D[TYPE_SELECTOR]->SetSize(D3DXVECTOR2(80.0f, 80.0f));

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{// �������ƃe�N�X�`���̐ݒ�
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	return S_OK;
}

//=============================================================================
// �|�[�Y�̏I������
//=============================================================================
void CPause::Uninit()
{
	// �|�[�Y��Ԃ�false�ɂ���
	CManager::GetManager()->SetPause(false);

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
	}

	// �I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
// �|�[�Y�̍X�V����
//=============================================================================
void CPause::Update()
{
	// �I���J�[�\���̊p�x�擾
	float fRot = m_apObject2D[TYPE_SELECTOR]->GetRot();
	// �p�x���Z
	fRot += 0.01f;
	// �p�x�̐ݒ�
	m_apObject2D[TYPE_SELECTOR]->SetRot(fRot);

	if (m_bPause == true)
	{
		// �L�[�{�[�h���̎擾
		CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
		// �Q�[���p�b�h���̎擾
		CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

		if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_UP) == true || pJoypad->GetTrigger(CInputJoypad::JOYKEY_UP, m_nNumPlayer) == true)
		{
			// ���ݑI������Ă��鍀�ڂ̐F�����ɖ߂�
			m_apObject2D[m_nPauseSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// ��ɂ����Ƃ��ԍ������炷
			m_nPauseSelect--;

			// �|�[�Y���ڂ̍ŏ㕔�𒴂����Ƃ�
			if (m_nPauseSelect < TYPE_RESUME)
			{
				m_nPauseSelect = TYPE_EXIT;
			}

			// �I������Ă���|�[�Y���ڂ̈ʒu���擾
			D3DXVECTOR3 pos = m_apObject2D[m_nPauseSelect]->GetPosition();
			// �I���J�[�\���̈ʒu�ݒ�
			m_apObject2D[TYPE_SELECTOR]->SetPosition(D3DXVECTOR3(pos.x - 380.0f, pos.y, pos.z));

			// ���ʉ�
			CSound::Play(CSound::SOUND_LABEL_SE_MENU_SELECT);
		}
		else if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_DOWN) || pJoypad->GetTrigger(CInputJoypad::JOYKEY_DOWN, m_nNumPlayer))
		{
			// ���ݑI������Ă��鍀�ڂ̐F�����ɖ߂�
			m_apObject2D[m_nPauseSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// ���ɂ����Ƃ��ԍ��𑝂₷
			m_nPauseSelect++;

			// �|�[�Y���ڂ̍ŉ����𒴂����Ƃ�
			if (m_nPauseSelect > TYPE_EXIT)
			{
				m_nPauseSelect = TYPE_RESUME;
			}

			// �I������Ă���|�[�Y���ڂ̈ʒu���擾
			D3DXVECTOR3 pos = m_apObject2D[m_nPauseSelect]->GetPosition();
			// �I���J�[�\���̈ʒu�ݒ�
			m_apObject2D[TYPE_SELECTOR]->SetPosition(D3DXVECTOR3(pos.x - 380.0f, pos.y, pos.z));

			// ���ʉ�
			CSound::Play(CSound::SOUND_LABEL_SE_MENU_SELECT);
		}

		// ���ݑI������Ă��鍀�ڂ͐F�����F�ɐݒ�
		m_apObject2D[m_nPauseSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

		if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_OK) || pJoypad->GetTrigger(CInputJoypad::JOYKEY_A, m_nNumPlayer))
		{
			// �I������Ă���UI���Q�Ƃ��A�ǂ̏��������邩����
			switch (m_nPauseSelect)
			{
				// �ĊJ�{�^��
			case TYPE_RESUME:
				// �|�[�Y�����
				SetPause();
				Uninit();
				return;
				// ���g���C�{�^��
			case TYPE_RESTART:
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME);
				Uninit();
				return;
				// �I���{�^��
			case TYPE_EXIT:
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);
				Uninit();
				return;
			default:
				break;
			}
		}

		// �|�[�Y��ʂ��I����
		if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_PAUSE) ||
			pJoypad->GetTrigger(CInputJoypad::JOYKEY_START, m_nNumPlayer))
		{
			if (m_bWait == true)
			{
				SetPause();
				Uninit();
				return;
			}
		}

		// ���_���W�̐ݒ�
		m_apObject2D[TYPE_SELECTOR]->SetVertex();

		m_bWait = true;
	}
}

//=============================================================================
// �|�[�Y�̕`�揈��
//=============================================================================
void CPause::Draw(void)
{

}

//=============================================================================
// �|�[�Y�̏���
//=============================================================================
void CPause::SetPause()
{
	m_bPause = m_bPause ? false : true;

	if (m_bPause == true)
	{
		CSound::Play(CSound::SOUND_LABEL_SE_MENU_IN);
	}
	else if (m_bPause == false)
	{
		CSound::Play(CSound::SOUND_LABEL_SE_MENU_OUT);
	}

	CManager::GetManager()->SetPause(m_bPause);
}
