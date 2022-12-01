//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//=============================================================================
// インクルード
//=============================================================================
#include "object2D.h"
#include <vector>
#include <string>
#include <map>

//using namespace std;

//=============================================================================
// クラス定義
//=============================================================================
class CTexture
{
public:
	//メンバ関数
	CTexture();						//コンストラクタ
	~CTexture();					//デストラクタ

	// 初期化
	void Init();
	// 終了
	void Uninit();
	// テクスチャの割り当て(名前指定)
	LPDIRECT3DTEXTURE9 GetTexture(std::string texType) { return m_apTexture[m_texType[texType]]; }
	// テクスチャの割り当て(番号指定)
	LPDIRECT3DTEXTURE9 GetTexture(int nCnt) { return m_apTexture[nCnt]; }
	// テクスチャのパス取得処理
	std::string GetPas(int nCntTex) { return m_aPas[nCntTex]; }
	// テクスチャの総数取得処理
	int GetNum() { return m_nNumTex; }

private:
	std::vector<LPDIRECT3DTEXTURE9> m_apTexture;		//テクスチャ
	std::vector<std::string>	m_aPas;					//テクスチャのパス
	std::map<std::string, int> m_texType;			//テクスチャの種類
	int m_nNumTex;									//テクスチャの総数
};

#endif
