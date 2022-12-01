//=============================================================================
//
// Xファイルモーション [x_file_motion.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _X_FILE_MOTION_H_
#define _X_FILE_MOTION_H_

#include "motion_data.h"
#include <vector>
#include <string>
#include <map>

//using namespace std;

//=============================================================================
// クラス定義
//=============================================================================
class CXFileMotion
{
	// メンバ関数
public:
	CXFileMotion();					//コンストラクタ
	~CXFileMotion();				//デストラクタ

	// 初期化
	HRESULT Init(HWND hWnd);
	// 終了
	void Uninit();
	// モーション情報の読み込み
	bool LoadMotion(char *pas);
	// Xファイル情報の取得(名前指定)
	ModelMotion GetMotion(std::string texType) { return m_aMotion[m_texType[texType]]; }
	// Xファイル情報の取得(番号指定)
	ModelMotion GetMotion(int nCnt) { return m_aMotion[nCnt]; }

private:
	// パーツの読み込み
	SModelInfo LoadParts(const char* pas);
	// テクスチャの読み込み
	void LoadXFileTexture(SModelInfo* pXFile);

	// メンバ変数
private:
	std::vector<ModelMotion> m_aMotion;		// モーション情報
	std::vector<std::string> m_aPas;		// Xファイルのパス
	std::map<std::string, int> m_texType;	// Xファイルの種類
	int m_nNumMotion;						// Xファイルの総数
};

#endif	//_X_FILE_MOTION_H_
