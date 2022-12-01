#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "object2D.h"
//プレーヤーのクラス
class CPlayer :public CObject2D
{
public:
	CPlayer();
	~CPlayer() override;

	static CPlayer* Create();
	static HRESULT Load();
	static void UnLoad();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetPlayer(D3DXVECTOR3 pos);
	
private:
	CPlayer *m_player;
	static LPDIRECT3DTEXTURE9 m_pTexture ;
	D3DXVECTOR3 m_pos;
};
#endif