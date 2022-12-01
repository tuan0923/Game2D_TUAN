#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "object2D.h"
class CPlayer;
class CEnemy;
class CBullet :public CObject2D
{
public:
	CBullet();
	~CBullet() override;

	static HRESULT Load();
	static void UnLoad();
	CBullet *Create();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
    D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	int m_Life;



};

#endif // !_BULLET_H_
