//=============================================================================
//
//	プレイヤー処理[player.cpp]
//	Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "sound.h"
#include "renderer.h"

#include "library.h"

#include "bg.h"
#include "spray.h"
#include "bullet.h"
#include "player.h"
#include "explosion.h"
#include "ui.h"
#include "gauge.h"
#include "life.h"
#include "score.h"

#include "rank.h"

// 追加
#include "model_obstacle.h"
#include "game.h"
#include "camera.h"
#include "x_file_motion.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define PLAYER_UI_SIZE				(D3DXVECTOR2(200.0f, 50.0f))
#define LIFE_UI_SIZE				(D3DXVECTOR2(120.0f, 30.0f))
#define LEVEL_UI_SIZE				(D3DXVECTOR2(50.0f, 50.0f))
#define ATTACK_INTERVAL				(7)
#define JOYKEY_LEFT_STICK_UP		(-0.2f)
#define JOYKEY_LEFT_STICK_DOWN		(0.2f)

#define FIELD_SIZE_WIDTH			(130.0f)
#define FIELD_SIZE_HEIGHT			(250.0f)
#define FIELD_SIZE_HEIGHT_CAMERA	(70.0f)

#define PLAYER_SIZE					(16.0f)

// 重力
#define GRAVITY			(0.1f)
// ジャンプ力
#define JUMP_POWER		(2.0f)

//-----------------------------------------------------------------------------
// using宣言
//-----------------------------------------------------------------------------
using namespace LibrarySpace;

//*****************************************************************************
// 定数宣言
//*****************************************************************************
const float CPlayer::SIZE_X = 90.0f;
const float CPlayer::SIZE_Y = 40.0f;
const float CPlayer::MOVE_DEFAULT = 0.35f;
// アニメーション間隔
const int CPlayer::ANIM_INTERVAL = 5;
// アニメーション最大数
const int CPlayer::MAX_ANIM = 2;
// U座標の最大分割数
const int CPlayer::DIVISION_U = 2;
// V座標の最大分割数
const int CPlayer::DIVISION_V = 4;
// プレイヤーのデフォルトカラー
const D3DXCOLOR CPlayer::DEFAULT_COL = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
// デフォルト残機
const int CPlayer::DEFAULT_LIFE = 2;

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
CPlayer::CPlayer() :
	m_move(0.0f, 0.0f, 0.0f), m_posOld(0.0f, 0.0f, 0.0f), m_state(STATE_NORMAL), m_nCntState(0), m_nCntAttack(0), m_nCntAnim(0), m_nPatternAnim(0), m_nCntAnimMove(0), m_bControlKeyboard(false), m_nGamePadNum(0),
	m_nTexRotType(TYPE_NEUTRAL), m_nPlayerNum(0), m_bIsJumping(false), m_bControl(false), m_bInSea(false), m_pLife(nullptr), m_pScore(nullptr), m_bDie(false), m_bStart(false)
{
	//オブジェクトの種類設定
	SetType(EObject::OBJ_PLAYER);
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

//-----------------------------------------------------------------------------
// インスタンス生成処理
//-----------------------------------------------------------------------------
CPlayer *CPlayer::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name, int nPlayerNum)
{
	//インスタンス生成
	CPlayer *pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		// 位置設定
		pPlayer->SetPosition(pos);
		// 角度設定
		pPlayer->SetRotation(rot);
		// Xファイルの設定
		pPlayer->BindMotion(CManager::GetManager()->GetMotion()->GetMotion(name));
		// 生成処理
		pPlayer->Init();
		// プレイヤー番号の設定
		pPlayer->m_nPlayerNum = nPlayerNum;
	}

	return pPlayer;
}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT CPlayer::Init()
{
	// スコアの生成
	CScore::Create(D3DXVECTOR3(250.0f, 25.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 20);

	// 操作可能状態にする
	m_bControl = true;

	// 初期化
	CMotion::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CPlayer::Uninit()
{
	CMotion::Uninit();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CPlayer::Update()
{
	//前回の位置を保存
	m_posOld = GetPosition();

	// 位置情報を取得
	D3DXVECTOR3 pos = CMotion::GetPosition();
	// サイズの取得
 	D3DXVECTOR3 size = GetSizeMax();

	// 操作できる状態なら && 死亡していないなら
	if (m_bControl == true && m_state != STATE_DIE)
	{
		// 移動処理
		Move();

		// ジャンプしていなければ
		if (m_bIsJumping == false)
		{
			// キーボード情報の取得
			CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
			// ジョイパッド情報の取得
			CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

			// キーボード操作の場合
			if (m_bControlKeyboard == true &&
				pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_ATTACK) == true)
			{// SPACEキー押下

				// ジャンプ力の設定
				m_move.y = JUMP_POWER;

				// ジャンプフラグの設定
				m_bIsJumping = true;
			}
			// ゲームパッド操作の場合
			else if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_A, m_nGamePadNum) == true)
			{// Aボタン押下

				// ジャンプ力の設定
				m_move.y = JUMP_POWER;

				// ジャンプフラグの設定
				m_bIsJumping = true;
			}
		}

		// 重力負荷をかける
		m_move.y -= GRAVITY;
	}
	
	//プレイヤーが雪崩に巻き込まれていたら
	if (m_state == STATE_INAVALANCHE)
	{
		// キーボード情報の取得
		CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
		// ジョイパッド情報の取得
		CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

		//プレイヤーを後退させる
		m_move.z -= 1.0f;

		if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_OK))
		{
			m_nPushButton++;
			if (m_nPushButton >= 1/*何回押したら雪崩を抜けるか*/)
			{
				m_state = STATE_NORMAL;
			}
		}
	}

	// 移動量の加算
	pos += m_move;

	// 障害物の当たり判定
	CObstacle::CollisionAll(&pos, m_nPlayerNum);

	// 移動量の減衰
	m_move.x -= m_move.x * 0.2f;
	m_move.z -= m_move.z * 0.2f;

	//壁・床の当たり判定処理
	if (pos.x - (size.x / 2) <= -FIELD_SIZE_WIDTH / 2)
	{//左壁
		pos.x = (-FIELD_SIZE_WIDTH / 2) + (size.x / 2);
	}
	else if (pos.x + (size.x / 2) >= FIELD_SIZE_WIDTH / 2)
	{//右壁
		pos.x = (FIELD_SIZE_WIDTH / 2) - (size.x / 2);
	}
	//if (g_Player.pos.z + (PLAYER_WIDTH / 2) >= 400.0f / 2)
	//{//奥壁
	//	g_Player.pos.z = (400.0f / 2) - (PLAYER_WIDTH / 2);
	//}

	// ゲーム参加中であれば
	if (m_bStart == true)
	{
		// カメラ位置の取得
		D3DXVECTOR3 posCamera = CManager::GetManager()->GetGame()->GetCamera()->GetPosV();

		if (pos.z - (size.z / 2) <= posCamera.z + FIELD_SIZE_HEIGHT_CAMERA)
		{//手前壁
			pos.z = (posCamera.z + FIELD_SIZE_HEIGHT_CAMERA) + (size.z / 2);
		}
	}
	// ロビー待機中であれば
	else
	{
		if (pos.z - (size.z / 2) <= -FIELD_SIZE_HEIGHT / 2)
		{//手前壁
			pos.z = (-FIELD_SIZE_HEIGHT / 2) + (size.z / 2);
		}
	}

	if (pos.y <= 0.0f)
	{//床
		pos.y = 0.0f;
		m_bIsJumping = false;
		m_move.y = 0.0f;			//移動量Yの初期化
	}

	//位置情報更新
	CMotion::SetPosition(pos);

	//状態管理
	//State();

	// モーション再生
	CMotion::Motion();
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void CPlayer::Draw()
{
	//描画
	CMotion::Draw();
}

//-----------------------------------------------------------------------------
// 移動処理
//-----------------------------------------------------------------------------
void CPlayer::Move()
{
	// キーボード情報の取得
	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();
	// ジョイパッド情報の取得
	CInputJoypad *pJoypad = CManager::GetManager()->GetInputJoypad();

	// キーボードで操作しているなら
	if (m_bControlKeyboard == true)
	{
		if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_LEFT) == true)
		{//左キー押下
			if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
			{//上キー押下
				//移動量加算
				m_move.x += GetSinVec(-0.75f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.75f, MOVE_DEFAULT);
				//アニメーション変更
				m_nCntAnimMove++;
			}
			else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
			{//下キー押下
				m_move.x += GetSinVec(-0.25f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.25f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else
			{
				m_move.x += GetSinVec(-0.5f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.5f, MOVE_DEFAULT);
				m_nTexRotType = TYPE_NEUTRAL;
				m_nCntAnimMove = 0;
			}
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_RIGHT) == true)
		{//右キー押下
			if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
			{//上キー押下
				m_move.x += GetSinVec(0.75f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.75f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
			{//下キー押下
				m_move.x += GetSinVec(0.25f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.25f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else
			{
				m_move.x += GetSinVec(0.5f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.5f, MOVE_DEFAULT);
				m_nTexRotType = TYPE_NEUTRAL;
				m_nCntAnimMove = 0;
			}
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
		{//上キー押下
			m_move.x += GetSinVec(1.0f, MOVE_DEFAULT);
			m_move.z += GetCosVec(1.0f, MOVE_DEFAULT);
			m_nCntAnimMove++;
		}
		else if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
		{//下キー押下
			m_move.x += GetSinVec(0.0f, MOVE_DEFAULT);
			m_move.z += GetCosVec(0.0f, MOVE_DEFAULT);
			m_nCntAnimMove++;
		}
	}
	// ゲームパッド操作なら
	else
	{
		if (pJoypad->GetPress(CInputJoypad::JOYKEY_LEFT, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).x <= -0.2f)
		{//左キー押下
			if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
			{//上キー押下
			 //移動量加算
				m_move.x += GetSinVec(-0.75f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.75f, MOVE_DEFAULT);
				//アニメーション変更
				m_nCntAnimMove++;
			}
			else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
			{//下キー押下
				m_move.x += GetSinVec(-0.25f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.25f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else
			{
				m_move.x += GetSinVec(-0.5f, MOVE_DEFAULT);
				m_move.z += GetCosVec(-0.5f, MOVE_DEFAULT);
				m_nTexRotType = TYPE_NEUTRAL;
				m_nCntAnimMove = 0;
			}
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_RIGHT, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).x >= 0.2f)
		{//右キー押下
			if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
			{//上キー押下
				m_move.x += GetSinVec(0.75f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.75f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
				pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
			{//下キー押下
				m_move.x += GetSinVec(0.25f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.25f, MOVE_DEFAULT);
				m_nCntAnimMove++;
			}
			else
			{
				m_move.x += GetSinVec(0.5f, MOVE_DEFAULT);
				m_move.z += GetCosVec(0.5f, MOVE_DEFAULT);
				m_nTexRotType = TYPE_NEUTRAL;
				m_nCntAnimMove = 0;
			}
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_DOWN, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y >= JOYKEY_LEFT_STICK_DOWN)
		{//上キー押下
			m_move.x += GetSinVec(1.0f, MOVE_DEFAULT);
			m_move.z += GetCosVec(1.0f, MOVE_DEFAULT);
			m_nCntAnimMove++;
		}
		else if (pJoypad->GetPress(CInputJoypad::JOYKEY_UP, m_nGamePadNum) == true ||
			pJoypad->GetStick(CInputJoypad::JOYKEY_LEFT_STICK, m_nGamePadNum).y <= JOYKEY_LEFT_STICK_UP)
		{//下キー押下
			m_move.x += GetSinVec(0.0f, MOVE_DEFAULT);
			m_move.z += GetCosVec(0.0f, MOVE_DEFAULT);
			m_nCntAnimMove++;
		}
	}
}

//-----------------------------------------------------------------------------
// ジャンプ
//-----------------------------------------------------------------------------
void CPlayer::Jump()
{

}

//-----------------------------------------------------------------------------
// 状態管理
//-----------------------------------------------------------------------------
void CPlayer::State()
{
	switch (m_state)
	{
		// 通常
	case CPlayer::STATE_NORMAL:
		break;

		// 走る
	case CPlayer::STATE_RUN:
		break;

		// ジャンプ
	case CPlayer::STATE_JUMP:
		break;

		// 攻撃
	case CPlayer::STATE_ATTACK:
		break;

		// 死亡
	case CPlayer::STATE_DIE:
		break;

		// 雪崩に巻き込まれてる
	case CPlayer::STATE_INAVALANCHE:
		break;

	default:
		break;
	}
}

//-----------------------------------------------------------------------------
// ダメージ処理
//-----------------------------------------------------------------------------
void CPlayer::Damage()
{
	//if (m_BarrierLevel == CBarrier::LEVEL_NONE)
	//{

	// 死亡処理
	Die();

	// プレイヤー死亡音
	//CSound::Play(CSound::SOUND_LABEL_SE_DIE_PLAYER);

	//}
	//else
	//{
	//	m_BarrierLevel = (CBarrier::LEVEL)(m_BarrierLevel - 1);

	//	if (m_BarrierLevel == CBarrier::LEVEL_NONE)
	//	{
	//		if (m_pBarrier != nullptr)
	//		{
	//			m_pBarrier->Uninit();
	//			m_pBarrier = nullptr;
	//		}
	//	}
	//	else
	//	{
	//		m_pBarrier->SetBarrier(m_BarrierLevel);
	//	}
	//	m_state = STATE_RESPAWN;
	//	m_nCntState = 150;
	//}
}

//-----------------------------------------------------------------------------
// 死亡処理
//-----------------------------------------------------------------------------
void CPlayer::Die()
{
	//CModel::Uninit();

	// 操作不能にする
	m_bControl = false;
	// プレイヤーを死亡状態にする
	m_bDie = true;

	//// ライフが破棄されていなければ
	//if (m_pLife != nullptr)
	//{
	//	// ライフを減らす
	//	m_pLife->Add(-1);

	//	// ライフが0未満
	//	if (m_pLife->GetLife() < 0)
	//	{
	//		// スコアの破棄
	//		if (m_pScore != nullptr)
	//		{
	//			m_pScore->Uninit();
	//			m_pScore = nullptr;
	//		}

	//		// ライフの破棄
	//		m_pLife->Uninit();
	//		m_pLife = nullptr;

	//		// プレイヤーを死亡状態にする
	//		m_bDie = true;

	//		// サイズの取得
	//		D3DXVECTOR2 size = GetSize();
	//		// 爆発の生成
	//		CExplosion::Create(CObject2D::GetPosition(), D3DXVECTOR2(size.x, size.y * 2));

	//		return;
	//	}

	//	// 操作不能にする
	//	m_bControl = false;
	//	// リスポーン状態にする
	//	m_state = STATE_DIE;
	//	m_nCntState = 60;

	//	// 変数のリセット
	//	m_nTexRotType = TYPE_NEUTRAL;		//アニメーション番号をリセットする

	//										// バリアの破棄
	//	if (m_pBarrier != nullptr)
	//	{
	//		m_pBarrier->Uninit();
	//		m_pBarrier = nullptr;
	//	}

	//	// オプションの破棄
	//	for (int nCnt = 0; nCnt < MAX_OPTION; nCnt++)
	//	{
	//		if (m_pOption[nCnt] != nullptr)
	//		{
	//			m_pOption[nCnt]->Uninit();
	//			m_pOption[nCnt] = nullptr;
	//		}
	//	}

	//	// 各強化状態を初期化する
	//	m_OptionLevel = CBulletOption::LEVEL_NONE;
	//	m_BarrierLevel = CBarrier::LEVEL_NONE;
	//	m_BulletLevel = CPlayer::LEVEL_1;

	//	// サイズの取得
	//	D3DXVECTOR2 size = GetSize();
	//	// 爆発の生成
	//	CExplosion::Create(CObject2D::GetPosition(), D3DXVECTOR2(size.x, size.y * 2));

	//	//プレイヤーの位置を左端に設定する
	//	if (m_nPlayerNum == PLAYER_1)
	//	{// 1Pの場合
	//		CObject2D::SetPosition(D3DXVECTOR3(-SIZE_X, CRenderer::SCREEN_HEIGHT / 2, 0.0f));
	//	}
	//	else
	//	{// 2Pの場合
	//		CObject2D::SetPosition(D3DXVECTOR3(-SIZE_X, CRenderer::SCREEN_HEIGHT / 2 + SIZE_Y, 0.0f));
	//	}

	//}
}
