#ifndef _SCORE_H_
#define _SCORE_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define SCORE_WIDTH		(20.0f)		//スコアの幅
#define SCORE_HEIGHT	(45.0f)		//スコアの高さ
#define SCORE_MAX		(8)			//スコアの最大桁数

//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void SetScore(int nScore, D3DXVECTOR3 pos, float width, float height);
void DrawScore(void);
void AddScore(int nValue);
int GetScore(void);


#endif