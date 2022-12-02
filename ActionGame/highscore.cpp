//========================================================
// highscore.cpp
// 2DGame
//Author: テュアン
//========================================================
#include<stdio.h>
#include <string.h>
#include "main.h"
#include "item.h"
#include "game.h"
#include "result.h"
#include "highscore.h"
#include "score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureHighScore = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHighScore = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posHighScore;								//スコアの位置
int g_HighScore;


//スコアの初期化処理
void InitHighScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntHighScore;


	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_pTextureHighScore);

	g_posHighScore = D3DXVECTOR3(800.0f, 420, 0.0f);		//位置の初期化
	g_HighScore = 0;											//値を初期化

	LoadHighScore();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHighScore,
		NULL);

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHighScore = 0; nCntHighScore < MAX_HIGHSCORE; nCntHighScore++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_posHighScore.x - 20 + 40 * nCntHighScore, g_posHighScore.y - 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posHighScore.x + 20 + 40 * nCntHighScore, g_posHighScore.y - 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posHighScore.x - 20 + 40 * nCntHighScore, g_posHighScore.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posHighScore.x + 20 + 40 * nCntHighScore, g_posHighScore.y + 30.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;				//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffHighScore->Unlock();

	SetHighScore(g_HighScore);
}


//スコアの終了処理
void UninitHighScore(void)
{
	//テクスチャの破棄
	if (g_pTextureHighScore != NULL)
	{
		g_pTextureHighScore->Release();
		g_pTextureHighScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffHighScore != NULL)
	{
		g_pVtxBuffHighScore->Release();
		g_pVtxBuffHighScore = NULL;
	}
}


//スコアの更新処理
void UpdateHighScore(void)
{

}


//スコアの描画処理
void DrawHighScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスへのポインタ
	int nCntHighScore;

	//デバイスへの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHighScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureHighScore);

	for (nCntHighScore = 0; nCntHighScore < MAX_HIGHSCORE; nCntHighScore++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//プリミティブの種類
			nCntHighScore * 4, 2);									//プリミティブ（ポリゴン）数
	}
}


//スコアの設定処理
void SetHighScore(int nHighScore)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	int aPosTexU[MAX_HIGHSCORE];				//各桁の数字を格納
	int nCntHighScore;

	g_HighScore = nHighScore;

	aPosTexU[0] = g_HighScore % 100000000 / 10000000;
	aPosTexU[1] = g_HighScore % 10000000 / 1000000;
	aPosTexU[2] = g_HighScore % 1000000 / 100000;
	aPosTexU[3] = g_HighScore % 100000 / 10000;
	aPosTexU[4] = g_HighScore % 10000 / 1000;
	aPosTexU[5] = g_HighScore % 1000 / 100;
	aPosTexU[6] = g_HighScore % 100 / 10;
	aPosTexU[7] = g_HighScore % 10 / 1;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHighScore = 0; nCntHighScore < MAX_HIGHSCORE; nCntHighScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntHighScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntHighScore] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntHighScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntHighScore] + 1), 1.0f);

		pVtx += 4;  //頂点データのポインタを４つ分進める

	}
	//頂点バッファをアンロック
	g_pVtxBuffHighScore->Unlock();
}


//加算処理
void AddHighScore(int nValue)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	int aPosTexU[MAX_HIGHSCORE];		//各桁の数字を格納
	int nCntHighScore;
	g_HighScore += nValue;

	if (g_HighScore <= 0)
	{
		g_HighScore = 0;
	}

	aPosTexU[0] = g_HighScore % 100000000 / 10000000;
	aPosTexU[1] = g_HighScore % 10000000 / 1000000;
	aPosTexU[2] = g_HighScore % 1000000 / 100000;
	aPosTexU[3] = g_HighScore % 100000 / 10000;
	aPosTexU[4] = g_HighScore % 10000 / 1000;
	aPosTexU[5] = g_HighScore % 1000 / 100;
	aPosTexU[6] = g_HighScore % 100 / 10;
	aPosTexU[7] = g_HighScore % 10 / 1;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHighScore = 0; nCntHighScore < MAX_HIGHSCORE; nCntHighScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntHighScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntHighScore] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntHighScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntHighScore] + 1), 1.0f);

		pVtx += 4;  //頂点データのポインタを４つ分進める

	}
	//頂点バッファをアンロック
	g_pVtxBuffHighScore->Unlock();
}

int GetHighScore(void)
{
	return g_HighScore;
}


//ファイルに書き込む処理
void SaveHighScore(void)
{
	FILE *pFile;		//ファイルポインタを宣言
	int nScore;

	nScore = GetScore();


	if (nScore > g_HighScore)
	{
		g_HighScore = nScore;
	}

	//ファイルを開く
	pFile = fopen("HighScore.txt", "w");
	if (pFile != NULL)
	{//ファイルが開けた場合

	 //ファイルから文字列を読み込む
		fprintf(pFile, "%d", g_HighScore);

	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルが開けませんでした***?n");
	}

	//ファイルを閉じる
	fclose(pFile);
}

//ファイルから読み込む処理
void LoadHighScore(void)
{
	FILE *pFile;		//ファイルポインタを宣言

	pFile = fopen("HighScore.txt", "r");
	if (pFile != NULL)
	{//ファイルが開けた場合
	 //ファイルに文字列を書き出す
		fscanf(pFile, "%d", &g_HighScore);
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルが開けませんでした***?n");
	}
}