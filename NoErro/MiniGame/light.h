//===================================================================
//
//		ライト処理のヘッダー[light.h]
//		Author:黒田 周吾
//
//===================================================================
#ifndef _LIGHT_H_			//このマクロ定義がされなかったら
#define _LIGHT_H_			//2重インクルード防止のマクロ定義

#include "object.h"

//======================================================
//	プロトタイプ宣言
//======================================================
class CLight : public CObject
{
public:
	CLight();
	~CLight() override;

	static CLight *Create(const D3DXVECTOR3& vecDir, const D3DXCOLOR& diffuse);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	D3DLIGHT9 m_aLight;			//ライト情報
	D3DXVECTOR3 m_vecDir;		//ライトの方向ベクトル
	D3DXCOLOR m_Diffuse;		//ライトの拡散光
	static int m_nNumLight;		//ライトの数
};

#endif