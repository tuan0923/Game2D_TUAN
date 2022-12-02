//===================================================================
//ファイルヘッダ
//===================================================================

#ifndef _MAIN_H_

#define _MAIN_H_	

#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//ビルド時の警告対処用マクロ
#include "dinput.h"						//入力処理に必要
#include "xinput.h"						//ジョイパッド処理に必要
#include "xaudio2.h"					//サウンド処理に必要


//ライブラリリンク
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//(d3d9.lib)の各様ライブラリ
#pragma comment(lib,"dxguid.lib")	
#pragma comment(lib,"winmm.lib")	
#pragma comment(lib,"dinput8.lib")

//マクロ定義
#define SCREEN_WIDTH	(1280)		//ウィンドウ幅
#define SCREEN_HEIGHT	(720)		//ウィンドウ高さ
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;
//画面（モード）
typedef enum
{
	MODE_TITLE = 0,
	MODE_HOWTO,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;
//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
#endif 
