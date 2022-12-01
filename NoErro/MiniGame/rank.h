//=============================================================================
//
// �����N���� [rank.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _RANK_H_
#define _RANK_H_

#include "object2D.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScore;

//*****************************************************************************
// �����L���O�N���X(�h���N���X)
//*****************************************************************************
class CRank : public CObject
{
public:
	// �ő僉���L���O�X�R�A��
	static const int MAX_RANKING = 5;
	// �ő�v���C���[�X�R�A��
	static const int MAX_PLAYER_SCORE = 2;

	enum TYPE
	{//�w�i�̎��
		TYPE_PLAYER1 = 0,	// �v���C���[1
		TYPE_PLAYER2,		// �v���C���[2
		TYPE_BG,			// �w�i
		TYPE_RANK,			// �����L���OUI
		TYPE_MAX			// �w�i�̍ő吔
	};

	CRank();
	~CRank();

	static CRank *Create();
	static HRESULT Load();		// �e�N�X�`���̓ǂݍ���
	static void Unload();		// �e�N�X�`���̍폜

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// �v���C���[�̃X�R�A�ݒ�
	static void SetScore(int nScore, int nPlayer) { m_nScorePlayer[nPlayer] = nScore; }

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	//�e�N�X�`���̃|�C���^
	static int m_nScorePlayer[MAX_PLAYER_SCORE];
	// �X�R�A�i�[�p
	CScore* m_pScore[MAX_RANKING + MAX_PLAYER_SCORE];
	// �I�u�W�F�N�g�̃|�C���^
	CObject2D* m_apObject2D[TYPE_MAX];
	// �X�R�A�i�[�p
	int m_aScore[MAX_RANKING + MAX_PLAYER_SCORE];
	bool m_bMyScoreFade[MAX_RANKING + MAX_PLAYER_SCORE];
	bool m_bNextMode;
};

#endif
