//===================================================================
//
//3D�A�N�V����(shadow.h)
//Author:�匴���r
//
//===================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//===================================================================
//�}�N���萔
//===================================================================
#define MAX_SHADOW	(128)	//�e�̍ő吔

//===================================================================
//�e�̍\���̐ݒ�
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	bool bUse;				//�g�p���Ă��邩
}Shadow;

//===================================================================
//�v���g�^�C�v�錾
//===================================================================
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void UnsetShadow(int nIdxShadow);

#endif 