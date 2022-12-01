#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//=================================
//インクルード
//=================================
#include "main.h"
#include "object.h"
#include "renderer.h"

//=================================
//object　クラス
//=================================
class CObject2D : public CObject
{
public:
	CObject2D();
	~CObject2D() override;

	 HRESULT Init() override;
	 void Uninit() override;
	 void Update() override;
	 void Draw() override;
	 D3DXVECTOR3 GetPos() override;

	 static CObject2D *Create();
	 void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	 void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	 void SetTex(int MaxTexture, int inPatternAnim);
	
	
private:

	//頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff;

	LPDIRECT3DTEXTURE9 m_Texture;

	D3DXVECTOR3 m_pos;
	float       g_Rot;
	static CObject2D* m_pObject2D[MAX_OBJECT];

};
// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;

	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;	//テクスチャ座標
};
// 頂点フォーマット
static const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

#endif // !_OBJECT_H_
