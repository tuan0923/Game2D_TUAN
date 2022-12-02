#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"
#include "game.h"
//
typedef enum
{
	ITEM_TYPE_COIN = 0,
	ITEM_TYPE_MAX
}ITEM_TYPE;
//�e�\���̂̒�`
typedef struct
{

	D3DXVECTOR3 pos;       //���݂̈ʒu�@
	D3DXVECTOR3 rot;
	float fWidth;          //��
	float fHeight;		   //����
	int nCountAnim;
	int nPatternAnim;
	ITEM_TYPE ntype;        //���
	bool bUse;
	
}ITEM;
//�}�N����`
#define MAX_ITEM (128)
#define NUM_ITEM (100)
#define ITEM_HEIGHT (60.0f)
#define ITEM_WIDTH (60.0f)
//�v���g�^�C�v�錾
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos,ITEM_TYPE type);
void CollisionItem(D3DXVECTOR3 *pPos, float fWidth, float fHeight);
void DeleteItem(int nCntItem);
ITEM*GetItem(void);
#endif // !_ITEM_H_


