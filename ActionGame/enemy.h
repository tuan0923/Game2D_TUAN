#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

//マクロ定義
#define MAX_ENEMY (128)
#define ENEMY_WIDTH (30)
#define ENEMY_HEIGHT (30)
#define NUM_ENEMY (4)

typedef enum
{
	ENEMY_Q=0,
	ENEMY_W,
	ENEMY_E
}ENEMY_TYPE;
//敵構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	float fWidth;          //幅
	float fHeight;		   //高さ
	D3DXVECTOR3 pPosOld;
	int nCounterState;
	int nCountAnimEnemy;
	int nPatternAnimEnemy;
	ENEMY_TYPE nType;
	bool bUse;

}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);
void SetEnemy(D3DXVECTOR3 pos, ENEMY_TYPE nType, D3DXVECTOR3 move);
void DeleteEnemy(int nCntEnemy);
Enemy * GetEnemy(void);

#endif // ! _ENEMY_H_
