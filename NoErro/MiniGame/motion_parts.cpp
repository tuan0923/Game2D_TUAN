//===================================================================
//
//	モデル処理[model.cpp]
//	Author:SHUGO KURODA
//
//===================================================================

//======================================================
//	インクルード
//======================================================
#include "manager.h"
#include "renderer.h"
#include "model.h"

#include "input.h"
#include "camera.h"
//#include "shadow.h"
#include "bullet.h"
#include "load.h"
#include "enemy.h"

// 追加
#include "motion_parts.h"

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
CParts::CParts() :m_pos(0.0f, 0.0f, 0.0f), m_baseRot(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f),
				m_nIndex(0), m_nParent(0)
{
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CParts::~CParts()
{
}

//-----------------------------------------------------------------------------
// 生成
// const char* pas → 生成するパーツ(種類)
//-----------------------------------------------------------------------------
CParts* CParts::Create(const char* pas)
{
	//インスタンス生成
	CParts *pModel = new CParts;

	//デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//Xファイルの読み込み
	HRESULT hr = D3DXLoadMeshFromX(pas,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&pModel->m_aXFile.pBuffMat,
		NULL,
		&pModel->m_aXFile.nNumMat,
		&pModel->m_aXFile.pMesh);

	if (hr != S_OK)
	{//Xファイル読み込み失敗
		return nullptr;
	}

	// テクスチャの読み込み処理
	pModel->LoadXFileTexture();

	// 初期化
	pModel->Init();

	return pModel;
}

//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
HRESULT CParts::Init()
{
	//int nNumVix;		//頂点数
	//DWORD sizeFVF;	//頂点フォーマットのサイズ
	//BYTE *pVtxBuff;	//頂点バッファへのポインタ

	////頂点数の取得
	//nNumVix = m_aXFile.pMesh->GetNumVertices();

	////頂点フォーマット取得
	//sizeFVF = D3DXGetFVFVertexSize(m_aXFile.pMesh->GetFVF());

	////頂点ロック
	//m_aXFile.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	////すべての頂点POSの取得
	//for (int nCntVtx = 0; nCntVtx < nNumVix; nCntVtx++)
	//{
	//	//頂点座標の代入
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

	//	if (m_vtxMax.x < vtx.x)
	//	{//X
	//		m_vtxMax.x = vtx.x;
	//	}
	//	else if (m_vtxMin.x > vtx.x)
	//	{
	//		m_vtxMin.x = vtx.x;
	//	}

	//	if (m_vtxMax.y < vtx.y)
	//	{//Y
	//		m_vtxMax.y = vtx.y;
	//	}
	//	else if (m_vtxMin.y > vtx.y)
	//	{
	//		m_vtxMin.y = vtx.y;
	//	}

	//	if (m_vtxMax.z < vtx.z)
	//	{//Z
	//		m_vtxMax.z = vtx.z;
	//	}
	//	else if (m_vtxMin.z > vtx.z)
	//	{
	//		m_vtxMin.z = vtx.z;
	//	}

	//	//頂点フォーマットのサイズ分ポインタを進める
	//	pVtxBuff += sizeFVF;
	//}

	////ラインを配置
	////SetLine(g_Model[nCnt].pos, g_Model[nCnt].vtxMax, g_Model[nCnt].vtxMin, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	////頂点アンロック
	//m_aXFile.pMesh->UnlockVertexBuffer();

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------
void CParts::Uninit()
{
	Release();
}

//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
void CParts::Update()
{
	//for (int nCntVtx = 0; nCntVtx < MAX_MODEL_TYPE; nCntVtx++)
	//{
	//	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	//	{
	//		//前回の位置を保存
	//		g_aModel[nCnt].posOld = g_aModel[nCnt].pos;

	//		//当たり判定
	//		//CollisionPlayer(&g_aModel[nCnt].pos, &g_aModel[nCnt].posOld, &g_aModel[nCnt].Airmove, g_aModel[nCnt].fWidth, g_aModel[nCnt].fHeight);
	//	}
	//}
}

//-----------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------
void CParts::Draw()
{
	////デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	//D3DMATERIAL9 matDef;			// 現在のマテリアル保存用
	//D3DXMATERIAL *pMat;			// マテリアルデータへのポインタ

	////ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&m_mtxWorld);

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	//// ワールドマトリックスの計算
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	////位置を反映
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	//// ワールドマトリックスの計算
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	////ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	////現在のマテリアルを保持
	//pDevice->GetMaterial(&matDef);

	////マテリアルデータへのポインタを取得
	//pMat = (D3DXMATERIAL*)m_aXFile.pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)m_aXFile.nNumMat; nCntMat++)
	//{
	//	//マテリアルの設定
	//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

	//	//テクスチャの設定
	//	pDevice->SetTexture(0, m_aXFile.pTexture[nCntMat]);

	//	//モデルパーツの描画
	//	m_aXFile.pMesh->DrawSubset(nCntMat);

	//	//テクスチャの設定を元に戻す
	//	pDevice->SetTexture(0, NULL);
	//}

	////保持していたマテリアルを戻す
	//pDevice->SetMaterial(&matDef);
}

//-----------------------------------------------------------------------------
// テクスチャの読み込み
//-----------------------------------------------------------------------------
void CParts::LoadXFileTexture()
{
	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_aXFile.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_aXFile.nNumMat; nCntMat++)
	{
		//マテリアルの設定
		//pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャがあった場合
		if ((pMat[nCntMat].pTextureFilename != NULL) && (strcmp(pMat[nCntMat].pTextureFilename, "") != 0))
		{
			//デバイスを取得する
			LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_aXFile.pTexture[nCntMat]);
		}
	}
}
