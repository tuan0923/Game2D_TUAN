//----------------------------------------
//�@�v���C���[
//----------------------------------------
#ifndef _MODEL2_H_
#define _MODEL2_H_

#include "main.h"

//�}�N����`
#define MAX_PLAYER			(1)		//�v���C���[�̍ő吔
#define PLAYER_SPEED		(3.0f)	//�v���C���[�̈ړ����x
#define MAX_PARTS			(12)	//�ő�p�[�c��

//���f���̍\����
typedef struct
{
	LPD3DXMESH pMesh;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	//�}�e���A�����ւ̃|�C���^
	DWORD nNumMat;			//�}�e���A�����̐�
	D3DXMATRIX mtxWorld;	//���[���h�}�g���N�X
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//�p�x
	int nIdxModelParent;	//�e���f���̃C���f�b�N�X
}ModelParts;

/**/
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 move;		//�ړ���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���N�X
	D3DXVECTOR3 vtxMin;		//���_�̍ŏ��l���擾�p
	D3DXVECTOR3 vtxMax;		//���_�̍ő�l���擾�p
	D3DXVECTOR3 size;		//�T�C�Y�ۑ��p
}Test;

typedef enum
{
	ROT_UP = 0,
	ROT_DOWN,
	ROT_RIGHT,
	ROT_LEFT
}PlayerRot;

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 move;		//�ړ���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���N�X
	float diff;				//�����p
	float rotDest;			//�ړI�̊p�x
	int IdxShadow;			//�e�p
	D3DXVECTOR3 vtxMin;		//���_�̍ŏ��l���擾�p
	D3DXVECTOR3 vtxMax;		//���_�̍ő�l���擾�p
	D3DXVECTOR3 size;		//�T�C�Y�ۑ��p
	ModelParts aModel[MAX_PARTS];	//���f���̏��[�ő�p�[�c����]
	bool bIsJumping;
	PlayerRot PlayerRot;
}Model2;

//�v���g�^�C�v�錾
void InitPlayer(void);		//�v���C���[�̏�����
void UninitPlayer(void);	//�v���C���[�̏I��
void UpdatePlayer(void);	//�v���C���[�̍X�V
void DrawPlayer(void);		//�v���C���[�̕`��
void MovePlayer(void);		//�v���C���[�̈ړ�
Model2 * GetModel2(void);	//�v���C���[�̏��
void MotionPlayer(int nMotion);		//�v���C���[�̃��[�V�����ݒ�
void SetMotion(int nSet);	//���[�V������ݒ肷��

#endif
//
////=======================================
////   model.h
////=======================================
//#ifndef _MODEL2_H_
//#define _MODEL2_H_	
//#include "main.h"
//#include "game.h"
////�}�N����`
//#define SPEED (1.50f)
//#define MODEL_MAX (128)
//#define NUM_MODEL (2)
//typedef enum
//{
//	MODEL_TYPE_BUS = 0,
//	MODEL_TYPE_MAX2
//}MODEL_TYPE2;
////�e�̍\����
//typedef struct
//{
//	D3DXVECTOR3 move;
//	D3DXVECTOR3 pos;							//�ʒu
//	D3DXCOLOR col;								//�F
//	D3DXVECTOR3 rot;
//	D3DXVECTOR3 rotDestModel;
//	D3DXMATRIX mtxWorld;
//	D3DXVECTOR3 vtxMinModel;
//	D3DXVECTOR3 vtxMaxModel;
//	D3DXVECTOR3 scaleVector;
//	MODEL_TYPE2 type;
//	bool bUse;
//
//}MODEL2;
//
////�v���g�^�C�v�錾
//void InitModel2(void);
//void UninitModel2(void);
//void UpdateModel2(void);
//void DrawModel2(void);
//void SetModel2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL_TYPE2 type);
//void CollisionModel2(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld,/* D3DXVECTOR3 *pMove,*/ D3DXVECTOR3 size);
//MODEL2 *GetModel2(void);
//#endif