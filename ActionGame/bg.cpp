//========================================================
// bg.cpp
// 2DGame
//Author: テュアン
//========================================================
#include "main.h"
#include "bg.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBG = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;//頂点バッファへのポインタ
int g_nCounterAnimBG;					//アニメーションカウンター
int g_nPatternAnimBG;					//アニメーションパターンNo.
float g_fBG;
//================================================
//背景の初期化処理
//================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

									//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg07.png",
		&g_pTextureBG);

	g_nCounterAnimBG = 0;		//カウンターを初期化
	g_nPatternAnimBG = 0;		//パターンNo.を初期化
	g_fBG = 0.01f;
								//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.7f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.7f);

	//頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();
}
//================================================
//背景の終了処理
//================================================
void UninitBG(void)
{
	//テクスチャの破棄
	if (g_pTextureBG != NULL)
	{
		g_pTextureBG->Release();
		g_pTextureBG = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}
//================================================
//背景の更新処理
//================================================
void UpdateBG(void)
{
	VERTEX_2D *pVtx2;		//頂点情報へのポインタ
	g_nCounterAnimBG++;		//カウンターを加算
	g_fBG += 0.0001f;
				//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx2, 0);

		// テクスチャ座標の設定
		pVtx2[0].tex = D3DXVECTOR2(0.0f +g_fBG,0.0f);
		pVtx2[1].tex = D3DXVECTOR2(1.0f +g_fBG, 0.0f); 
		pVtx2[2].tex = D3DXVECTOR2 (0.0f+g_fBG, 1.0f);
		pVtx2[3].tex = D3DXVECTOR2(1.0f + g_fBG,1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffBG->Unlock();
	
}
//================================================
//背景の描画処理
//================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ

									//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBG);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,		//描画する最初の頂点インデックス
		2);		//プリミティブ（ポリゴン）数

}