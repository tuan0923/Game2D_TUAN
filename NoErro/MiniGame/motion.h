//===================================================================
//
//	���f�������̃w�b�_�[[motion.h]
//	Author : SHUGO KURODA
//
//===================================================================
#ifndef _MOTION_H_			//���̃}�N����`������Ȃ�������
#define _MOTION_H_			//2�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"
#include "motion_data.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CMotion : public CObject
{
	// �\����
private:
	//���[�V�����ԍ����
	struct AnimIdx
	{
		int nFrame;			// ���݂̃t���[����
		int nKeySetIdx;		// �Đ����̃L�[�Z�b�g�ԍ�
		int nMotionIdx;		// �Đ����̃��[�V�����ԍ�
	};

	// �����o�֐�
public:
	CMotion();		// �R���X�g���N�^
	virtual ~CMotion() override;	// �f�X�g���N�^

	// ����
	static CMotion* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name);

	// ������
	virtual HRESULT Init() override;
	// �I��
	virtual void Uninit() override;
	// �X�V
	virtual void Update() override;
	// �`��
	virtual void Draw() override;

	// �ʒu�ݒ�
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	// �p�x�ݒ�
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	// �ʒu�擾
	D3DXVECTOR3 GetPosition() { return m_pos; }
	// �ʒu�擾
	D3DXVECTOR3 *GetpPosition() { return &m_pos; }
	// �p�x�擾
	D3DXVECTOR3 GetRotation() { return m_rot; }
	// �ő�T�C�Y�擾
	D3DXVECTOR3 GetSizeMax() { return m_vtxMax; }
	// �ŏ��T�C�Y�擾
	D3DXVECTOR3 GetSizeMin() { return m_vtxMin; }
	// ���[�V�������̐ݒ�
	void BindMotion(ModelMotion motion) { m_motion = motion; }

protected:
	// ���[�V�����Đ�
	void Motion();

private:
	// ���[�V�����ύX
	void Change(int nMotion, int nKey);

	// �����o�ϐ�
private:
	//���[�V�������
	ModelMotion m_motion;
	// ���݂̃��[�V�����ԍ����
	AnimIdx m_animIdx;
	//�ʒu
	D3DXVECTOR3 m_pos;
	//��]
	D3DXVECTOR3 m_rot;
	//���f���̍ő�T�C�Y,�ŏ��T�C�Y
	D3DXVECTOR3 m_vtxMax, m_vtxMin;
	//���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxWorld;
};

#endif		// _MOTION_H_
