#include "player.h"
#include "application.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"

LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = nullptr;


CEnemy * CEnemy::Create()
{
	CEnemy *pEnemy;

	//オブジェクトクラスの生成
	pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{
		pEnemy->Init();
		pEnemy->SetObjectType(CObject::OBJECT_ENEMY);
	}

	return pEnemy;
}


CEnemy::CEnemy()
{
	m_Life = 100;
	m_pos = D3DXVECTOR3(600.0f, 400.0f, 0.0f);
}

CEnemy::~CEnemy()
{
}

HRESULT CEnemy::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy000.png", &m_pTexture);

	return S_OK;
}

void CEnemy::UnLoad()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

HRESULT CEnemy::Init()
{
	
	CObject2D::Init();
	Enemy_Move = D3DXVECTOR3(0.10f, 0.0f, 0);

	BindTexture(m_pTexture);
	SetTex(1, 0);
	
	return S_OK;
}

void CEnemy::Uninit()
{
	CObject2D::Uninit();

}

void CEnemy::Update()
{
	m_pos.x += Enemy_Move.x;
	
	CObject2D::Update();
}

void CEnemy::Draw()
{
	CObject2D::Draw();

}

void CEnemy::HitEnemy(int nDamage)
{
	
}

