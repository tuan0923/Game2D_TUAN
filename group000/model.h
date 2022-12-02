//----------------------------------------
//�@���f��
//----------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//�}�N����`
#define MAX_MODEL			(1)		//���f���̍ő吔
#define MODEL_SPEED			(1.0f)	//���f���̈ړ����x

//typedef enum
//{
//	PLAYER_P1 = 0,
//	PLAYER_P2
//}PLAYER_TYPE;

//���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	float diff;				//�����p
	float rotDestModel;		//�ړI�̊p�x
	int IdxShadow;			//�e�p
	bool bUse;				//�g���Ă��邩�ǂ���
	PLAYER_TYPE type;
}Model;

//�v���g�^�C�v�錾
void InitModel(void);		//���f���̏�����
void UninitModel(void);		//���f���̏I��
void UpdateModel(void);		//���f���̍X�V
void DrawModel(void);		//���f���̕`��
void MoveModel(void);		//���f���̈ړ�
Model * GetModel(void);		//���f���̏��
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//���f���̐ݒ�

#endif
