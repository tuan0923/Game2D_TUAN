//=============================================================================
//
// ベースシーン処理 [base.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _BASE_H_
#define _BASE_H_

#include "renderer.h"

//-----------------------------------------------------------------------------
// ベースクラス(基本クラス)
//-----------------------------------------------------------------------------
class CBase
{
public:
	enum EBase
	{// シーンの種類
		BASE_NONE = 0,
		BASE_TITLE,
		BASE_GAME,
		BASE_RESULT,
		BASE_MAX
	};

	CBase();
	virtual ~CBase();

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;

	void SetType(EBase type) { m_type = type; }
	EBase GetType() { return m_type; }

private:
	// シーンの種類
	EBase m_type;
};

#endif
