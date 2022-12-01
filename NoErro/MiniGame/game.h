//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "enemy_data.h"

#include "player.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScore;
class CEnemyBoss;
class CItem;
class CCamera;

//-----------------------------------------------------------------------------
// ゲーム画面クラス
//-----------------------------------------------------------------------------
class CGame
{
private:	//定数
	static const int MAX_POS_CLOUD = 250;
	static const int MIN_POS_CLOUD = 180;

public:		//メンバ関数
	CGame();
	~CGame();

	// 初期化
	HRESULT Init();
	// 終了
	void Uninit();
	// 更新
	void Update();

	// ゲームを終了するかどうかを判定
	bool CheckGameEnd();
	// 敵を生成
	void CreateEnemy();
	// ロゴを生成
	void CreateLogo(int nCounter);

	// ゲーム開始フラグを設定
	void SetStart(bool bStart) { m_bStart = bStart; }

	// プレイヤー情報の取得
	CPlayer *GetPlayer(int nNum) { return m_pPlayer[nNum]; }
	// 敵ボス情報
	CEnemyBoss* GetEnemyBoss() { return m_pEnemyBoss; }
	//Item 情報
	CItem* GetItem() { return m_pItem; }
	//カメラ情報
	CCamera* GetCamera() { return m_pCamera; }

	// ゲーム開始フラグを取得
	bool GetStart() { return m_bStart; }
	// プレイヤーのスコアをランキングに設定
	void SetPlayerScore();

private:
	// テクスチャ読み込み
	//static void LoadAll();
	// テクスチャ破棄
	//static void UnloadAll();

private:	//メンバ変数
	// プレイヤー情報
	CPlayer *m_pPlayer[CPlayer::PLAYER_MAX];
	CEnemyBoss* m_pEnemyBoss;
	CItem* m_pItem;
	CCamera* m_pCamera;

	// ゲームが始まったかどうか
	bool m_bStart;
	// ゲームが終了したかどうか
	bool m_bEnd;

	// 敵のセット情報
	EnemySetInfo m_EnemyInfo;
};

#endif	//_GAME_H_
