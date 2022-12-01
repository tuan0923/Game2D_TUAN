//===================================================================
//
//		カメラ処理のヘッダー[camera.h]
//		Author:黒田 周吾
//
//===================================================================
#ifndef _CAMERA_H_			//このマクロ定義がされなかったら
#define _CAMERA_H_			//2重インクルード防止のマクロ定義

#include "object.h"

//======================================================
//	カメラの構造体
//======================================================
class CCamera : public CObject
{
public:
	CCamera();
	~CCamera() override;

	static CCamera *Create(const D3DXVECTOR3& posV, const D3DXVECTOR3& posR, const D3DXVECTOR3& rot);	//インスタンス生成処理

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// 視点位置の取得
	D3DXVECTOR3 GetPosV() { return m_posV; }
	// 注視点位置の取得
	D3DXVECTOR3 GetPosR() { return m_posR; }

	// 追従対象の設定
	void SetPosTracking(D3DXVECTOR3 *pPosDest) { m_pPosTracking = pPosDest; }
	// 追従フラグの設定
	void SetTracking(bool bTracking) { m_bTracking = bTracking; }

private:
	D3DXVECTOR3 m_move;				//移動量
	D3DXVECTOR3 m_posV;				//視点
	D3DXVECTOR3 m_posR;				//注視点
	D3DXVECTOR3 m_vecU;				//上方向ベクトル
	D3DXVECTOR3 m_rot;				//向き
	D3DXVECTOR3 *m_pPosTracking;	//追従対象の位置
	D3DXVECTOR3 m_posVDest;			//目的の視点
	D3DXVECTOR3 m_posRDest;			//目的の注視点
	float m_fDistance;				//視点から注視点までの距離
	D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			//ビューマトリックス
	bool m_bTracking;				//カメラ追従中かどうか
};

#endif
