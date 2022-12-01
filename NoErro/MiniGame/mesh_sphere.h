//=============================================================================
//
//	メッシュ(球)処理 [mesh_sphere.h]
//	Author : SHUGO KURODA
//
//=============================================================================
#ifndef _MESH_SPHERE_H_			//このマクロ定義がされなかったら
#define _MESH_SPHERE_H_			//2重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
//	インクルードファイル
//-----------------------------------------------------------------------------
#include "object.h"

//-------------------------------------------
// ロゴクラス
//-------------------------------------------
class CMeshSphere : public CObject
{
public:
	// コンストラクタ
	CMeshSphere();
	// デストラクタ
	~CMeshSphere() override;

	// 生成
	static CMeshSphere *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXCOLOR& col, const D3DXVECTOR2& rad, const int& nMeshX, const int& nMeshZ, const char* name);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// テクスチャのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 向き
	D3DXCOLOR m_col;		// カラー
	D3DXVECTOR2 m_rad;		// 各横縦幅
	int m_nMeshX;
	int m_nMeshZ;			// 縦横のメッシュ化の数
	int m_nPolygon;			// ポリゴン数
	int m_nTop;				// 頂点
	int m_nIdx;				// インデックス数
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
};

#endif		// _MESH_SPHERE_H_
