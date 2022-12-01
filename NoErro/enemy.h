#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "object2D.h"
//プレーヤーのクラス
class CEnemy :public CObject2D
{
public:
	CEnemy();
	~CEnemy() override;

	static CEnemy* Create();
	static HRESULT Load();
	static void UnLoad();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void HitEnemy(int nDamage);
private:
	CEnemy *m_enemy;
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 Enemy_Move;
	int m_Life;
};
#endif