//=============================================================================
//
// カウントダウンロゴ処理[logo_countdown.cpp]
// Author : SHUGO KURODA
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "manager.h"
#include "game.h"
#include "enemy_boss.h"
#include "logo_countdown.h"
#include "number.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COUNT_SIZE		(100.0f)
#define COUNT_UNINIT	(60)

//=============================================================================
// コンストラクタ
//=============================================================================
CLogoCountDown::CLogoCountDown() :m_nNum(0)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CLogoCountDown::~CLogoCountDown()
{
}

//=============================================================================
// 生成
//=============================================================================
CLogoCountDown *CLogoCountDown::Create(const int &nCountStart)
{
	CLogoCountDown *pLogo = new CLogoCountDown;

	if (pLogo != nullptr)
	{
		// 数字の設定
		pLogo->m_nNum = nCountStart;

		// 数字ポリゴン生成
		pLogo->m_apNumber = new CNumber("TEX_TYPE_SCORE_UI");

		if (pLogo->m_apNumber != nullptr)
		{
			// 位置設定
			pLogo->m_apNumber->SetPosition(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f));
			// サイズ設定
			pLogo->m_apNumber->SetSize(D3DXVECTOR2(COUNT_SIZE, COUNT_SIZE));
			// 初期化
			pLogo->m_apNumber->Init();
		}

		// 初期化
		pLogo->Init();
	}

	return pLogo;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CLogoCountDown::Init()
{
	// 色の設定
	//m_apNumber->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	// 破棄までのカウンター設定
	SetCountUninit(COUNT_UNINIT);
	// 数値の設定
	Set();

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CLogoCountDown::Uninit()
{
	// 中身があるなら
	if (m_apNumber != nullptr)
	{
		// 数字情報の終了処理
		m_apNumber->Uninit();
		m_apNumber = nullptr;
	}

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新
//=============================================================================
void CLogoCountDown::Update()
{
	int nCounter = GetCountUninit();

	nCounter--;

	// 破棄カウンターが一定数以下
	if (nCounter <= 0)
	{
		if (m_nNum > 1)
		{
			Create(m_nNum - 1);
		}
		else if (m_nNum == 1)
		{
			// ゲーム開始ロゴの追加
			CLogo::Create(m_apNumber->GetPosition(), D3DXVECTOR2(200.0f, 80.0f), "TEX_TYPE_START_UI", 90);
			// ボスを動かす
			CManager::GetManager()->GetGame()->GetEnemyBoss()->SetPattern(CEnemyBoss::PATTERN_NORMAL);
			// ゲームの開始フラグを立てる
			CManager::GetManager()->GetGame()->SetStart(true);
		}

		// 破棄
		Uninit();
		return;
	}

	SetCountUninit(nCounter);

	D3DXVECTOR2 size = m_apNumber->GetSize();

	size.x -= 1.0f;
	size.y -= 1.0f;

	m_apNumber->SetSize(size);

	m_apNumber->SetVertex();
}

//=============================================================================
// 描画
//=============================================================================
void CLogoCountDown::Draw()
{
}

//=============================================================================
// スコアの設定
//=============================================================================
void CLogoCountDown::Set()
{
	//数値を格納
	int nPosTexU = m_nNum % 10;

	// テクスチャ座標の更新
	m_apNumber->SetAnimation(nPosTexU, 0, CNumber::DIVISION_U, CNumber::DIVISION_V);
}
