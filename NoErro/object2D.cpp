//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object2D.h"
#include "application.h"
#include "input.h"

CObject2D *CObject2D::m_pObject2D[MAX_OBJECT] = {};

CObject2D * CObject2D::Create()
{

	CObject2D *pObject2D;

	//�I�u�W�F�N�g�N���X�̐���
	pObject2D = new CObject2D;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
	}

	return pObject2D;
}

CObject2D::CObject2D()
{
	g_pVtxBuff = NULL;
	
}

CObject2D::~CObject2D()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CObject2D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	g_Rot = 0.0f; 

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - OBJECT2D_SIZE_X, m_pos.y - OBJECT2D_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + OBJECT2D_SIZE_X, m_pos.y - OBJECT2D_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - OBJECT2D_SIZE_X, m_pos.y + OBJECT2D_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + OBJECT2D_SIZE_X, m_pos.y + OBJECT2D_SIZE_Y, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		////�e�N�X�`�����W�̐ݒ�
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuff->Unlock();

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void CObject2D::Uninit()
{
	
	if (g_pVtxBuff != NULL)
	{
		g_pVtxBuff->Release();
		g_pVtxBuff = NULL;
	}
	release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObject2D::Update()
{
	//VERTEX_2D *pVtx;	//���_���̃|�C���^
	//
	//
	//g_Rot -= 0.03f;

	//g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W�ݒ�
	//pVtx[0].pos = D3DXVECTOR3((m_pos.x + (sinf(g_Rot + D3DX_PI * 0.25f + D3DX_PI * 0.75f)* OBJECT2D_SIZE_X)),
	//	                       m_pos.y + (cosf(g_Rot + D3DX_PI * 0.25f + D3DX_PI * 0.75f)* OBJECT2D_SIZE_X), 0.0f);

	//pVtx[1].pos = D3DXVECTOR3((m_pos.x + (sinf(g_Rot + D3DX_PI * 0.25f + D3DX_PI * 0.25f)* OBJECT2D_SIZE_X)), 
	//	                       m_pos.y + (cosf(g_Rot + D3DX_PI * 0.25f + D3DX_PI * 0.25f)* OBJECT2D_SIZE_X), 0.0f);

	//pVtx[2].pos = D3DXVECTOR3((m_pos.x + (sinf(g_Rot + D3DX_PI * 0.25f + D3DX_PI * -0.75f)* OBJECT2D_SIZE_X)),
	//	                       m_pos.y + (cosf(g_Rot + D3DX_PI * 0.25f + D3DX_PI * -0.75f)* OBJECT2D_SIZE_X), 0.0f);

	//pVtx[3].pos = D3DXVECTOR3((m_pos.x + (sinf(g_Rot + D3DX_PI * 0.25f + D3DX_PI * -0.25f)* OBJECT2D_SIZE_X)), 
	//	                       m_pos.y + (cosf(g_Rot + D3DX_PI * 0.25f + D3DX_PI * -0.25f)* OBJECT2D_SIZE_X), 0.0f);

	////�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//
	//g_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObject2D::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, m_Texture);

	// �|���S���̕`��
  	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}


void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_Texture = pTexture;
}

void CObject2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	VERTEX_2D *pVtx;
	
	m_pos = pos;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	//���_���W���A�����b�N
	g_pVtxBuff->Unlock();
}


void CObject2D::SetTex(int MaxTexture, int inPatternAnim)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float nTest = 0 / MaxTexture;
	float nTest2 = (1 / (float)MaxTexture);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2((0 / (float)MaxTexture) + ((1 / (float)MaxTexture) * inPatternAnim), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1 / (float)MaxTexture) + ((1 / (float)MaxTexture) * inPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((0 / (float)MaxTexture) + ((1 / (float)MaxTexture) * inPatternAnim), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1 / (float)MaxTexture) + ((1 / (float)MaxTexture) * inPatternAnim), 1.0f);

	//���_���W���A�����b�N
  	g_pVtxBuff->Unlock();
}

D3DXVECTOR3 CObject2D::GetPos()
{
	return m_pos;
}