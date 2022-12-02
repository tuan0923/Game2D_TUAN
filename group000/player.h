//===================================================================
//
//3D�A�N�V����(player.h)
//Author:�匴���r
//
//===================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//===================================================================
//�}�N���萔
//===================================================================
#define PLAYER_SPEED		(0.5f)
#define MAX_PLAYER_PARTS	(10)
#define MAX_KEY				(4)
#define MAX_KEYSET			(3)
#define MAX_FLAME			(40.0f)

//===================================================================
//�v���C���[�̃L�[�\����
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos[MAX_PLAYER_PARTS];	//�ʒu
	D3DXVECTOR3 rot[MAX_PLAYER_PARTS];	//����
	float fMaxFlame;	//�t���[���ő吔
} Key;

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
	Key aKey[MAX_KEY];	//�L�[�\����
} KeySet;

//===================================================================
//�v���C���[�̃��[�V�����\����
//===================================================================
typedef struct
{
	int nUseKeySet;				//�g�p���̃L�[�Z�b�g
	int nNumKeySet;				//�L�[�Z�b�g�̐�
	KeySet aKeySet[MAX_KEYSET];	//�L�[�Z�b�g�\����
} MotionSet;

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
}ModelParts;

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
	ModelParts aModel[MAX_PLAYER_PARTS];	//���f���p�[�c��
	bool bUse;								//�g�p���Ă��邩�ۂ�
	PLAYER_TYPE type;						//�f�B�X�N�����Ă�l
}Player;

//===================================================================
//�v���g�^�C�v�錾
//===================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

//===================================================================
//����֐��̐錾
//===================================================================
void SetMove(void);
Player *GetPlayer(void);
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type);
#endif 
