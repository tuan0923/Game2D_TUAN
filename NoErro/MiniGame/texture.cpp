//=============================================================================
//
// テクスチャマネージャー [texture.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include <stdio.h>

#include "texture.h"
#include "renderer.h"
#include "manager.h"

//================================================
// マクロ定義
//================================================
#define MAX_CHAR		(128)		// 最大読み取り文字数

//================================================
// 静的メンバ変数宣言
//================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	// 変数の初期化
	m_texType.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CTexture::Init()
{
	// ファイル読み込み
	FILE *pFile = fopen("data/TEXT/texPas.txt", "r");

	if (pFile == NULL)
	{// ファイルを開けなかった場合
		return;
	}

	char cScanf[MAX_CHAR];		//一行分読み取るための変数
	char cScanfHead[MAX_CHAR];	//頭の文字を読み取るための変数
	bool bReadScript = false;	//スクリプトを読み込むかどうか
	int nNum = 0;

	// 一行ずつ保存
	while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
	{
		// 文字列の分析
		sscanf(cScanf, "%s", &cScanfHead);

		if (!bReadScript && strcmp(&cScanfHead[0], "SCRIPT") == 0)
		{// スクリプトの読み込みを開始
			bReadScript = true;
		}
		else if (bReadScript)
		{// SCRIPT読み込みを開始したら

			// 文字列の中にTEX_NUMがあったら
			if (strcmp(&cScanfHead[0], "TEX_NUM") == 0)
			{
				// テクスチャ最大数読み込み
				sscanf(cScanf, "%s = %d", &cScanfHead, &m_nNumTex);
			}
			if (strcmp(&cScanfHead[0], "TEXSET") == 0)
			{// テクスチャ読み込みを開始

				// 一行ずつ保存
				while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
				{
					// 文字列の分析
					sscanf(cScanf, "%s", &cScanfHead);

					// 文字列の中にPASがあったら
					if (strcmp(&cScanfHead[0], "PAS") == 0)
					{// パスの取得
						sscanf(cScanf, "%s = %s", &cScanfHead, &cScanf[0]);
						m_aPas.push_back(&cScanf[0]);
					}
					else if (strcmp(&cScanfHead[0], "NAME") == 0)
					{// 名前の取得
						sscanf(cScanf, "%s = %s", &cScanfHead, &cScanf[0]);
						// 名前と数の割り当て
						m_texType[cScanf] = nNum;
						nNum++;
					}
					else if (strcmp(&cScanfHead[0], "END_TEXSET") == 0)
					{// テクスチャ読み込み終了
						break;
					}
				}
			}
			else if (strcmp(&cScanfHead[0], "END_SCRIPT") == 0)
			{// テキストファイルを読み切った時
				break;
			}
		}
	}

	// ファイルを閉じる
	fclose(pFile);

	// デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	for (int nCntTex = 0; nCntTex < m_nNumTex; nCntTex++)
	{
		// テクスチャ保存用
		LPDIRECT3DTEXTURE9 pTexBuffer = nullptr;

		// テクスチャの生成
		D3DXCreateTextureFromFile(pDevice, m_aPas[nCntTex].c_str(), &pTexBuffer);

		// テクスチャの割り当て
		m_apTexture.push_back(pTexBuffer);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CTexture::Uninit()
{
	for (int nCntTexture = 0; nCntTexture < m_nNumTex; nCntTexture++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}
