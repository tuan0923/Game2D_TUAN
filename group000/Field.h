//=======================================
//
//   Field.h
//  Author: �e���A��
//
//=======================================
#ifndef _FIELD_H_
#define _FIELD_H_	

#include "main.h"
#include "game.h"

typedef enum
{
	Field_TYPE_WALL_RED = 0,
	Field_TYPE_WALL_BLUE,
	Field_TYPE_YUKA_RED,
	Field_TYPE_YUKA_BLUE,
	Field_TYPE_WALL_NAKA,
	Field_TYPE_KANSHA,
	Field_TYPE_MINIROBOT,
	Field_TYPE_ROBOT,
	Field_TYPE_MINION,
	Field_TYPE_BALLOON
}Field_TYPE;
//�e�̍\����
typedef struct
{
	D3DXVECTOR3 move;
	D3DXVECTOR3 pos;							//�ʒu
	D3DXCOLOR col;								//�F
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDestField;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 vtxMinField;
	D3DXVECTOR3 vtxMaxField;
	D3DXVECTOR3 scaleVectorField;
	Field_TYPE type;
	bool bUse;

}Field;

//�v���g�^�C�v�錾
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);
void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scaleVectorField, Field_TYPE type);
bool CollisionField(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size);
Field *GetField(void);

#endif