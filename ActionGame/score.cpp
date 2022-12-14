//========================================================
// score.cpp
// 2DGame
//Author: テュアン
//========================================================
#include "score.h"
#include "Highscore.h"
#include "game.h"
#include "result.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posScore;							//スコアの位置
int g_nScore;										//スコアの値
//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitScore(void)
{
	int nCount;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//number000.png",
		&g_pTextureScore);

		g_posScore = D3DXVECTOR3(200.0f, 40.0f, 0.0f);
	
	g_nScore = 0;													

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	
	for (nCount = 0; nCount < SCORE_MAX; nCount++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - (SCORE_WIDTH / 2) + SCORE_WIDTH * nCount, g_posScore.y - (SCORE_HEIGHT / 2), 0);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + (SCORE_WIDTH / 2) + SCORE_WIDTH * nCount, g_posScore.y - (SCORE_HEIGHT / 2), 0);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - (SCORE_WIDTH / 2) + SCORE_WIDTH * nCount, g_posScore.y + (SCORE_HEIGHT / 2), 0);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + (SCORE_WIDTH / 2) + SCORE_WIDTH * nCount, g_posScore.y + (SCORE_HEIGHT / 2), 0);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;		//頂点データを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
	SetScore(0, g_posScore, SCORE_WIDTH, SCORE_HEIGHT);
	SetScore(0, D3DXVECTOR3(500.0f, 40.0f, 0.0f), SCORE_WIDTH, SCORE_HEIGHT);

}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateScore(void)
{
	
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawScore(void)
{
	int nCntScore;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureScore);
	for (nCntScore = 0; nCntScore < SCORE_MAX; nCntScore++)
	{
		
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//-------------------------------------------
//スコアの設定処理
//-------------------------------------------
void SetScore(int nScore, D3DXVECTOR3 pos, float width, float height)
{//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	int aPosTexScore[SCORE_MAX];			//各桁の数字を格納
	int nCountScore;

	g_nScore = nScore;
	g_posScore = pos;
	aPosTexScore[0] = g_nScore % 100000000 / 10000000;
	aPosTexScore[1] = g_nScore % 10000000 / 1000000;
	aPosTexScore[2] = g_nScore % 1000000 / 100000;
	aPosTexScore[3] = g_nScore % 100000 / 10000;
	aPosTexScore[4] = g_nScore % 10000 / 1000;
	aPosTexScore[5] = g_nScore % 1000 / 100;
	aPosTexScore[6] = g_nScore % 100 / 10;
	aPosTexScore[7] = g_nScore % 10 / 1;

	//頂点バッファをロックし、頂点情報へのポインタを取得

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (nCountScore = 0; nCountScore < SCORE_MAX; nCountScore++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - width / 2 + width * nCountScore, g_posScore.y - height / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + width / 2 + width * nCountScore, g_posScore.y - height / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - width / 2 + width * nCountScore, g_posScore.y + height / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + width / 2 + width * nCountScore, g_posScore.y + height / 2, 0.0f);

		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore] + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//-------------------------------------------
//スコアの加算処理
//-------------------------------------------
void AddScore(int nValue)
{
	int aPosTexScore[SCORE_MAX];		//各桁の数字を格納
	int nCountScore;

	g_nScore += nValue;
	if (g_nScore <= 0)
	{
		g_nScore = 0;
	}
	aPosTexScore[0] = g_nScore % 100000000 / 10000000;
	aPosTexScore[1] = g_nScore % 10000000 / 1000000;
	aPosTexScore[2] = g_nScore % 1000000 / 100000;
	aPosTexScore[3] = g_nScore % 100000 / 10000;
	aPosTexScore[4] = g_nScore % 10000 / 1000;
	aPosTexScore[5] = g_nScore % 1000 / 100;
	aPosTexScore[6] = g_nScore % 100 / 10;
	aPosTexScore[7] = g_nScore % 10 / 1;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (nCountScore = 0; nCountScore < SCORE_MAX; nCountScore++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexScore[nCountScore] + 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

int GetScore(void)
{
	return g_nScore;
}