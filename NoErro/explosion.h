#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "object2D.h"
class CExplosion : public CObject2D
{
public:
	CExplosion();
	~CExplosion();

	static HRESULT Load();
	static void UnLoad();
	
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CExplosion *Create();

	static const int MAX_EXPLOSION = 8;

private:
	

	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nCounterAnim;
	int m_nPatternAnim;
	bool bUse;

};

#endif // !_EXPLOSION_H_
