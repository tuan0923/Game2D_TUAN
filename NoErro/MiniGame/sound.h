//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA, SHUGO KURODA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <xaudio2.h>					// �T�E���h�Đ��ɕK�v

//-----------------------------------------------------------------------------
// �T�E���h�N���X(��{�N���X)
//-----------------------------------------------------------------------------
class CSound
{
public:
	CSound();
	~CSound();

	// �T�E���h�t�@�C��
	typedef enum
	{
		// BGM��
		SOUND_LABEL_TITLE = 0,			// �^�C�g��BGM
		SOUND_LABEL_GAME,				// �Q�[��BGM
		SOUND_LABEL_RESULT,				// ���U���gBGM
		SOUND_LABEL_BOSS,				// �{�X��BGM
		// �Q�[��SE��
		SOUND_LABEL_SE_ENTRY,			// ���@�o��
		SOUND_LABEL_SE_SHOT,			// �e����
		SOUND_LABEL_SE_SHOT2,			// �e����
		SOUND_LABEL_SE_HIT,				// �e�q�b�g
		SOUND_LABEL_SE_EXPLOSION,		// ����
		SOUND_LABEL_SE_EXPLOSION_BOSS,	// �{�X���j
		SOUND_LABEL_SE_DIE_PLAYER,		// �v���C���[����
		SOUND_LABEL_SE_DIE_BOSS,		// �{�X���j
		SOUND_LABEL_SE_ITEM,			// �A�C�e���擾
		SOUND_LABEL_SE_CLEAR,			// �Q�[���N���A
		SOUND_LABEL_SE_WARNING,			// �x��T�C����
		SOUND_LABEL_SE_WARNING2,		// �x��T�C����2
		SOUND_LABEL_SE_RUSH,			// �G�̓ːi
		// UI�֘ASE��
		SOUND_LABEL_SE_MENU_IN,			// ���j���[�C��
		SOUND_LABEL_SE_MENU_OUT,		// ���j���[�A�E�g
		SOUND_LABEL_SE_MENU_SELECT,		// �I��
		SOUND_LABEL_SE_MENU_OK,			// ����
		SOUND_LABEL_SE_CANCEL,			// �L�����Z��
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit();
	static HRESULT Play(SOUND_LABEL label);
	static void Stop(SOUND_LABEL label);
	static void Stop();

private:
	// �p�����[�^�\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	static IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y

	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};

#endif
