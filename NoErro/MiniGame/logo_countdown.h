//-------------------------------------------
//
// カウントダウンロゴの情報[logo_countdown.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _LOGO_COUNTDOWN_H_
#define _LOGO_COUNTDOWN_H_

//-------------------------------------------
// インクルード
//-------------------------------------------
#include "logo.h"

//-------------------------------------------
// 前方宣言
//-------------------------------------------
class CNumber;

//-------------------------------------------
// カウントダウンロゴクラス
//-------------------------------------------
class CLogoCountDown : public CLogo
{
public:
	// コンストラクタ
	CLogoCountDown();
	// デストラクタ
	~CLogoCountDown() override;

	// 生成
	static CLogoCountDown* Create(const int& nNum);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	void Set();							// スコアの設定

private:
	CNumber *m_apNumber;				// 数字のポインタ
	int m_nNum;							// 数字の格納情報
};

#endif		// _LOGO_COUNTDOWN_H_
