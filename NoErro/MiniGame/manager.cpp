//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "base.h"
#include "fade.h"
#include "sound.h"
#include "load.h"

// 追加
#include "texture.h"
#include "x_file.h"
#include "x_file_motion.h"
/**/

#include "input_keyboard.h"
#include "input_joypad.h"
#include "input_mouse.h"

#include "object.h"
#include "title.h"
#include "game.h"
#include "result.h"

#include "continue.h"

#include <time.h>

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CManager *CManager::m_pManager = nullptr;		// マネージャーのポインタ

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
CManager::CManager() :m_pTitle(), m_pGame(), m_pResult(), m_pRenderer(), m_pInputKeyboard(), m_pInputJoypad(), m_pInputMouse(), m_pSound(), m_pTexture(),
					m_pXFile(), m_pMotion(), m_pFade(), m_bPause(false), m_mode(MODE_TITLE)
{
	// 初期化
	ZeroMemory(&m_EntryInfo, sizeof(m_EntryInfo));
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CManager::~CManager()
{
}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// 現在時刻によってランダムに設定する
	srand((unsigned)time(NULL));

	// レンダラーの初期化処理
	m_pRenderer = new CRenderer;

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}

	// キーボードの初期化処理
	m_pInputKeyboard = new CInputKeyboard;

	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Init(hInstance, hWnd);
	}

	// ジョイパッド情報の初期化処理
	m_pInputJoypad = new CInputJoypad;

	if (m_pInputJoypad != nullptr)
	{
		m_pInputJoypad->Init();
	}

	// マウス情報の初期化処理
	m_pInputMouse = new CInputMouse;

	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Init(hInstance, hWnd);
	}

	//テクスチャクラスの初期化処理
	m_pTexture = new CTexture;

	if (m_pTexture != nullptr)
	{
		m_pTexture->Init();
	}
	
	//Xファイルクラスの初期化処理
	m_pXFile = new CXFile;

	if (m_pXFile != nullptr)
	{
		m_pXFile->Init();
	}

	//モデルモーションクラスの初期化処理
	m_pMotion = new CXFileMotion;

	if (m_pMotion != nullptr)
	{
		m_pMotion->Init(hWnd);
	}

	// サウンドの初期化処理
	m_pSound = new CSound;

	if (m_pSound != nullptr)
	{
		m_pSound->Init(hWnd);
	}

	// フェードの生成
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create(m_mode);
	}

	//敵配置情報のロード
	//LoadSpace::LoadEnemy(hWnd);

	// モードの設定
	SetMode(MODE_TITLE);

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CManager::Uninit()
{
	// サウンドの終了処理
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	// レンダラの終了処理
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// フェードの破棄
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		m_pFade = nullptr;
	}

	// オブジェクトの終了処理
	CObject::ReleaseAll();

	// 全てのシーンを破棄
	UninitSceneAll();

	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Uninit();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//Xファイルの破棄
	if (m_pXFile != nullptr)
	{
		m_pXFile->Uninit();
		delete m_pXFile;
		m_pXFile = nullptr;
	}

	//モデルモーション情報の破棄
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// キーボードの終了処理
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	// ジョイパッドの終了処理
	if (m_pInputJoypad != nullptr)
	{
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = nullptr;
	}

	// マウスの終了処理
	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CManager::Update()
{
	// キーボードの更新処理(※最初に行う)
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	// ジョイパッドの更新処理
	if (m_pInputJoypad != nullptr)
	{
		m_pInputJoypad->Update();
	}

	// マウスの更新処理
	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Update();
	}

	// フェードの更新
	if (m_pFade != nullptr)
	{
		m_pFade->Update();
	}

	//ポーズ中でないなら
	if (m_bPause == false)
	{
		// タイトルの更新処理
		if (m_pTitle != nullptr)
		{
			m_pTitle->Update();
		}

		// ゲームの更新処理
		if (m_pGame != nullptr)
		{
			m_pGame->Update();
		}

		// リザルトの更新処理
		if (m_pResult != nullptr)
		{
			m_pResult->Update();
		}
	}

	// レンダラの更新処理
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void CManager::Draw()
{
	// フェードの更新
	if (m_pFade != nullptr)
	{
		m_pFade->Draw();
	}

	// レンダラの描画処理
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

//-----------------------------------------------------------------------------
// 全てのシーンを破棄
//-----------------------------------------------------------------------------
void CManager::UninitSceneAll()
{
	// タイトルの破棄
	if (m_pTitle != nullptr)
	{
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = nullptr;
	}

	// ゲームの破棄
	if (m_pGame != nullptr)
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = nullptr;
	}

	// リザルトの破棄
	if (m_pResult != nullptr)
	{
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = nullptr;
	}
}

//-----------------------------------------------------------------------------
// モードの設定
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	// 全てのシーンを破棄
	UninitSceneAll();

	// オブジェクトの削除
	CObject::ReleaseAll();

	// モードの設定
	m_mode = mode;

	// モードの確定
	switch (m_mode)
	{
	case MODE_TITLE:
		// タイトル情報の生成
		m_pTitle = new CTitle;
		// 初期化処理
		m_pTitle->Init();
		break;

	case MODE_GAME:
		// ゲーム情報の生成
		m_pGame = new CGame;
		// 初期化処理
		m_pGame->Init();
		break;

	case MODE_RESULT:
		// リザルト情報の生成
		m_pResult = new CResult;
		// 初期化処理
		m_pResult->Init();
		break;
	}
}

//-----------------------------------------------------------------------------------------------
// 全てのプレイヤーの参加情報を確認
//-----------------------------------------------------------------------------------------------
bool CManager::GetEntryAll()
{
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		// 1人でもエントリーしていれば
		if (m_EntryInfo[nCntPlayer].bEntry == true)
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------------------------
// 参加情報の設定
//-----------------------------------------------------------------------------------------------
void CManager::SetEntryAll(SEntryInfo *pEntry)
{
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		m_EntryInfo[nCntPlayer] = pEntry[nCntPlayer];
	}
}
