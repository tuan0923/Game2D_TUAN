//===================================================================
//
//	クレバス(地面の亀裂)の処理[model_crevasse.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _CREVASSE_H_
#define _CREVASSE_H_

#include "model.h"

//*******************************************************************
//	障害物クラスの定義
//*******************************************************************
class CCrevasse : public CModel
{
public:
	//メンバ関数
	CCrevasse();
	~CCrevasse() override;

	// 生成処理
	static CCrevasse *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static void CollisionAll(D3DXVECTOR3* pPosPlayer, D3DXVECTOR3* pPosPlayerOld, D3DXVECTOR3* pSizePlayer);
	bool Collision(D3DXVECTOR3* pPosPlayer, D3DXVECTOR3* pPosPlayerOld, D3DXVECTOR3* pSizePlayer);

private:
	D3DXVECTOR3 m_PosOld;	//前回の位置
};

#endif	// _OBSTACLE_H_
