//===================================================================
//
//	モデルパーツ[motion_parts.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _PARTS_H_			//このマクロ定義がされなかったら
#define _PARTS_H_			//2重インクルード防止のマクロ定義

#include "object.h"
#include "x_file_data.h"

//=============================================================================
// クラス定義
//=============================================================================
class CParts : public CObject
{
public:
	//メンバ関数
	CParts();					//コンストラクタ
	~CParts();					//デストラクタ

	// 生成
	static CParts* Create(const char* pas);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// 位置設定
	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }
	// 角度設定
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }
	// モデルの設定
	void BindXFile(const SModelInfo& XFile) { m_aXFile = XFile; }
	// 位置取得
	D3DXVECTOR3 GetPosition() { return m_pos; }
	// 角度取得
	D3DXVECTOR3 GetRotation() { return m_rot; }
	// 基本の角度取得
	D3DXVECTOR3 GetRotationBase() { return m_baseRot; }

private:
	// テクスチャの読み込み
	void LoadXFileTexture();

	// メンバ変数
private:
	// Xファイル情報
	SModelInfo m_aXFile;
	// 位置
	D3DXVECTOR3 m_pos;
	// 基本の角度
	D3DXVECTOR3 m_baseRot;
	// 回転
	D3DXVECTOR3 m_rot;
	// ワールドマトリックス
	D3DXMATRIX m_mtxWorld;
	// このパーツの番号
	int m_nIndex;
	// 親パーツの番号
	int m_nParent;
};

#endif
