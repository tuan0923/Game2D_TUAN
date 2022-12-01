//-------------------------------------------
//
// ロゴの情報[logo_extend.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _LOGO_EXTEND_H_
#define _LOGO_EXTEND_H_

//-------------------------------------------
// インクルード
//-------------------------------------------
#include "logo.h"

//-------------------------------------------
// ロゴクラス
//-------------------------------------------
class CLogoExtend : public CLogo
{
private:
	// 動き方の種類
	enum EAnim
	{
		ANIM_NONE = 0,
		ANIM_Y_EXPAND,
		ANIM_Y_SHORTEN,
		ANIM_X_EXPAND,
		ANIM_X_SHORTEN
	};

public:
	// コンストラクタ
	CLogoExtend();
	// デストラクタ
	~CLogoExtend() override;

	// 生成
	static CLogoExtend* Create(const D3DXVECTOR2& size, const char* name, const int& nCount);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// 動き方の設定
	void Pattern();

	// メンバ変数
private:
	// 元のサイズ記憶用
	D3DXVECTOR2 m_DefaultSize;
	// 動き方の種類
	EAnim m_anim;
};

#endif		// _LOGO_EXTEND_H_
