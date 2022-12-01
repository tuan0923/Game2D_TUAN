#include "explosion.h"
#include "application.h"

LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = nullptr;

CExplosion::CExplosion()
{
	
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

CExplosion::~CExplosion()
{
}

HRESULT CExplosion::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion000.png", &m_pTexture);

	return S_OK;
}

void CExplosion::UnLoad()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

HRESULT CExplosion::Init()
{
	

	CObject2D::Init();
	CObject2D::BindTexture(m_pTexture);
	CObject2D::SetTex(8, 0);
	return S_OK;
}

void CExplosion::Uninit()
{
	
	CObject2D::Uninit();
	
}

void CExplosion::Update()
{
	if (m_pTexture != nullptr)
	{
		//�e�N�X�`���̃A�j���[�V����
		m_nCounterAnim++;

		if (m_nCounterAnim % 8 == 0)
		{
			m_nPatternAnim++;
			CObject2D::SetTex(8, m_nPatternAnim);
			if (m_nPatternAnim > 8)
			{
				Uninit();
				
			}
		}
	}

}

void CExplosion::Draw()
{
	CObject2D::Draw();
}

CExplosion * CExplosion::Create()
{
	CExplosion *pExplosion;

	//�����̐���
	pExplosion = new CExplosion;

	if (pExplosion != nullptr)
	{
		pExplosion->Init();
	}
	return pExplosion;

}
