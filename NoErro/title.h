#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "object.h"
class CObject2D;

class CTitle : public CObject
{
public:
	CTitle();
	~CTitle();
	//�v���g�^�C�v�錾
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};

#endif // !_TITLE_H_
