#include "player.h"
#include "application.h"
#include "input.h"
#include "bullet.h"

LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = nullptr;


CPlayer * CPlayer::Create()
{
	CPlayer *pPlayer;

	//�I�u�W�F�N�g�N���X�̐���
	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		pPlayer->Init();
	}

	return pPlayer;
}


CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player000.png", &m_pTexture);

	return S_OK;
}

void CPlayer::UnLoad()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

HRESULT CPlayer::Init()
{
	m_pos = D3DXVECTOR3(600.0f, 500.0f, 0);
	CObject2D::Init();

	CObject2D::BindTexture(m_pTexture);
	CObject2D::SetTex(1, 0);
	return S_OK;
}

void CPlayer::Uninit()
{
	CObject2D::Uninit();

}

void CPlayer::Update()
{

	if (CInputKeyboard::GetKeyboardPress(DIK_W) == true)
	{   // W�@�� ��������
		if (CInputKeyboard::GetKeyboardPress(DIK_D) == true)
		{ // �E��ړ�
			m_pos.x += sinf(D3DX_PI * 0.75f) * 6.0f;
			m_pos.y += cosf(-D3DX_PI * 0.75f) * 6.0f;
		}

		else if (CInputKeyboard::GetKeyboardPress(DIK_A) == true)
		{ // ����ړ�
			m_pos.x += sinf(-D3DX_PI * 0.75f)*6.0f;
			m_pos.y += cosf(-D3DX_PI * 0.75f)*6.0f;
		}

		else
		{ // ��ړ�
			m_pos.x += sinf(-D3DX_PI * 1.0f) *6.0f;
			m_pos.y += cosf(-D3DX_PI * 1.0f) *6.0f;
		}

	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_S) == true)
	{// S ����������
		if (CInputKeyboard::GetKeyboardPress(DIK_D) == true)
		{// �E���ړ�
			m_pos.x += sinf(D3DX_PI * 0.25f)*6.0f;
			m_pos.y += cosf(D3DX_PI * 0.25f)*6.0f;
		}

		else if (CInputKeyboard::GetKeyboardPress(DIK_A) == true)
		{//�����ړ�
			m_pos.x += sinf(-D3DX_PI * 0.25f)*6.0f;
			m_pos.y += cosf(D3DX_PI * 0.25f)*6.0f;
		}

		else
		{//���ړ�
			m_pos.x += sinf(D3DX_PI * 0.0f) * 6.0f;
			m_pos.y += cosf(D3DX_PI * 0.0f) * 6.0f;
		}
	}
	// D �̂�
	else if (CInputKeyboard::GetKeyboardPress(DIK_D) == true)
	{//�E�ړ�
		m_pos.x += sinf(D3DX_PI * 0.5f) * 6.0f;
		m_pos.y += cosf(D3DX_PI * 0.5f) * 6.0f;
	}
	// A �̂�
	else if (CInputKeyboard::GetKeyboardPress(DIK_A) == true)
	{//���ړ�
		m_pos.x += sinf(-D3DX_PI * 0.5f) * 6.0f;
		m_pos.y += cosf(D3DX_PI * 0.5f) * 6.0f;
	}
	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) == true)
	{//SPACE�L�[������
	 //�e�̐ݒ�
		D3DXVECTOR3 BulletMove = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
		CBullet *pBullet = nullptr;

		pBullet->Create()->SetBullet(m_pos, BulletMove);
	}
	

	//�ړ��ʍX�V�i�����j
	//m_pos.x += (0.0f - m_pos.x)*0.1f;
	//m_pos.y += (0.0f - m_pos.y)*0.1f;
	
	CObject2D::SetPosition(m_pos, D3DXVECTOR3(50.0f, 50.0f, 0));
}

void CPlayer::Draw()
{
	CObject2D::Draw();
	
}

void CPlayer::SetPlayer(D3DXVECTOR3 pos)
{
	m_pos = pos;
	
}

