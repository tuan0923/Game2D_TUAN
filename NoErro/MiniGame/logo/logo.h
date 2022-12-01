//-------------------------------------------
//
// ロゴの生成[logo.h]
// Author : Koshimoto　Manato
//
//-------------------------------------------
#ifndef _LOGO_H_
#define _LOGO_H_

//-------------------------------------------
// インクルード
//-------------------------------------------
#include "object2D.h"

//-------------------------------------------
// ロゴクラス
//-------------------------------------------
class CLogo : public CObject2D
{
public:
	enum LOGOTYPE
	{//ロゴの種類


	};

	// コンストラクタ
	CLogo();
	// デストラクタ
	~CLogo() override;

	// 生成
	static CLogo* Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const D3DXCOLOR& col, const char *aLogoname);
	// テクスチャの読み込み
	static HRESULT Load(const char *aLogoname);
	// テクスチャの削除
	static void Unload();

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
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LOGOTYPE  m_Logotype;
	// 破棄するまでのカウンター
	int m_nCountUninit;
	// 元のサイズ記憶用
	D3DXVECTOR2 m_DefaultSize;
};

#endif		// _LOGO_H_
