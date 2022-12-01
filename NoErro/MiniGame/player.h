//===================================================================
//
//	プレイヤーの処理[player.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object2D.h"
#include "motion.h"

//*******************************************************************
//	前方宣言
//*******************************************************************
class CLife;
class CScore;

//*******************************************************************
//	プレイヤークラスの定義
//*******************************************************************
class CPlayer : public CMotion
{
private:
	//プレイヤーのサイズ(X)
	static const float SIZE_X;
	// プレイヤーのサイズ(Y)
	static const float SIZE_Y;
	// プレイヤーの基本移動量
	static const float MOVE_DEFAULT;
	// アニメーション間隔
	static const int ANIM_INTERVAL;
	// アニメーション最大数
	static const int MAX_ANIM;
	// U座標の最大分割数
	static const int DIVISION_U;
	// V座標の最大分割数
	static const int DIVISION_V;
	// プレイヤーのデフォルトカラー
	static const D3DXCOLOR DEFAULT_COL;
	// 最大オプション数
	static const int MAX_OPTION = 4;
	// デフォルト残機数
	static const int DEFAULT_LIFE;

public:
	// プレイヤー
	enum PLAYER
	{
		PLAYER_1 = 0,	//1P
		PLAYER_2,		//2P
		PLAYER_3,		//3P
		PLAYER_4,		//4P
		PLAYER_MAX
	};

	//状態
	enum STATE
	{
		STATE_NORMAL = 0,	// 通常
		STATE_RUN,			// 走る
		STATE_JUMP,			// ジャンプ
		STATE_ATTACK,		// 攻撃
		STATE_DIE,			// 死亡状態
		STATE_INAVALANCHE,	// 雪崩に巻き込まれている状態
		STATE_MAX
	};

	//アニメーション番号
	enum ANIMTYPE
	{
		TYPE_NEUTRAL = 0,
		TYPE_UP,
		TYPE_DOWN,
		TYPE_MAX
	};

	//メンバ関数
public:

	// コンストラクタ
	CPlayer();
	// デストラクタ
	~CPlayer() override;

	// 生成
	static CPlayer *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name, int nPlayryNum);	//インスタンス生成処理

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;
	// 移動
	void Move();
	// ジャンプ
	void Jump();
	// 状態管理
	void State();
	// ダメージ処理
	void Damage();
	// 死亡処理
	void Die();

	// 状態の取得
	STATE GetState() { return m_state; }
	// スコア情報の取得
	CScore *GetScore() { return m_pScore; }
	// 死亡状態の取得
	bool GetDie() { return m_bDie; }
	// 過去の位置を取得
	D3DXVECTOR3 GetPositionOld() { return m_posOld; }
	
	// 移動量の設定
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }
	// 移動量Xの設定
	void SetMoveX(const float& fmove) { m_move.x = fmove; }
	// 移動量Zの設定
	void SetMoveZ(const float& fmove) { m_move.z = fmove; }
	// 移動量Yの設定
	void SetMoveY(const float& fmove) { m_move.y = fmove; }
	// 状態の設定
	void SetState(const STATE& inState) { m_state = inState; }

	// ジャンプフラグの設定
	void SetJumping(const bool& bJumping) { m_bIsJumping = bJumping; }
	// キーボード使用フラグの設定
	void SetKeyboard(const bool& bControl) { m_bControlKeyboard = bControl; }
	// ゲームパッド番号の設定
	void SetGamePadNum(const int& nNum) { m_nGamePadNum = nNum; }
	// ゲーム開始フラグの設定
	void SetStart(const bool& bStart) { m_bStart = bStart; }

private:	//メンバ変数

	// ライフのポインタ
	CLife *m_pLife;
	// スコアのポインタ
	CScore *m_pScore;

	//移動量
	D3DXVECTOR3 m_move;
	//前回の位置
	D3DXVECTOR3 m_posOld;
	//状態
	STATE m_state;
	//状態カウンター
	int m_nCntState;
	//攻撃カウンター
	int m_nCntAttack;
	//アニメーションカウンター
	int m_nCntAnim;
	//アニメーションのパターンNo.
	int m_nPatternAnim;
	//アニメーション遷移までの硬直カウンター
	int m_nCntAnimMove;
	//現在のアニメーションV番号
	int m_nPatterAnimV;
	//テクスチャアニメーションの種類
	ANIMTYPE m_nTexRotType;

	// プレイヤーの番号
	int m_nPlayerNum;
	// 使うゲームパッドの番号
	int m_nGamePadNum;

	// ジャンプしているかどうか
	bool m_bIsJumping;
	//プレイヤーが操作できるかどうか
	bool m_bControl;
	// キーボードで操作しているかどうか
	bool m_bControlKeyboard;
	//海に入ったかどうか
	bool m_bInSea;
	//雪崩を抜けるためのキー(ボタン)入力回数
	int m_nPushButton;

	// ゲームを開始しているかどうか
	bool m_bStart;
	// 死亡したかどうか
	bool m_bDie;
};

#endif	//_PLAYER_H_
