//*****************************************************************************
// インクルード
//*****************************************************************************

#include "application.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
//#include "effect.h"
//グローバル変数

CRenderer *CApplication::m_pRenderer = nullptr;
CInputKeyboard *CApplication::m_pInputKeyboard = nullptr;


CApplication::CApplication()
{
}

CApplication::~CApplication()
{
}

HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_pRenderer = new CRenderer;

	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}

	m_pInputKeyboard = new CInputKeyboard;\

	//キーボードの初期化処理
	if (FAILED(m_pInputKeyboard->InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	LoadAll();

	CEnemy* pEnemy = CEnemy::Create();
	//pEnemy = CEnemy::Create();
	CPlayer::Create();

	return S_OK;
}

void CApplication::Uninit(void)
{

	//レンダリングクラスの破棄
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->UninitKeyboard();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	UnLoadAll();

	//オブジェクトの破棄
	CObject::ReleaseAll();
}

void CApplication::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

void CApplication::Update(void)
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->UpdateKeyboard();
	}
}

void CApplication::LoadAll(void)
{
	CPlayer::Load();

	CBullet::Load();

	CExplosion::Load();

	CEnemy::Load();
	//CEffect::Load();
}

void CApplication::UnLoadAll(void)
{
	CPlayer::UnLoad();

	CBullet::UnLoad();

	CExplosion::UnLoad();

	CEnemy::UnLoad();

	//CEffect::UnLoad();
}

CRenderer * CApplication::GetRenderer()
{
	return m_pRenderer;
}

CInputKeyboard * CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}






