//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"


CObject *CObject::m_pObject[MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;


CObject::CObject()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if(m_pObject[nCnt] == nullptr)
		{
			m_pObject[nCnt] = this;
			m_nNumAll++;
			m_nID = nCnt;
			break;
		}
	 }

}

CObject::~CObject()
{
}

void CObject::ReleaseAll()
{

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_pObject[nCnt] != nullptr)
		{
			m_pObject[nCnt]->Uninit();
			delete m_pObject[nCnt];
			m_pObject[nCnt] = nullptr;
		}
	}
}

void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_pObject[nCnt] != nullptr)
		{
			m_pObject[nCnt]->Update();

		}
	}
}

void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_pObject[nCnt] != nullptr)
		{
			m_pObject[nCnt]->Draw();

		}
	}
}

CObject::EObjectType CObject::GetObjectType()
{
	return m_Type;
}


void CObject::release()
{
	int nCntID;
	nCntID = m_nID;

	delete m_pObject[nCntID];
	m_pObject[nCntID] = nullptr;
	m_nNumAll--;

}

