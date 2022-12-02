//----------------------------------------
//�@�f�B�X�N
//----------------------------------------
#ifndef _DISC_H_
#define _DISC_H_

#include "main.h"

//�f�B�X�N�̏��
typedef enum
{
	STATUS_WAITING = 0,	//�v���C���[�������Ă�����
	STATUS_MOVING		//������ꂽ���
}DISC_STATUS;

//�f�B�X�N�̓������̎��
typedef enum
{
	SHOT_NOMAL = 0,	//�ʏ�O��(�����Ă�������ɐ^������)
	SHOT_CURVE,		//�J�[�u�O��
	SHOT_UP			//������ɗ��Ƃ��܂�
}DISC_SHOT;

//�f�B�X�N�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//�p�x
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;			//�J���[
	D3DXMATRIX mtxWorld;	//���[���h�}�g���N�X
	bool bUse;				//�g�p���Ă��邩�ǂ���
	float speed;			//�ړ��X�s�[�h
	DISC_STATUS status;		//�f�B�X�N�̏��
	float gravity;			//�d��
	D3DXVECTOR3 vtxMin;		//���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;		//���f���̍ő�l
	D3DXVECTOR3 size;		//�T�C�Y
	int type;				//�v���C���[�̂ǂ����������Ă��邩
}Disc;

//�v���g�^�C�v�錾
void InitDisc(void);		//�f�B�X�N�̏���������
void UninitDisc(void);		//�f�B�X�N�̏I������
void UpdateDisc(void);		//�f�B�X�N�̍X�V����
void DrawDisc(void);		//�f�B�X�N�̕`�揈��
void SetPosDisc(D3DXVECTOR3 pos, int type);		//�f�B�X�N�̏����ʒu�ݒ�
void SetMoveDisc(D3DXVECTOR3 rot, float speed, DISC_SHOT shot, int type);	//�f�B�X�N�̋O���ݒ�
void CollisionDisc_Player(D3DXVECTOR3 *pos, D3DXVECTOR3 size, int type);	//�f�B�X�N�ƃv���C���[�̓����蔻��(�L���b�`�̏���)
void SetPositionDisc(D3DXVECTOR3 pos, int type);	//�v���C���[���f�B�X�N�����Ă�悤�ɂȂ鏈��

#endif


