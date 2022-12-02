//===================================================================
//
//3D�A�N�V����(mob.h)
//Author:�匴���r
//
//===================================================================
#ifndef _MOB_H_
#define _MOB_H_

//===================================================================
//�}�N���萔
//===================================================================
#define MOB_SPEED		(0.5f)
#define MAX_MOB_PARTS	(10)
#define MAX_MOB_KEY				(4)
#define MAX_MOB_KEYSET			(3)
#define MAX_MOB_FLAME			(40.0f)

//===================================================================
//�v���C���[�̃L�[�\����
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos[MAX_MOB_PARTS];	//�ʒu
	D3DXVECTOR3 rot[MAX_MOB_PARTS];	//����
	float fMaxFlame;	//�t���[���ő吔
} MobKey;

//===================================================================
//�v���C���[�̃L�[�Z�b�g�\����
//===================================================================
typedef struct
{
	float fFlame;		//���݂̃t���[��
	bool bLoop;			//���[�v���邩�ۂ�
	bool bUse;			//�I�����Ă��邩�ۂ�
	int nNum_Key;		//�L�[�̐�
	int nUseKey;		//�g�p���̃L�[
	MobKey aMobKey[MAX_MOB_KEY];	//�L�[�\����
} MobKeySet;

//===================================================================
//�v���C���[�̃��[�V�����\����
//===================================================================
typedef struct
{
	int nUseKeySet;				//�g�p���̃L�[�Z�b�g
	int nNumKeySet;				//�L�[�Z�b�g�̐�
	MobKeySet aMobKeySet[MAX_MOB_KEYSET];	//�L�[�Z�b�g�\����
} MobMotionSet;

//===================================================================
//�v���C���[�̃p�[�c�\����
//===================================================================
typedef struct
{
	LPD3DXMESH pMesh;				//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			//�}�e���A�����ւ̃|�C���^
	DWORD nNumMat;					//�}�e���A�����
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	int nIdx;						//�C���f�b�N�X�ԍ�
	int nIdxModelParent;			//�e���f���̃C���f�b�N�X
}MobModelParts;

//===================================================================
//���f���\����
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 posOld;						//�ЂƂO�̈ʒu
	D3DXVECTOR3 move;						//�ړ���
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 size;						//�傫��
	D3DXVECTOR3 vtxMin;						//���_�̍ŏ��l
	D3DXVECTOR3 vtxMax;						//���_�̍ő�l
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	int IdxShadow;							//�e�̐ݒu
	MobModelParts aModel[MAX_MOB_PARTS];	//���f���p�[�c��
	bool bUse;								//�g�p���Ă��邩�ۂ�
	PLAYER_TYPE type;						//�f�B�X�N�����Ă�l
}MOB;

//===================================================================
//�v���g�^�C�v�錾
//===================================================================
void InitMob(void);
void UninitMob(void);
void UpdateMob(void);
void DrawMob(void);

//===================================================================
//����֐��̐錾
//===================================================================
void SetMobMove(void);
MOB *GetMob(void);
void SetMob(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type);
#endif 