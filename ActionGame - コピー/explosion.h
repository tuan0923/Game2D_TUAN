#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//マクロ定義
#define MAX_EXPLOSION (128)
#define EXPLOSION_SIZE_X (50.0f)
#define EXPLOSION_SIZE_Y (50.0f)
#define NUM_EXPLOSION (100)
//
typedef enum
{
	EXPLOSION_Q = 0,
	EXPLOSION_W,
}EXPLOSION_TYPE;
//爆発構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	int nCounterAnim;
	int nPatternAnim;
	bool bUse;
	EXPLOSION_TYPE ntype;
}Explosion;
//プロトタイプ宣言
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, EXPLOSION_TYPE ntype);
#endif