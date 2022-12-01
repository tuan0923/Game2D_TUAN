#include "player.h"
#include "application.h"
#include "input.h"
#include "bullet.h"

LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = nullptr;


CPlayer * CPlayer::Create()
{
	CPlayer *pPlayer;

	//オブジェクトクラスの生成
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
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
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
	{   // W　を 押したら
		if (CInputKeyboard::GetKeyboardPress(DIK_D) == true)
		{ // 右上移動
			m_pos.x += sinf(D3DX_PI * 0.75f) * 6.0f;
			m_pos.y += cosf(-D3DX_PI * 0.75f) * 6.0f;
		}

		else if (CInputKeyboard::GetKeyboardPress(DIK_A) == true)
		{ // 左上移動
			m_pos.x += sinf(-D3DX_PI * 0.75f)*6.0f;
			m_pos.y += cosf(-D3DX_PI * 0.75f)*6.0f;
		}

		else
		{ // 上移動
			m_pos.x += sinf(-D3DX_PI * 1.0f) *6.0f;
			m_pos.y += cosf(-D3DX_PI * 1.0f) *6.0f;
		}

	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_S) == true)
	{// S を押したら
		if (CInputKeyboard::GetKeyboardPress(DIK_D) == true)
		{// 右下移動
			m_pos.x += sinf(D3DX_PI * 0.25f)*6.0f;
			m_pos.y += cosf(D3DX_PI * 0.25f)*6.0f;
		}

		else if (CInputKeyboard::GetKeyboardPress(DIK_A) == true)
		{//左下移動
			m_pos.x += sinf(-D3DX_PI * 0.25f)*6.0f;
			m_pos.y += cosf(D3DX_PI * 0.25f)*6.0f;
		}

		else
		{//下移動
			m_pos.x += sinf(D3DX_PI * 0.0f) * 6.0f;
			m_pos.y += cosf(D3DX_PI * 0.0f) * 6.0f;
		}
	}
	// D のみ
	else if (CInputKeyboard::GetKeyboardPress(DIK_D) == true)
	{//右移動
		m_pos.x += sinf(D3DX_PI * 0.5f) * 6.0f;
		m_pos.y += cosf(D3DX_PI * 0.5f) * 6.0f;
	}
	// A のみ
	else if (CInputKeyboard::GetKeyboardPress(DIK_A) == true)
	{//左移動
		m_pos.x += sinf(-D3DX_PI * 0.5f) * 6.0f;
		m_pos.y += cosf(D3DX_PI * 0.5f) * 6.0f;
	}
	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) == true)
	{//SPACEキーを押す
	 //弾の設定
		D3DXVECTOR3 BulletMove = D3DXVECTOR3(0.0f, -10.0f, 0.0f);
		CBullet *pBullet = nullptr;

		pBullet->Create()->SetBullet(m_pos, BulletMove);
	}
	

	//移動量更新（減衰）
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

