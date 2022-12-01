//===================================================================
//
//	雪崩発生時の処理[avalanche.h]
//	Author:Koshimoto Manato
//
//===================================================================
#ifndef _AVALANCHE_H_
#define _AVALANCHE_H_

#include "object.h"

//*******************************************************************
//	前方宣言
//*******************************************************************
class CEffect;

//*******************************************************************
//	雪崩クラスの定義
//*******************************************************************
class CAvalanche : public CObject
{
private:
	static const int MAX_AVALANCHE = 256;	//雪崩に使用するエフェクトの最大数
public:
	CAvalanche();					//コンストラクタ
	~CAvalanche() override;			//デストラクタ

	//メンバ関数
	static CAvalanche *Create();	//生成処理
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画

private:
	static CEffect *m_pEffect[MAX_AVALANCHE];	//雪崩のエフェクト情報
	int m_nDuration;				//雪崩の継続時間
	int m_nEffectIdx;				//雪崩のエフェクトのインデックス
	bool m_bEnd;					//雪崩が終わったかどうか
};

#endif		// _AVALANCHE_H_
