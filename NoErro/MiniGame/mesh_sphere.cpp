//=============================================================================
//
// メッシュ(球)処理 [mesh_sphere.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "object3D.h"

#include "mesh_sphere.h"
#include "texture.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define CYLINDER_MAX		(256)		//球体の最大数

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CMeshSphere::CMeshSphere() :m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pIdxBuff(nullptr), m_pos(0.0f, 0.0f, 0.0f),
							m_rot(0.0f, 0.0f, 0.0f), m_col(0.0f, 0.0f, 0.0f, 0.0f), m_rad(0.0f, 0.0f), m_nMeshX(0), m_nMeshZ(0)
{
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CMeshSphere::~CMeshSphere()
{
}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CMeshSphere* CMeshSphere::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXCOLOR& col, const D3DXVECTOR2& rad, const int& nMeshX, const int& nMeshZ, const char* name)
{
	// 生成
	CMeshSphere* pMeshSphere = new CMeshSphere;

	// 構造体を使用状態にする
	pMeshSphere->m_pos = pos;
	pMeshSphere->m_rot = rot;
	pMeshSphere->m_col = col;
	pMeshSphere->m_rad = rad;
	pMeshSphere->m_nMeshX = nMeshX;
	pMeshSphere->m_nMeshZ = nMeshZ;
	pMeshSphere->m_pTexture = CManager::GetManager()->GetTexture()->GetTexture(name);

	// 初期化
	pMeshSphere->Init();

	return pMeshSphere;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CMeshSphere::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// 頂点数の計算
	m_nTop = (m_nMeshX + 1) * (m_nMeshZ + 1);
	// インデックス数の計算
	m_nIdx = (m_nMeshX + 1) * 2 * m_nMeshZ + (m_nMeshZ - 1) * 2;
	// ポリゴン数の計算
	m_nPolygon = m_nMeshX * m_nMeshZ * 2 + (m_nMeshZ - 1) * 4;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(CObject3D::VERTEX_3D) * 4 * m_nTop,	// 確保する頂点の数
		D3DUSAGE_WRITEONLY,
		CObject3D::FVF_VERTEX_3D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点のインデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 4 * m_nIdx,	// 確保する頂点の数
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,						// 頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	CObject3D::VERTEX_3D *pVtx = NULL;		// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ <= m_nMeshZ; nCntZ++)
	{
		float fData = m_rad.y * cosf((D3DX_PI / m_nMeshZ * nCntZ) - D3DX_PI / 2);

		for (int nCntX = 0; nCntX <= m_nMeshX; nCntX++)
		{
			pVtx[0].pos.x = fData * sinf(D3DX_PI * 2 / m_nMeshX * nCntX);
			pVtx[0].pos.y = m_rad.y * sinf((D3DX_PI / m_nMeshZ  * nCntZ) - D3DX_PI / 2);
			pVtx[0].pos.z = fData * cosf(D3DX_PI * 2 / m_nMeshX * nCntX);

			// 各頂点の法線の設定（ベクトルの大きさは１にする必要がある）
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = m_col;

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2((1.0f / m_nMeshX) * nCntX, (1.0f / m_nMeshZ) * nCntZ);

			// データを1つ分進める
			pVtx++;
		}
	}

	// インデックス情報へのポインタ
	WORD* pIdx;

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntZ = 0; nCntZ <= m_nMeshZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_nMeshX; nCntX++)
		{
			//インデックスの設定
			pIdx[0] = (WORD)(nCntX + (m_nMeshX + 1) * (nCntZ + 1));
			pIdx[1] = (WORD)(nCntX + (m_nMeshX + 1) * nCntZ);
			pIdx += 2;		//インデックスのデータを２すすめる
		}

		if (nCntZ < m_nMeshZ - 1)
		{
			//インデックスの設定
			pIdx[0] = pIdx[-1];
			pIdx[1] = (WORD)((m_nMeshX + 1) * (nCntZ + 2));
			pIdx += 2;		//インデックスのデータを２すすめる
		}
	}

	//インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 破棄
//-----------------------------------------------------------------------------------------------
void CMeshSphere::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//インデックスバッファの破棄
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CMeshSphere::Update()
{
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CMeshSphere::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//カリングOFF
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject3D::VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(CObject3D::FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,					// 描画する最初の頂点インデックス
		0,					// インデックスの最小値
		m_nTop,				// 頂点の数
		0,					// インデックスの最初の数
		m_nPolygon);		// プリミティブ（ポリゴン）数

	//カリングを元に戻す(ON)
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
