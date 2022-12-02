//========================================================
// game.cpp
// 2DGame
//Author: テュアン
//========================================================
#include "game.h"
#include "input.h"
#include "main.h"
#include "fade.h"

LPDIRECT3DTEXTURE9 g_pTextureGame = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGame = NULL;	//頂点バッファへのポインタ

//================================================
//ゲーム画面の初期化処理
//================================================
void InitGame(void)
{
	//背景初期化処理
	InitBG();

	InitTime();
	//ポリゴンの初期化設定
	InitPlayer();

	InitBlock();

	InitEnemy();

	InitItem();

	InitScore();
	
	InitExplosion();
	PlaySound(SOUND_LABEL_BGM001);
}
//================================================
//ゲーム画面の終了処理
//================================================
void UninitGame(void)
{
	//背景の終了処理
	UninitBG();

	UninitTime();
	//各種オブジェクトの終了処理
	UninitPlayer();

	UninitBlock();
	
	UninitEnemy();

	UninitItem();

	UninitScore();
	 
	UninitExplosion();
	////サウンドの停止
	StopSound();


}
//================================================
//ゲーム画面の更新処理
//================================================
void UpdateGame(void)
{
	//背景更新処理
	UpdateBG();

	//各種オブジェクトの更新処理
	UpdatePlayer();

	UpdateBlock();

	UpdateEnemy();

	UpdateItem();

	UpdateExplosion();

	UpdateScore();

	UpdateTime();

	FADE pFade;
	pFade = GetFade();
	if (GetKeyboardTrigger(DIK_RETURN) == true && pFade == FADE_NONE)
	{
		SetFade(MODE_RESULT);
	}

}
//================================================
//ゲーム画面の描画処理
//================================================
void DrawGame(void)
{
	//各種オブジェクトの描画処理
	DrawBG();

	DrawBlock();

	DrawExplosion();
	//プレイヤーの描画処理
	DrawPlayer();

	DrawEnemy();

	DrawItem();

	DrawScore();

	DrawTime();
}