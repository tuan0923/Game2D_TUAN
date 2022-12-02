//============================================================
//
// 3D����@���s���S�̏���[rogo.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _ROGO_H_
#define _ROGO_H_

#include "main.h"

//�}�N����`
#define MAX_Rogo			(128)		//�G�̍ő吔
#define NUM_Rogo			(10)		//�G�̎��
#define Rogo_SIZE			(300.0f)	//�G�̃T�C�Y

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	int nType;										//���
	bool bUse;										//�g�p���Ă��邩�ǂ���
}Rogo;


//�v���g�^�C�v�錾
void lnitRogo(void);
void UninitRogo(void);
void UpdateRogo(void);
void DrawRogo(void);
void SetRogo(D3DXVECTOR3 pos, int nType);

Rogo*GetRogo(void);

#endif 


