//========================================================
// main.cpp
// 2DGame
//Author: テュアン
//========================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bg.h"
#include "block.h"
#include "item.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "sound.h"
#include "score.h"
#include "time.h"
#include "enemy.h"
#include "explosion.h"
#include "fade.h"
#include "howto.h"
#include "highscore.h"
//マクロ定義
#define CLASS_NAME		"WindowClass"		//ウィンドウクラス名
#define WINDOW_NAME		"2Dのゲーム"
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LPDIRECT3DDEVICE9 GetDevice(void);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//グローバル変数
LPDIRECT3D9		g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;
MODE g_mode = MODE_TITLE;
//========================================================
//メイン関数
//========================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lCmdLine, int nCmdShow)

{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//画面サイズの構造体
	DWORD dwCurrentTime;				//現在時刻
	DWORD dwExecLastTime;				//最後に処理した時刻

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						//ウィンドウのスタイル
		WindowProc,						//ウィンドウプロシージャ
		0,
		0,
		hInstance,						//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),//タスクバーアイコン
		LoadCursor(NULL,IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)

	};
	HWND hWnd;		//ウィンドウハンドル
	MSG msg;		//メッセージを格納する変数

					//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウ生成
	hWnd = CreateWindowEx(
		0,							//拡張ウィンドウスタイル
		CLASS_NAME,					//ウィンドウクラスの名前
		WINDOW_NAME,				//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル
		CW_USEDEFAULT,				//ウィンドウの左上x座標
		CW_USEDEFAULT,				//ウィンドウの左上y座標
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//初期化処理(ダメだった時の処理)
	if (FAILED(Init(hInstance, hWnd, FALSE)))
	{
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;		//処理開始の時刻（現在時刻）を保存
			}

			//更新処理
			Update();
			//描画処理
			Draw();
		}
	}

	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}
//================================================
//ウィンドウプロシージャー
//================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN://キーを押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE://[ESC]キーが押された
			int nID = MessageBox(hWnd, "終了しますか", "終了メッセージ", MB_YESNO);
			//ウインドを破棄する(WM_DESTROYメッセージを送る)
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//================================================
//初期化処理
//================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;		//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ

									//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3Dデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))

	{
		//Direct3Dデバイスの生成（描画処理はハードウェア、頂点処理はCPUで行う）
		if (FAILED((g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice))))

		{
			//Direct3Dデバイスの生成（描画処理と頂点処理をCPUで行う）
			if (FAILED((g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice))))

			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	InitSound(hWnd);
	//モードの設定
	InitFade(g_mode);
	SetMode(g_mode);
	return S_OK;
}
//================================================
//終了処理
//================================================
void Uninit(void)
{
	//タイトル画面の終了処理
	UninitTitle();

	UninitHowto();
	//ゲーム画面の終了処理
	UninitGame();

	//リザルト画面の終了処理
	UninitResult();

	//キーボードの終了処理
	UninitKeyboard();
	
	//サウンドの終了設定
	UninitSound();

	UninitFade();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//================================================
//更新処理
//================================================
void Update(void)
{
	UpdateFade();
	//キーボードの更新処理
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面
		UpdateTitle();
		break;
	case MODE_HOWTO:
		UpdateHowto();
		break;
	case MODE_GAME:	//ゲーム画面
		UpdateGame();
		break;

	case MODE_RESULT:	//リザルト処理
		UpdateResult();
		break;
	}

}
//================================================
//描画処理
//================================================
void Draw(void)
{
	//画面クリア（バッファクリア、Zバッファのクリア）
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功
	 
		////描画終了
	
		switch (g_mode)
		{
		case MODE_TITLE:	//タイトル画面
			DrawTitle();
			break;
		case MODE_HOWTO:	
			DrawHowto();
			break;
		case MODE_GAME:	//ゲーム画面
			DrawGame();
			break;

		case MODE_RESULT:	//リザルト処理
			DrawResult();
			break;
		}
		DrawFade();
	
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//デバイスの取得
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//================================================
//
//================================================
void SetMode(MODE mode)
{
	//現在の画面の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面
		UninitTitle();
		break;
	case MODE_HOWTO:	
		UninitHowto();
		break;
	case MODE_GAME:	//ゲーム画面
		UninitGame();
		break;

	case MODE_RESULT:	//リザルト処理
		UninitResult();
		break;
	}

	//新しい画面の初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_HOWTO:
		InitHowto();
		break;
	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;
	}

	g_mode = mode;	//現在の画面を切り替える
}

//モードの取得
MODE GetMode(void)
{
	return g_mode;
}