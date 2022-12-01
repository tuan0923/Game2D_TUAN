//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "renderer.h"
#include "player.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;
class CPlayer;
class CCamera;

//-----------------------------------------------------------------------------
// タイトル画面クラス
//-----------------------------------------------------------------------------
class CTitle
{
public:
	enum TITLE_OBJ
	{//背景の種類
		BG_SKY = 0,		// 背景の空
		LOGO_PLAYER,	// プレイヤーロゴ
		LOGO_TITLE,		// タイトルロゴ
		LOGO_PRESS,		// PRESSロゴ
		BG_FADE,		// 画面を薄暗くする用
		LOGO_TUTORIAL,	// チュートリアル
		LOGO_SHADOW,	// プレイヤーロゴ(黒)
		OBJ_MAX			// 背景の最大数
	};

public:
	CTitle();
	~CTitle();

	//メンバ関数
	HRESULT Init();
	void Uninit();
	void Update();

	// プレイヤー情報
	CPlayer* GetPlayer() { return m_pPlayer[0]; }
	//カメラ情報
	CCamera* GetCamera() { return m_pCamera; }

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[OBJ_MAX];		//テクスチャのポインタ
	CPlayer* m_pPlayer[CPlayer::PLAYER_MAX];
	CCamera* m_pCamera;
	CObject2D *m_apObject2D[OBJ_MAX - 1];
	bool m_bPush;
	// キーボードで参加したかどうか
	bool m_bEntryKeyboard;
	// 参加番号
	int m_nEntryNum;
	int m_nCounter;
	D3DXVECTOR3 m_move;		// 移動量
};

#endif		// _TITLE_H_
