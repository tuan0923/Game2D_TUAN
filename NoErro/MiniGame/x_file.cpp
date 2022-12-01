//=============================================================================
//
// Xファイルマネージャー [x_file.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include <stdio.h>

#include "x_file.h"
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
CXFile::CXFile()
{
	// 変数の初期化
	m_texType.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CXFile::~CXFile()
{
}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CXFile::Init()
{
	//ファイル読み込み
	FILE *pFile = fopen("data/TEXT/XFilePas.txt", "r");

	if (pFile != NULL)
	{
		char cString[MAX_CHAR];

		//一行ずつ保存
		while (fgets(cString, MAX_CHAR, pFile) != NULL)
		{
			//文字列を保存
			fscanf(pFile, "%s", cString);
			//文字列の中にTEX_NUMがあったら
			if (strncmp("XFILE_NUM", cString, 8) == 0)
			{
				//テクスチャ最大数読み込み
				fscanf(pFile, "%*s%d", &m_nNumXFile);

				int nNum = 0;
				//一行ずつ保存
				while (fgets(cString, MAX_CHAR, pFile) != NULL)
				{
					//文字列を保存
					fscanf(pFile, "%s", cString);
					//文字列の中にPASがあったら
					if (strncmp("PAS", cString, 4) == 0)
					{
						//パスの取得
						fscanf(pFile, "%*s%s", &cString[0]);
						m_aPas.push_back(&cString[0]);

						//名前の取得
						fscanf(pFile, "%*s%*s%s", cString);
						//名前と数の割り当て
						m_texType[cString] = nNum;
						nNum++;
					}
				}
			}
			else if (strncmp("END_SCRIPT", cString, 11) == 0)
			{//テキストファイルを読み切った時
				break;
			}
		}
	}
	else
	{
		printf("テクスチャファイルが開けませんでした\n");
	}

	// ファイルを閉じる
	fclose(pFile);

	//デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	for (int nCntXFile = 0; nCntXFile < m_nNumXFile; nCntXFile++)
	{
		// テクスチャ保存用
		SModelInfo XFile;

		//Xファイルの読み込み
		D3DXLoadMeshFromX(m_aPas[nCntXFile].c_str(),
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&XFile.pBuffMat,
			NULL,
			&XFile.nNumMat,
			&XFile.pMesh);

		// テクスチャの読み込み処理
		LoadXFileTexture(XFile);

		// Xファイル情報の保存
		m_aXFile.push_back(XFile);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CXFile::Uninit()
{
	for (int nCnt = 0; nCnt < m_nNumXFile; nCnt++)
	{
		//メッシュの破棄
		if (m_aXFile[nCnt].pMesh != NULL)
		{
			m_aXFile[nCnt].pMesh->Release();
			m_aXFile[nCnt].pMesh = NULL;
		}
		//マテリアルの破棄
		if (m_aXFile[nCnt].pBuffMat != NULL)
		{
			m_aXFile[nCnt].pBuffMat->Release();
			m_aXFile[nCnt].pBuffMat = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// テクスチャ読み込み
//-----------------------------------------------------------------------------
void CXFile::LoadXFileTexture(SModelInfo& XFile)
{
	//デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();
	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)XFile.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)XFile.nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャがあった場合
		if ((pMat[nCntMat].pTextureFilename != NULL) && (strcmp(pMat[nCntMat].pTextureFilename, "") != 0))
		{//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &XFile.pTexture[nCntMat]);
		}
	}
}
