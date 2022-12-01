//===================================================================
//
//	モデル処理のヘッダー[motion.h]
//	Author : SHUGO KURODA
//
//===================================================================
#ifndef _MOTION_H_			//このマクロ定義がされなかったら
#define _MOTION_H_			//2重インクルード防止のマクロ定義

#include "object.h"
#include "motion_data.h"

//=============================================================================
// クラス定義
//=============================================================================
class CMotion : public CObject
{
	// 構造体
private:
	//モーション番号情報
	struct AnimIdx
	{
		int nFrame;			// 現在のフレーム数
		int nKeySetIdx;		// 再生中のキーセット番号
		int nMotionIdx;		// 再生中のモーション番号
	};

	// メンバ関数
public:
	CMotion();		// コンストラクタ
	virtual ~CMotion() override;	// デストラクタ

	// 生成
	static CMotion* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name);

	// 初期化
	virtual HRESULT Init() override;
	// 終了
	virtual void Uninit() override;
	// 更新
	virtual void Update() override;
	// 描画
	virtual void Draw() override;

	// 位置設定
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	// 角度設定
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	// 位置取得
	D3DXVECTOR3 GetPosition() { return m_pos; }
	// 位置取得
	D3DXVECTOR3 *GetpPosition() { return &m_pos; }
	// 角度取得
	D3DXVECTOR3 GetRotation() { return m_rot; }
	// 最大サイズ取得
	D3DXVECTOR3 GetSizeMax() { return m_vtxMax; }
	// 最小サイズ取得
	D3DXVECTOR3 GetSizeMin() { return m_vtxMin; }
	// モーション情報の設定
	void BindMotion(ModelMotion motion) { m_motion = motion; }

protected:
	// モーション再生
	void Motion();

private:
	// モーション変更
	void Change(int nMotion, int nKey);

	// メンバ変数
private:
	//モーション情報
	ModelMotion m_motion;
	// 現在のモーション番号情報
	AnimIdx m_animIdx;
	//位置
	D3DXVECTOR3 m_pos;
	//回転
	D3DXVECTOR3 m_rot;
	//モデルの最大サイズ,最小サイズ
	D3DXVECTOR3 m_vtxMax, m_vtxMin;
	//ワールドマトリックス
	D3DXMATRIX m_mtxWorld;
};

#endif		// _MOTION_H_
