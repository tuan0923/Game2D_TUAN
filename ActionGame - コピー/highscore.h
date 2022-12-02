#ifndef _HIGHSCORE_H_		//このマクロ定義がされなかったら
#define _HIGHSCORE_H_		//2重インクルード防止のマクロ定義

//マクロ定義
#define MAX_HIGHSCORE		(8)			//最大スコア数

//プロトタイプ宣言
void InitHighScore(void);
void UninitHighScore(void);
void UpdateHighScore(void);
void DrawHighScore(void);
void SetHighScore(int nScore);
void AddHighScore(int nValue);
int GetHighScore(void);
void SaveHighScore(void);
void LoadHighScore(void);
#endif 

