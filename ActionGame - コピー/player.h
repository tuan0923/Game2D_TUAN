#include"main.h"
#include "game.h"
#ifndef _PLAYER_H_
#define _PLAYER_H_
//#define D3DX_PI	(3.14f)
#define PLAYER_WIDTH (40.0f)
#define PLAYER_HEIGTH (80.0f)
//プレイヤーの構造体
typedef struct
{
	int nCounterAnimPlayer;
	int nPatternAnimPlayer;
	int nDirectionMove;
	int nCounterState;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 posOld;
	bool bIsJumping;
	bool bDisp;
}PLAYER;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(void);
#endif