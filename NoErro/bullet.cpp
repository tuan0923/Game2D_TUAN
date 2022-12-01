#include "bullet.h"
#include "application.h"
#include "explosion.h"
#include "object.h"

 LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

CBullet::CBullet()
{
	m_Life = 50;
}

CBullet::~CBullet()
{
}

HRESULT CBullet::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &m_pTexture);

	return S_OK;
}

void CBullet::UnLoad()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}
HRESULT CBullet::Init()
{
	CObject2D::Init();
	CObject2D::BindTexture(m_pTexture);
	CObject2D::SetTex(1, 0);
	return S_OK;
}

void CBullet::Uninit()
{
	CObject2D::Uninit();
	
}

void CBullet::Update()
{

	CExplosion *pExplosion;
	m_pos += m_move;
	m_Life--;
	CObject2D::SetPosition(m_pos, D3DXVECTOR3(10.0f, 10.0f, 0));
	if (m_Life <= 0)
	{
		//爆発の生成
		pExplosion->Create()->SetPosition(m_pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		this->Uninit();
	}
	else
	{
		CObject2D::SetPosition(m_pos, D3DXVECTOR3(10.0f, 10.0f, 0));
	}
//==========================================================
//当たり判定
//==========================================================
	CObject **pObject;
	CObject::EObjectType nType;
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		
		pObject = CObject::GetObject();
		if (pObject[nCntObject] != nullptr)
		{
			
			nType = pObject[nCntObject]->GetObjectType();
			if (nType == CObject::OBJECT_ENEMY)
			{

 				D3DXVECTOR3 Object_pos = pObject[nCntObject]->GetPos();
				if (   m_pos.x >= Object_pos.x - 25.0f
					&& m_pos.x <= Object_pos.x + 25.0f
					&& m_pos.y >= Object_pos.y - 25.0f
					&& m_pos.y <= Object_pos.y + 25.0f)
				{

					pExplosion->Create()->SetPosition(m_pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));
					this->Uninit();
				}
			}
		}
	}
}

void CBullet::Draw()
{
	CObject2D::Draw();
}

void CBullet::SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}

//==========================================================
//当たり判定
//==========================================================

CBullet * CBullet::Create()
{
	CBullet *pBullet = nullptr;
	pBullet = new CBullet;
	if (pBullet != nullptr)
	{
		pBullet->Init();
		pBullet->SetObjectType(CObject::OBJECT_BULLET);
	}
	return pBullet;
}
