#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "main.h"
#include "game.h"
//
typedef enum
{
	BLOCK_TYPE_S = 0,
	BLOCK_TYPE_MEDIUM,
	BLOCK_TYPE_MAX
}BLOCK_TYPE;
//弾構造体の定義
typedef struct
{

	D3DXVECTOR3 pos;
	bool bUse;
	float fWidth;
	float fHeight;
	BLOCK_TYPE nType;
}BLOCK;
//マクロ定義
#define BLOCK_W (300)
#define BLOCK_H (30)
#define MAX_BLOCK (128)
#define NUM_BLOCK (10)
//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, BLOCK_TYPE nType);

bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);

#endif // !_BLOCK_H_

