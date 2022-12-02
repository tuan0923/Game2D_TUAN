#ifndef _GAME_H_
#define _GAME_H_ 
#include "main.h"
#include "player.h"
#include "input.h"
#include "bg.h"
#include "block.h"
#include "item.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "sound.h"
#include "score.h"
#include "time.h"
#include "enemy.h"
#include "explosion.h"
#include "fade.h"
//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

#endif