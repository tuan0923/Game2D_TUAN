//========================================================
// explosion.cpp
// 2DGame
//Author: テュアン
//========================================================
#include "main.h"
#include "explosion.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExplosion[NUM_EXPLOSION] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
Explosion g_aExplosion[MAX_EXPLOSION];

//================================================
//爆発の初期化処理
//================================================
void InitExplosion(void)
{
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//effect001.png",
		&g_pTextureExplosion[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//explosion000.png",
		&g_pTextureExplosion[1]);
	//爆発の情報の初期化処理
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].ntype = EXPLOSION_Q;
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE_Y, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}
//================================================
//
//================================================
void UninitExplosion(void)
{
	//テクスチャ破棄
	for (int nCntExplosion = 0; nCntExplosion < NUM_EXPLOSION; nCntExplosion++)
	{
		if (g_pTextureExplosion[nCntExplosion] != NULL)
		{
			g_pTextureExplosion[nCntExplosion]->Release();
			g_pTextureExplosion[nCntExplosion] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//================================================
//
//================================================
void UpdateExplosion(void)
{
	VERTEX_2D *pVtx;
	int nCntExplosion;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//テクスチャのアニメーション
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if (g_aExplosion[nCntExplosion].nCounterAnim % 8 == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnim++;
				if (g_aExplosion[nCntExplosion].nPatternAnim > 5)
				{
					g_aExplosion[nCntExplosion].bUse = false;		//使用していない状態にする
				}
			}
				//テクスチャの座標設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.25f * g_aExplosion[nCntExplosion].nPatternAnim), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + (0.25f * g_aExplosion[nCntExplosion].nPatternAnim), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.25f * g_aExplosion[nCntExplosion].nPatternAnim), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + (0.25f * g_aExplosion[nCntExplosion].nPatternAnim), 1.0f);
				pVtx += 4;

			}			
		}
	//頂点座標をアンロック
	g_pVtxBuffExplosion->Unlock();
}
//================================================
//
//================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, EXPLOSION_TYPE ntype)
{
	VERTEX_2D *pVtx;
	int nCntExplosion;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//爆発が使用されていない
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].ntype = ntype;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].bUse = true;
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_SIZE_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_SIZE_Y, 0.0f);
			////テクスチャ
			//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	//頂点座標をアンロック
	g_pVtxBuffExplosion->Unlock();
}
//================================================
//
//================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	pDevice = GetDevice();	//デバイスの取得
	int nCntExplosion;

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//弾が使用されているとき
		 //テクスチャ設定
			pDevice->SetTexture(0, g_pTextureExplosion[g_aExplosion[nCntExplosion].ntype]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);

		}
	}
}