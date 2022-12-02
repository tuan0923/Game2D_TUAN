//========================================================
// player.cpp
// 2DGame
//Author: テュアン
//========================================================
#include "main.h"
#include "enemy.h"
#include "player.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ

PLAYER g_aPlayer;	//プレイヤー構造体

//================================================
//プレイヤーの初期化設定
//================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	VERTEX_2D *pVtx;	//頂点情報のポインタ
	//デバイスの取得
	pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//player000.png",
		&g_pTexturePlayer);
	g_aPlayer.bDisp = false;
	g_aPlayer.bIsJumping = false;
	g_aPlayer.nCounterAnimPlayer = 0;
	g_aPlayer.nPatternAnimPlayer = 0;
	g_aPlayer.pos = D3DXVECTOR3(500.0f, 700.f, 0.0f);
	g_aPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x - (PLAYER_WIDTH / 2), g_aPlayer.pos.y - PLAYER_HEIGTH, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + (PLAYER_WIDTH / 2), g_aPlayer.pos.y - PLAYER_HEIGTH, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x - (PLAYER_WIDTH / 2), g_aPlayer.pos.y , 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + (PLAYER_WIDTH / 2), g_aPlayer.pos.y, 0.0f);

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
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffPlayer->Unlock();
}
//================================================
//ポリゴンの終了処理
//================================================
void UninitPlayer(void)
{
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
	//テクスチャ破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}
//================================================
//プレイヤーのの更新処理
//================================================
void UpdatePlayer(void)
{

	VERTEX_2D *pVtx;	//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//移動処理
	if (GetKeyboardPress(DIK_D) == true)
	{ // 右上移動
		
		g_aPlayer.move.x += sinf(D3DX_PI * 0.5f) * 1.50f;
		g_aPlayer.move.y += cosf(D3DX_PI * 0.5f) * 1.50f;
		
		g_aPlayer.nDirectionMove = 0;
		
	}
	if (GetKeyboardPress(DIK_A) == true)
	{ // 左上移動
		
		g_aPlayer.move.x += sinf(-D3DX_PI * 0.5f) * 1.50f;
		g_aPlayer.move.y += cosf(-D3DX_PI * 0.5f) * 1.50f;
		
		g_aPlayer.nDirectionMove = 1;
		
	}

	//移動量更新（減衰）
	g_aPlayer.move.x += (0.0f - g_aPlayer.move.x)*0.19f;	//目的の値-現在の値*減衰係数

	//JUMP
	if (GetKeyboardTrigger(DIK_W) == true)
	{//SPACEキーを押す
		if (g_aPlayer.bIsJumping == false)
		{
			PlaySound(SOUND_LABEL_SE_JUMP);
			g_aPlayer.move.y = -19.0f;
			g_aPlayer.bIsJumping = true;
			if (g_aPlayer.nPatternAnimPlayer == 0 || g_aPlayer.nPatternAnimPlayer == 2)
			{//ジャンプ中のポーズ
				g_aPlayer.nPatternAnimPlayer += 1;

			}
		}
	}
	if (g_aPlayer.bIsJumping != true )
	{
		if (g_aPlayer.move.x >= 1.0f || g_aPlayer.move.x <= -1.0f)
		{//移動していたら
			g_aPlayer.nCounterAnimPlayer++;
			//ジャンプ時のアニメーション固定
			if (g_aPlayer.nCounterAnimPlayer % 9 == 4)
			{//パターン数を増やす
				g_aPlayer.nPatternAnimPlayer++;
			}
			if (g_aPlayer.nPatternAnimPlayer == 4)
			{//パターン数を戻す
				g_aPlayer.nPatternAnimPlayer = 0;
			}
		}
		else
		{//移動停止
			if (g_aPlayer.nPatternAnimPlayer == 1 || g_aPlayer.nPatternAnimPlayer == 3)
			{//パターン1,3だったら
				g_aPlayer.nPatternAnimPlayer ++ ;

				if (g_aPlayer.nPatternAnimPlayer == 4)
				{//パターン数を戻す
					g_aPlayer.nPatternAnimPlayer = 0;
				}
			}
		}
	}

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((0.0f + (0.25f*g_aPlayer.nPatternAnimPlayer)), 0.0f + (0.5f*g_aPlayer.nDirectionMove));
	pVtx[1].tex = D3DXVECTOR2((0.25f + (0.25f*g_aPlayer.nPatternAnimPlayer)), 0.0f + 0.5f*(g_aPlayer.nDirectionMove));
	pVtx[2].tex = D3DXVECTOR2((0.0f + (0.25f*g_aPlayer.nPatternAnimPlayer)), 0.5f + (0.5f*g_aPlayer.nDirectionMove));
	pVtx[3].tex = D3DXVECTOR2((0.25f + (0.25f*g_aPlayer.nPatternAnimPlayer)), 0.5f + (0.5f*g_aPlayer.nDirectionMove));

	//前回の位置を保存
	g_aPlayer.posOld = g_aPlayer.pos;
	/*a_aPlayer.pos += g_aPlayer.move;*/
	//重力加算
	g_aPlayer.move.y += 1.00f;
	////位置更新
	g_aPlayer.pos.x += g_aPlayer.move.x;
	g_aPlayer.pos.y += g_aPlayer.move.y;
	//画面外に出ないように
	if (g_aPlayer.pos.x > SCREEN_WIDTH - 17.5f)
	{
		g_aPlayer.pos.x = SCREEN_WIDTH - 17.5f;
	}
	if (g_aPlayer.pos.y > SCREEN_HEIGHT - 10.0f)
	{
		g_aPlayer.pos.y = SCREEN_HEIGHT - 10.0f;
		g_aPlayer.bIsJumping = false;
	}
	if (g_aPlayer.pos.x < 0.0f)
	{
		g_aPlayer.pos.x = 0.0f;

	}
			
	
	//ブロックとの当たり判定
	bool bIsLanding = CollisionBlock(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move,25.0f/2, 100.0f);
	if (bIsLanding == true)
	{
		g_aPlayer.bIsJumping = false;
		
	}

	//Itemの当たり判定
	CollisionItem(&g_aPlayer.pos, 25.0f/2, 100.0f);
	//Enemy の当たり判定
	CollisionEnemy(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, 25.0f / 2 ,100.0f);

	
	if (g_aPlayer.pos.y >= SCREEN_HEIGHT)
	{//地面より下にいかない
		g_aPlayer.pos.y = SCREEN_HEIGHT;
		g_aPlayer.move.y = 0.0f;
		g_aPlayer.bIsJumping = false;
	}
	if (g_aPlayer.bDisp == true)
	{
		g_aPlayer.nCounterState--;
		if (g_aPlayer.nCounterState <= 0)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_aPlayer.bDisp = false;
		}
	}
	//頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x - (PLAYER_WIDTH / 2), g_aPlayer.pos.y - PLAYER_HEIGTH, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + (PLAYER_WIDTH / 2), g_aPlayer.pos.y - PLAYER_HEIGTH, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x - (PLAYER_WIDTH / 2), g_aPlayer.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + (PLAYER_WIDTH / 2), g_aPlayer.pos.y, 0.0f);
	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

}
//================================================
// Hit Player
//================================================
void HitPlayer(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	g_aPlayer.nCounterState = 15;
	g_aPlayer.bDisp = true;
	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(225, 5, 5, 5);
	pVtx[1].col = D3DCOLOR_RGBA(225, 5, 5, 5);
	pVtx[2].col = D3DCOLOR_RGBA(225, 5, 5, 5);
	pVtx[3].col = D3DCOLOR_RGBA(225, 5, 5, 5);
	
	g_pVtxBuffPlayer->Unlock();


}
//================================================
//ポリゴンの描画処理
//================================================
void DrawPlayer(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}