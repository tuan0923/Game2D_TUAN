//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "renderer.h"
#include "player.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;
class CPlayer;
class CCamera;

//-----------------------------------------------------------------------------
// �^�C�g����ʃN���X
//-----------------------------------------------------------------------------
class CTitle
{
public:
	enum TITLE_OBJ
	{//�w�i�̎��
		BG_SKY = 0,		// �w�i�̋�
		LOGO_PLAYER,	// �v���C���[���S
		LOGO_TITLE,		// �^�C�g�����S
		LOGO_PRESS,		// PRESS���S
		BG_FADE,		// ��ʂ𔖈Â�����p
		LOGO_TUTORIAL,	// �`���[�g���A��
		LOGO_SHADOW,	// �v���C���[���S(��)
		OBJ_MAX			// �w�i�̍ő吔
	};

public:
	CTitle();
	~CTitle();

	//�����o�֐�
	HRESULT Init();
	void Uninit();
	void Update();

	// �v���C���[���
	CPlayer* GetPlayer() { return m_pPlayer[0]; }
	//�J�������
	CCamera* GetCamera() { return m_pCamera; }

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[OBJ_MAX];		//�e�N�X�`���̃|�C���^
	CPlayer* m_pPlayer[CPlayer::PLAYER_MAX];
	CCamera* m_pCamera;
	CObject2D *m_apObject2D[OBJ_MAX - 1];
	bool m_bPush;
	// �L�[�{�[�h�ŎQ���������ǂ���
	bool m_bEntryKeyboard;
	// �Q���ԍ�
	int m_nEntryNum;
	int m_nCounter;
	D3DXVECTOR3 m_move;		// �ړ���
};

#endif		// _TITLE_H_
