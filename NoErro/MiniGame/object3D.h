//===================================================================
//
//		�|���S�������̃w�b�_�[[polygon.h]
//		Author:SHUGO KURODA
//
//===================================================================
#ifndef _POLYGON_H_			//���̃}�N����`������Ȃ�������
#define _POLYGON_H_			//2�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"

//======================================================
//	�}�N����`
//======================================================
#define POLYGON_SIZE	(4000.0f)	//�|���S���̃T�C�Y

//======================================================
//	�N���X�錾
//======================================================
class CObject3D : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	static const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);	//���W�E�@���E�J���[�E�e�N�X�`��;
	// ���_�̐�
	static const int MAX_VERTEX = 4;

	// ���_�f�[�^
	struct VERTEX_3D
	{
		D3DXVECTOR3 pos;		//���_���W
		D3DXVECTOR3 nor;		//�@���x�N�g��
		D3DCOLOR col;			//���_�J���[
		D3DXVECTOR2 tex;		//�e�N�X�`�����W
	};

	CObject3D();
	~CObject3D() override;

	static CObject3D *Create(const D3DXVECTOR3& pos);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }

	// �e�N�X�`���̐ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 Texture) { m_pTexture = Texture; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;		//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//����
	D3DXMATRIX	m_mtxWorld;	//���[���h�}�g���b�N�X
};

#endif