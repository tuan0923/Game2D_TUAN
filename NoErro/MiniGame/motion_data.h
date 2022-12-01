//===================================================================
//
// Xファイル情報 [x_file_data.h]
// Author : SHUGO KURODA
//
//===================================================================
#ifndef _MOTION_DATA_H_
#define _MOTION_DATA_H_

#include "x_file_data.h"
#include <vector>

//===================================================================
// 前方宣言
//===================================================================
class CParts;

//*******************************************************************
// 構造体宣言
//*******************************************************************
typedef struct
{
	// Xファイル情報
	SModelInfo xFile;
	// 位置
	D3DXVECTOR3 pos;
	// 基本の角度
	D3DXVECTOR3 baseRot;
	// 回転
	D3DXVECTOR3 rot;
	// ワールドマトリックス
	D3DXMATRIX mtxWorld;
	// このパーツの番号
	int nIndex;
	// 親パーツの番号
	int nParent;
}Parts;

// キー情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	// モーション再生中の位置
	D3DXVECTOR3 rot;	// モーション再生中の向き
}Key;

// モーションキー情報の構造体
typedef struct
{
	int nFrame;				// 必要フレーム数
	std::vector<Key> aKey;	// キー情報
}KeySet;

// モーション情報の構造体
typedef struct
{
	int nLoop;		// ループするかどうか
	int nNumKey;	// 総キー数
	std::vector<KeySet> aKeyInfo;	// キー設定情報
}MotionSet;

//全てのモデルモーション情報の構造体
typedef struct
{
	int nNumParts;		// パーツの総数
	int nNumMotion;		// モーション総数
	float fMove;		// 移動量
	float fJump;		// ジャンプ力
	std::vector<Parts> aParts;			//パーツの情報
	std::vector<MotionSet> aMotion;		//各モーションの情報
}ModelMotion;

#endif		// _MOTION_DATA_H_
