//============================================================
//
// 3D����@�C���N�̏���[Ink.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _INK_H_
#define _INK_H_

#include "main.h"

//============================================================
// �C���N�̍\���̂̒�`
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;				//���_					
	D3DXVECTOR3 rot;				//�����_
	D3DXVECTOR3 size;				//�T�C�Y
	D3DXVECTOR3 move;				//�T�C�Y
	D3DXMATRIX mtxWorld;			//
	bool bUse;						//
}Ink;

//============================================================
// �v���g�^�C�v�錾
//============================================================
void lnitInk(void);
void UninitInk(void);
void UpdateInk(void);
void DrawInk(void);
int SetInk(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionInk(int nIdxInk, D3DXVECTOR3 pos);
bool CollisionInk(
	D3DXVECTOR3* pPos,				//���݂̈ʒu
	D3DXVECTOR3* pPosOld,			//�O��̍���
	D3DXVECTOR3* pMove,				//�ړ���
	D3DXVECTOR3* pSize);			//�T�C�Y

#endif

