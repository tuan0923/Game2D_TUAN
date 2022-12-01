//-------------------------------------------
//
// ���S�̏��[logo_extend.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _LOGO_EXTEND_H_
#define _LOGO_EXTEND_H_

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include "logo.h"

//-------------------------------------------
// ���S�N���X
//-------------------------------------------
class CLogoExtend : public CLogo
{
private:
	// �������̎��
	enum EAnim
	{
		ANIM_NONE = 0,
		ANIM_Y_EXPAND,
		ANIM_Y_SHORTEN,
		ANIM_X_EXPAND,
		ANIM_X_SHORTEN
	};

public:
	// �R���X�g���N�^
	CLogoExtend();
	// �f�X�g���N�^
	~CLogoExtend() override;

	// ����
	static CLogoExtend* Create(const D3DXVECTOR2& size, const char* name, const int& nCount);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �������̐ݒ�
	void Pattern();

	// �����o�ϐ�
private:
	// ���̃T�C�Y�L���p
	D3DXVECTOR2 m_DefaultSize;
	// �������̎��
	EAnim m_anim;
};

#endif		// _LOGO_EXTEND_H_
