//-----------------------------------------------------------------------------------------------
//
// ロゴ処理[logo_extend.cpp]
// Author : SHUGO KURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "logo_extend.h"
#include "manager.h"		// アプリケーション
#include "renderer.h"		// レンダリング
#include "fade.h"
#include "game.h"

#include "texture.h"

//-----------------------------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------------------------
#define EXTEND_SPEED		(20.0f)		// アニメーションの速度

//-----------------------------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CLogoExtend::CLogoExtend() :m_DefaultSize(0.0f, 0.0f), m_anim(ANIM_NONE)
{
	SetType(EObject::OBJ_LOGO);
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CLogoExtend::~CLogoExtend()
{
}

//-----------------------------------------------------------------------------------------------
// 生成
// const D3DXVECTOR3& pos → 生成する位置
// const D3DXVECTOR2& size → 生成するサイズ
// const char* name → 生成するテクスチャ
// const int& nCount → 破棄するまでの時間
//-----------------------------------------------------------------------------------------------
CLogoExtend* CLogoExtend::Create(const D3DXVECTOR2& size, const char* name, const int& nCount)
{
	// ポインタクラスを宣言
	CLogoExtend* pLogoExtend = new CLogoExtend;

	if (pLogoExtend != nullptr)
	{// もしnullptrではなかったら

		// サイズの保存
		pLogoExtend->m_DefaultSize = size;

		// 破棄カウンターを設定
		pLogoExtend->SetCountUninit(nCount);

		// 初期化
		pLogoExtend->Init();

		// テクスチャの設定
		pLogoExtend->BindTexture(CManager::GetManager()->GetTexture()->GetTexture(name));
	}

	return pLogoExtend;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CLogoExtend::Init()
{
	// 位置設定
	SetPosition(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f));
	// 動き方の設定
	m_anim = ANIM_Y_EXPAND;
	// サイズの設定
	SetSize(D3DXVECTOR2(m_DefaultSize.x, 0.0f));
	//初期化
	CObject2D::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CLogoExtend::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CLogoExtend::Update()
{
	// 破棄カウンターの取得
	int nCountUninit = GetCountUninit();

	// カウントを減らす
	nCountUninit--;

	// 表示カウンターが0以下
	if (nCountUninit <= 0)
	{
		// モードの設定
		CManager::GetManager()->GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_TITLE);

		// 破棄
		Uninit();
		return;
	}

	// 破棄カウンターの設定
	SetCountUninit(nCountUninit);

	// 動き方の設定
	Pattern();
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CLogoExtend::Draw()
{
	CObject2D::Draw();
}

//-----------------------------------------------------------------------------------------------
// 動き方の設定
//-----------------------------------------------------------------------------------------------
void CLogoExtend::Pattern()
{
	// サイズの取得
	D3DXVECTOR2 size = GetSize();

	// 動き方の設定
	switch (m_anim)
	{
		// 縦に広がる
	case CLogoExtend::ANIM_Y_EXPAND:

		// サイズの加算
		size.y += EXTEND_SPEED;
		// 指定のサイズに達したら
		if (size.y >= m_DefaultSize.y * 2.0f)
		{
			m_anim = ANIM_Y_SHORTEN;
		}

		break;

		// 縦に縮む
	case CLogoExtend::ANIM_Y_SHORTEN:

		// サイズの加算
		size.y -= EXTEND_SPEED;
		// 指定のサイズに達したら
		if (size.y <= m_DefaultSize.y)
		{
			m_anim = ANIM_X_EXPAND;
		}

		break;

		// 横に広がる
	case CLogoExtend::ANIM_X_EXPAND:

		// サイズの加算
		size.x += EXTEND_SPEED;
		// 指定のサイズに達したら
		if (size.x >= m_DefaultSize.x * 1.5f)
		{
			m_anim = ANIM_X_SHORTEN;
		}
		break;

		// 横に縮む
	case CLogoExtend::ANIM_X_SHORTEN:

		// サイズの加算
		size.x -= EXTEND_SPEED;
		// 指定のサイズに達したら
		if (size.x <= m_DefaultSize.x)
		{
			m_anim = ANIM_NONE;
		}
		break;

	default:
		break;
	}

	if (m_anim != ANIM_NONE)
	{
		// サイズの設定
		SetSize(size);

		// 頂点座標の設定
		SetVertex();
	}
}
