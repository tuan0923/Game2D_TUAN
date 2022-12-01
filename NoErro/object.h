#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//object　クラス
class CObject
{
public:
	enum EObjectType
	{
		OBJECT_PLAYER,
		OBJECT_BULLET,
		OBJECT_EXPLOSION,
		OBJECT_ENEMY,
		OBJECT_MAX
	};
	CObject();
	virtual~CObject();

	virtual HRESULT Init()=0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual D3DXVECTOR3 GetPos() =0;
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();
	
	void SetObjectType(EObjectType objType) { m_Type = objType; }
	EObjectType GetObjectType();
	static CObject** GetObject() { return  m_pObject ; }

protected:

	void release();

private:	
	static CObject* m_pObject[MAX_OBJECT];
	static int m_nNumAll;
	int m_nID;
	EObjectType  m_Type;
	
};

#endif // !_OBJECT_H_
