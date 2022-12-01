//===================================================================
//
//		�J���������̃w�b�_�[[camera.h]
//		Author:���c ����
//
//===================================================================
#ifndef _CAMERA_H_			//���̃}�N����`������Ȃ�������
#define _CAMERA_H_			//2�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"

//======================================================
//	�J�����̍\����
//======================================================
class CCamera : public CObject
{
public:
	CCamera();
	~CCamera() override;

	static CCamera *Create(const D3DXVECTOR3& posV, const D3DXVECTOR3& posR, const D3DXVECTOR3& rot);	//�C���X�^���X��������

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// ���_�ʒu�̎擾
	D3DXVECTOR3 GetPosV() { return m_posV; }
	// �����_�ʒu�̎擾
	D3DXVECTOR3 GetPosR() { return m_posR; }

	// �Ǐ]�Ώۂ̐ݒ�
	void SetPosTracking(D3DXVECTOR3 *pPosDest) { m_pPosTracking = pPosDest; }
	// �Ǐ]�t���O�̐ݒ�
	void SetTracking(bool bTracking) { m_bTracking = bTracking; }

private:
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_posV;				//���_
	D3DXVECTOR3 m_posR;				//�����_
	D3DXVECTOR3 m_vecU;				//������x�N�g��
	D3DXVECTOR3 m_rot;				//����
	D3DXVECTOR3 *m_pPosTracking;	//�Ǐ]�Ώۂ̈ʒu
	D3DXVECTOR3 m_posVDest;			//�ړI�̎��_
	D3DXVECTOR3 m_posRDest;			//�ړI�̒����_
	float m_fDistance;				//���_���璍���_�܂ł̋���
	D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
	bool m_bTracking;				//�J�����Ǐ]�����ǂ���
};

#endif
