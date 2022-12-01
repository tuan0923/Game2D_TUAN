//=============================================================================
//
// Xファイルモーション [x_file_motion.cpp]
// Author : SHUGO KURODA
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include <stdio.h>
#include "x_file_motion.h"

#include "renderer.h"
#include "manager.h"

// 追加
//#include "motion_parts.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LINE_MAX_READING_LENGTH (256)			//一行の最大読み取り文字数

//=============================================================================
// コンストラクタ
//=============================================================================
CXFileMotion::CXFileMotion()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CXFileMotion::~CXFileMotion()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CXFileMotion::Init(HWND hWnd)
{
	// ファイルポインター宣言
	FILE *pFile = NULL;

	char cBff[LINE_MAX_READING_LENGTH];			// 一行分読み取るための変数
	char cBffHead[LINE_MAX_READING_LENGTH];		// 頭の文字を読み取るための変数
	int nNum = 0;

	// ファイルを開く
	pFile = fopen("data/TEXT/motion_pas.ini", "r");

	if (pFile == NULL)
	{//開けなかった時用
		MessageBox(hWnd, "INIファイルを開けませんでした", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	//文字列の読み取りループ処理
	while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
	{
		//文字列の分析
		sscanf(cBff, "%s", &cBffHead);

		// 文字列の中にTEX_NUMがあったら
		if (strcmp(&cBffHead[0], "MODEL_MOTION_NUM") == 0)
		{
			// モデルモーション最大数読み込み
			sscanf(cBff, "%s = %d", &cBffHead, &m_nNumMotion);
		}
		if (strcmp(&cBffHead[0], "MODEL_MOTIONSET") == 0)
		{// モデルモーション読み込みを開始

			// 一行ずつ保存
			while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
			{
				//文字列の分析
				sscanf(cBff, "%s", &cBffHead);

				if (strcmp(&cBffHead[0], "SCRIPT_FILENAME") == 0)
				{//モーションテキストの相対パス用

					//相対パス保存用
					char sPath[LINE_MAX_READING_LENGTH];

					//一行の文字列から相対パスの読み取り
					sscanf(cBff, "%s = %s", &cBffHead, &sPath[0]);

					//Xファイルの読み込み
					if (LoadMotion(&sPath[0]) == false)
					{// 読み込み失敗
						MessageBox(hWnd, "モーションテキストを開けませんでした", "警告！", MB_ICONWARNING);
						return E_FAIL;
					}
				}
				else if (strcmp(&cBffHead[0], "NAME") == 0)
				{// 名前の取得
					sscanf(cBff, "%s = %s", &cBffHead, &cBff[0]);
					// 名前と数の割り当て
					m_texType[cBff] = nNum;
					nNum++;
				}
				else if (strcmp(&cBffHead[0], "END_MODEL_MOTIONSET") == 0)
				{// モデルモーション読み込み終了
					break;
				}
			}
		}
		else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
		{//読み込み終了
			break;
		}
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CXFileMotion::Uninit()
{
	for (int nCntMotion = 0; nCntMotion < m_nNumMotion; nCntMotion++)
	{
		for (int nCntParts = 0; nCntParts < m_aMotion[nCntMotion].nNumParts; nCntParts++)
		{
			// メッシュの破棄
			if (m_aMotion[nCntMotion].aParts[nCntParts].xFile.pMesh != NULL)
			{
				m_aMotion[nCntMotion].aParts[nCntParts].xFile.pMesh->Release();
				m_aMotion[nCntMotion].aParts[nCntParts].xFile.pMesh = NULL;
			}
			// マテリアルの破棄
			if (m_aMotion[nCntMotion].aParts[nCntParts].xFile.pBuffMat != NULL)
			{
				m_aMotion[nCntMotion].aParts[nCntParts].xFile.pBuffMat->Release();
				m_aMotion[nCntMotion].aParts[nCntParts].xFile.pBuffMat = NULL;
			}
		}
	}
}

//-----------------------------------------------------------------------------
// モーション情報の読み込み
//-----------------------------------------------------------------------------
bool CXFileMotion::LoadMotion(char* pas)
{
	// ファイルポインター宣言
	FILE *pFile = NULL;

	// ファイルを開く
	pFile = fopen(pas, "r");

	if (pFile == NULL)
	{// ファイルを開けなかった場合
		return false;
	}

	// モーション情報保存用
	ModelMotion motion;
	// 一行分読み取るための変数
	char cBff[LINE_MAX_READING_LENGTH];
	// 頭の文字を読み取るための変数
	char cBffHead[LINE_MAX_READING_LENGTH];
	// パーツの読み込み
	std::vector<SModelInfo> partsXFile;

	//文字列の読み取りループ処理
	while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
	{
		// 文字読み込み用変数の初期化
		memset(&cBffHead, 0, sizeof(cBffHead));
		// 文字列の分析
		sscanf(cBff, "%s", &cBffHead);

		if (strcmp(&cBffHead[0], "MODEL_FILENAME") == 0)
		{//Xファイルの相対パス用

			// 相対パス保存用
			char sPath[LINE_MAX_READING_LENGTH];

			// 一行の文字列から相対パスの読み取り
			sscanf(cBff, "%s = %s", &cBffHead, &sPath[0]);

			// パーツの読み込み
			SModelInfo xFile = LoadParts(&sPath[0]);

			// パーツ情報の格納
			partsXFile.push_back(xFile);
		}
		else if (strcmp(&cBffHead[0], "CHARACTERSET") == 0)
		{//プレイヤーの配置用

			//プレイヤー情報の読み取りループ処理
			while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
			{
				//文字列の分析
				sscanf(cBff, "%s", &cBffHead);

				if (strcmp(&cBffHead[0], "NUM_PARTS") == 0)
				{//パーツ数
					//文字列の分析
					sscanf(cBff, "%s = %d", &cBffHead, &motion.nNumParts);
				}
				else if (strcmp(&cBffHead[0], "MOVE") == 0)
				{//移動量
					//文字列の分析
					sscanf(cBff, "%s = %f", &cBffHead, &motion.fMove);
				}
				else if (strcmp(&cBffHead[0], "JUMP") == 0)
				{//ジャンプ量
					//文字列の分析
					sscanf(cBff, "%s = %f", &cBffHead, &motion.fJump);
				}
				else if (strcmp(&cBffHead[0], "PARTSSET") == 0)
				{
					// パーツ情報保存用	
					Parts parts;

					//プレイヤーパーツ情報の読み取りループ処理
					while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
					{
						//文字列の分析
						sscanf(cBff, "%s", &cBffHead);

						if (strcmp(&cBffHead[0], "INDEX") == 0)
						{//パーツ番号
							// 文字列の分析
							sscanf(cBff, "%s = %d", &cBffHead, &parts.nIndex);
						}
						else if (strcmp(&cBffHead[0], "PARENT") == 0)
						{//現在のパーツの親
							// 文字列の分析
							sscanf(cBff, "%s = %d", &cBffHead, &parts.nParent);
						}
						else if (strcmp(&cBffHead[0], "POS") == 0)
						{//位置
							// 文字列の分析
							sscanf(cBff, "%s = %f%f%f", &cBffHead, &parts.pos.x, &parts.pos.y, &parts.pos.z);
						}
						else if (strcmp(&cBffHead[0], "ROT") == 0)
						{//回転(角度)
							// 文字列の分析
							sscanf(cBff, "%s = %f%f%f", &cBffHead, &parts.rot.x, &parts.rot.y, &parts.rot.z);
							parts.baseRot = parts.rot;
						}
						else if (strcmp(&cBffHead[0], "END_PARTSSET") == 0)
						{// パーツ読み込み終了
							parts.xFile = partsXFile[parts.nIndex];
							// パーツ情報の保存
							motion.aParts.push_back(parts);
							break;
						}
					}
				}
				else if (strcmp(&cBffHead[0], "END_CHARACTERSET") == 0)
				{//プレイヤー読み込み終了
					break;
				}
			}
		}
		else if (strcmp(&cBffHead[0], "MOTIONSET") == 0)
		{//モーション設定用

			// モーション情報保存用
			MotionSet motionInfo;

			//モーション情報の読み取りループ処理
			while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
			{
				//文字列の分析
				sscanf(cBff, "%s", &cBffHead);

				if (strcmp(&cBffHead[0], "LOOP") == 0)
				{//ループ設定
					//文字列の分析
					sscanf(cBff, "%s = %d", &cBffHead, &motionInfo.nLoop);
				}
				else if (strcmp(&cBffHead[0], "NUM_KEY") == 0)
				{//キーの数
					//文字列の分析
					sscanf(cBff, "%s = %d", &cBffHead, &motionInfo.nNumKey);
				}
				else if (strcmp(&cBffHead[0], "KEYSET") == 0)
				{
					// キー情報保存用
					KeySet keyInfo;

					//キーセット情報の読み取りループ処理
					while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
					{
						//文字列の分析
						sscanf(cBff, "%s", &cBffHead);

						if (strcmp(&cBffHead[0], "FRAME") == 0)
						{//ループ設定
							//文字列の分析
							sscanf(cBff, "%s = %d", &cBffHead, &keyInfo.nFrame);

							if (keyInfo.nFrame == 0)
							{//再生フレーム数が0の場合1にする
								keyInfo.nFrame = 1;
							}
						}
						if (strcmp(&cBffHead[0], "KEY") == 0)
						{// ループ設定

							// キー情報保存用
							Key key;

							// キー情報の読み取りループ処理
							while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
							{
								//文字列の分析
								sscanf(cBff, "%s", &cBffHead);

								if (strcmp(&cBffHead[0], "POS") == 0)
								{//モーション再生中の位置情報読み込み
								 //文字列の分析
									sscanf(cBff, "%s = %f%f%f", &cBffHead, &key.pos.x, &key.pos.y, &key.pos.z);
								}
								else if (strcmp(&cBffHead[0], "ROT") == 0)
								{//モーション再生中の回転情報読み込み
								 //文字列の分析
									sscanf(cBff, "%s = %f%f%f", &cBffHead, &key.rot.x, &key.rot.y, &key.rot.z);
								}
								else if (strcmp(&cBffHead[0], "END_KEY") == 0)
								{
									keyInfo.aKey.push_back(key);
									break;
								}
							}
						}
						else if (strcmp(&cBffHead[0], "END_KEYSET") == 0)
						{
							motionInfo.aKeyInfo.push_back(keyInfo);
							break;
						}
					}
				}
				else if (strcmp(&cBffHead[0], "END_MOTIONSET") == 0)
				{
					// モーションの総数を加算
					motion.nNumMotion++;
					motion.aMotion.push_back(motionInfo);
					break;
				}
			}
		}
		// テキストファイルを読み切った時
		else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
		{
			// モーション情報の格納
			m_aMotion.push_back(motion);
			break;
		}
	}

	//ファイルを閉じる
	fclose(pFile);

	return true;
}

//-----------------------------------------------------------------------------
// Xファイルの読み込み
//-----------------------------------------------------------------------------
SModelInfo CXFileMotion::LoadParts(const char* pas)
{
	//デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// モデル情報保存用
	SModelInfo xFile;

	//Xファイルの読み込み
	HRESULT hr = D3DXLoadMeshFromX(pas,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&xFile.pBuffMat,
		NULL,
		&xFile.nNumMat,
		&xFile.pMesh);

	if (hr != S_OK)
	{//Xファイル読み込み失敗
		//return nullptr;
	}

	// テクスチャの読み込み処理
	LoadXFileTexture(&xFile);

	return xFile;
}

//-----------------------------------------------------------------------------
// テクスチャの読み込み
//-----------------------------------------------------------------------------
void CXFileMotion::LoadXFileTexture(SModelInfo* pXFile)
{
	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pXFile->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pXFile->nNumMat; nCntMat++)
	{
		//マテリアルの設定
		//pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャがあった場合
		if ((pMat[nCntMat].pTextureFilename != NULL) && (strcmp(pMat[nCntMat].pTextureFilename, "") != 0))
		{
			//デバイスを取得する
			LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &pXFile->pTexture[nCntMat]);
		}
	}
}