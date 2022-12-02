//----------------------------------------
//�@�S�[��
//----------------------------------------
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"

//�S�[���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	float fWidth;			//��
	float fHeight;			//����
}Goal;

void InitGoal(float X, float Z);	//�S�[���̏���������	����(�����̔��a, �c���̔��a)
void UninitGoal(void);		//�S�[���̏I������
void UpdateGoal(void);		//�S�[���̍X�V����
void DrawGoal(void);		//�S�[���̕`�揈��
void CollisionGoal(D3DXVECTOR3 pos, bool *bUse, int type);	//�S�[���̓����蔻��

#endif