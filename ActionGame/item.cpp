//========================================================
// item.cpp
// 2DGame
//Author: テュアン
//========================================================
#include"main.h"
#include "item.h"
#include "time.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureItem[NUM_ITEM] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;
ITEM g_Item[MAX_ITEM];
int g_ItemTotalNum;

//================================================
//初期化処理
//================================================
void InitItem(void)
{
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//coin000.png", &g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//Diamond.png", &g_pTextureItem[1]);
	//Itemの情報初期化
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_Item[nCntItem].nCountAnim = 0;
		g_Item[nCntItem].nPatternAnim = 0;
		g_Item[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCntItem].fWidth = ITEM_WIDTH;
		g_Item[nCntItem].fHeight = ITEM_HEIGHT;
		g_Item[nCntItem].bUse = false;
		g_Item[nCntItem].ntype = ITEM_TYPE_COIN;

	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

		pVtx += 4;
	}
	//Item出す
	SetItem(D3DXVECTOR3(200.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(250.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(300.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(350.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(400.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);

	SetItem(D3DXVECTOR3(1100.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(1000.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(1050.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(950.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(900.0f, 470.0f, 0.0f), ITEM_TYPE_COIN);

	SetItem(D3DXVECTOR3(250.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(400.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(350.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(300.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);

	SetItem(D3DXVECTOR3(930.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(980.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(1030.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(1080.0f, 250.0f, 0.0f), ITEM_TYPE_COIN);

	SetItem(D3DXVECTOR3(650.0f, 320.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(315.0f, 120.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(950.0f, 120.0f, 0.0f), ITEM_TYPE_COIN);
	SetItem(D3DXVECTOR3(650.0f, 30.0f, 0.0f), ITEM_TYPE_MAX);

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}
//================================================
//Itemの終了処理
//================================================
void UninitItem(void)
{

	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
	//テクスチャ破棄
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem]->Release();
			g_pTextureItem[nCntItem] = NULL;
		}
	}
}
//================================================
//
//================================================
void UpdateItem(void)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	int nCntItem;
	//頂点バッファをロックし、頂点情報へのポインタを取得									
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_Item[nCntItem].nCountAnim++;		//カウンターを加算
		if (g_Item[nCntItem].nCountAnim % 15 == 0)
		{
			g_Item[nCntItem].nPatternAnim++;//パターンNo.を更新
		}
		
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((0.0f + (0.25*g_Item[nCntItem].nPatternAnim)), 0.0f );
		pVtx[1].tex = D3DXVECTOR2((0.25f + (0.25*g_Item[nCntItem].nPatternAnim)), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((0.0f + (0.25*g_Item[nCntItem].nPatternAnim)), 1.0f );
		pVtx[3].tex = D3DXVECTOR2((0.25f + (0.25*g_Item[nCntItem].nPatternAnim)), 1.0f );
		pVtx += 4;
	}
	
	//頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}
//================================================
//
//================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	pDevice = GetDevice();	//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{//ブロックが使用されているとき
		 //テクスチャ設定
			pDevice->SetTexture(0, g_pTextureItem[g_Item[nCntItem].ntype]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nCntItem * 4, 2);
		}
	}
}
//================================================
//
//================================================
void SetItem(D3DXVECTOR3 pos, ITEM_TYPE type)
{
	VERTEX_2D *pVtx;
	
	//頂点バッファロック
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == false)
		{//itemが使われていない
			g_Item[nCntItem].pos = pos;
			g_Item[nCntItem].ntype = type;
			g_Item[nCntItem].bUse = true;
			//頂点座標の更新									
			pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y + (ITEM_HEIGHT / 2), 0.0f);

			break;
		}
		pVtx += 4;
	}
	//頂点バッファアンロック
	g_pVtxBuffItem->Unlock();
}
//================================================
//
//================================================
void CollisionItem(D3DXVECTOR3 *pPos, float fWidth, float fHeight)
 {
	 ITEM * pItem;
	 int nCntItem;
	 pItem = GetItem();
	
	 for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	 {
		 if (pItem->bUse == true)
		 {
			 if ((pItem->pos.x - (fWidth / 2)) <= (pPos->x + (fWidth / 2)) &&
				 (pItem->pos.x + (fWidth / 2)) >= (pPos->x - (fWidth / 2)) &&
				 (pItem->pos.y - (fHeight / 2)) <= (pPos->y) &&
				 (pItem->pos.y + (fHeight / 2) >= pPos->y - (fHeight)))
			 {
				 DeleteItem(nCntItem);
			 }			
		 }
		 pItem++;
	 }
 }
//================================================
//
//================================================
void DeleteItem(int nCntItem)
{
	if (g_Item[nCntItem].ntype == ITEM_TYPE_COIN)
	{
		g_Item[nCntItem].bUse = false;
		SetExplosion(g_Item[nCntItem].pos, 255, EXPLOSION_Q);
		AddScore(100);
		PlaySound(SOUND_LABEL_SE_COIN);
	} 
	if (g_Item[nCntItem].ntype == ITEM_TYPE_MAX)
	{
		AddScore(1000);
		g_Item[nCntItem].bUse = false;

		PlaySound(SOUND_LABEL_SE_ITEM);
		SetExplosion(g_Item[nCntItem].pos, 255, EXPLOSION_Q);
		SetFade(MODE_RESULT);
	}
}
//================================================
//
//================================================
 ITEM*GetItem(void)
 {
	 return g_Item;

 }
