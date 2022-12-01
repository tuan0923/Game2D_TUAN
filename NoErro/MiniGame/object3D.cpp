//===================================================================
//
//	3Dポリゴン処理 [object3D.cpp]
//	Author:SHUGO KURODA
//
//===================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"

#include "object3D.h"

//======================================================
//	コンストラクタ
//======================================================
CObject3D::CObject3D() : m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pos(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f)
{
}

//======================================================
//	デストラクタ
//======================================================
CObject3D::~CObject3D()
{
}

//======================================================
//	生成処理
//======================================================
CObject3D *CObject3D::Create(const D3DXVECTOR3& pos)
{
	//インスタンス生成
	CObject3D *pObject3D = new CObject3D;
	
	// 位置設定
	pObject3D->SetPosition(pos);

	// 初期化
	pObject3D->Init();

	// テクスチャの割り当て
	pObject3D->BindTexture(CManager::GetManager()->GetTexture()->GetTexture("TEX_TYPE_TITLE_FLOOR"));

	return pObject3D;
}

//======================================================
//	初期化処理
//======================================================
HRESULT CObject3D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg000_11.jpg", &m_pTexture);

	VERTEX_3D *pVtx = nullptr;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (POLYGON_SIZE / 2), m_pos.y, m_pos.z + (POLYGON_SIZE / 2));
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (POLYGON_SIZE / 2), m_pos.y, m_pos.z + (POLYGON_SIZE / 2));
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (POLYGON_SIZE / 2), m_pos.y, m_pos.z - (POLYGON_SIZE / 2));
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (POLYGON_SIZE / 2), m_pos.y, m_pos.z - (POLYGON_SIZE / 2));

	//各頂点の法線の設定(ベクトルの大きさは１にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//======================================================
//	終了処理
//======================================================
void CObject3D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//======================================================
//	更新処理
//======================================================
void CObject3D::Update()
{
}

//======================================================
//	描画処理
//======================================================
void CObject3D::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,			//描画する最初の頂点インデックス
		2);			//プリミティブ（ポリゴン）数
}
