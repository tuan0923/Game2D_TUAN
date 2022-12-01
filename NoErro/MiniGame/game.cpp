//===============================================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : SHUGO KURODA
//
//===============================================================================================
#include "manager.h"
#include "game.h"
#include "object.h"
#include "sound.h"

#include "library.h"
#include "load.h"
#include "fade_scene.h"
#include "input_keyboard.h"
#include "input_joypad.h"

#include "score.h"
#include "life.h"
#include "number.h"
#include "logo.h"
#include "pause.h"
#include "rank.h"
#include "score.h"

#include "bg.h"
#include "cloud.h"
#include "enemy.h"
#include "enemy_boss.h"
#include "bullet.h"
#include "bullet_option.h"
#include "item.h"
#include "barrier.h"
#include "explosion.h"
#include "spray.h"
#include "bubble.h"
#include "effect.h"
#include "bg_move.h"
#include "ui.h"
#include "gauge.h"
#include "continue.h"

// 追加
#include "object3D.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "enemy_boss.h"
#include "item.h"
#include "model_obstacle.h"
#include "model_manager.h"
#include "logo_countdown.h"
#include "logo_extend.h"
#include "mesh_sphere.h"
//#include "avalanche.h"

//-----------------------------------------------------------------------------------------------
// using宣言
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CGame::CGame() :m_pPlayer{}, m_pEnemyBoss(), m_pItem(), m_pCamera(), m_bStart(false), m_bEnd(false)
{
	//敵の生成情報を初期化
	ZeroMemory(&m_EnemyInfo, sizeof(m_EnemyInfo));
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CGame::~CGame()
{
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CGame::Init()
{
	//球体メッシュの配置
	CMeshSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR2(3000.0f, 3000.0f), 10, 10, "TEX_TYPE_GAME_BG");

	// 板ポリ生成
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// 板ポリ生成
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f));
	// 板ポリ生成
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, -400.0f));
	// 板ポリ生成
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, -600.0f));
	// 板ポリ生成
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, -800.0f));

	// ライト生成
	CLight::Create(D3DXVECTOR3(-0.2f, -0.8f, 0.4f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CLight::Create(D3DXVECTOR3(0.2f, -0.1f, -0.8f), D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));

	// モデル生成
	CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_ITEM_METAL");

	// 敵ボス生成
	m_pEnemyBoss = CEnemyBoss::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_WASIZU");

	// カメラ生成
	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 130.0f, -230.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// 追従対象の設定
	m_pCamera->SetTracking(true);
	m_pCamera->SetPosTracking(m_pEnemyBoss->GetpPosition());

	// Item生成
	m_pItem = CItem::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), CItem::TYPE_NONE, "XFILE_TYPE_SHOE");

	// 木の２つ列を生成
	for (int nCnt = -2; nCnt < 0; nCnt++)
	{
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (50.0f*(nCnt ))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木1");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (200.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木2");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (300.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木3");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (400.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木4");

		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (100.0f*(nCnt ))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木1");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (200.0f*(nCnt ))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木2");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (300.0f*(nCnt ))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木3");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (400.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木4");

	}
	for (int nCnt = 1; nCnt < 5; nCnt++)
	{
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (50.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木1");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (200.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木2");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (300.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木3");
		CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f + (400.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木4");

		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (50.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木1");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (200.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木2");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (300.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木3");
		CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 0.0f + (400.0f*(nCnt))), D3DXVECTOR3(0.0f, nCnt, 0.0f), "XFILE_TYPE_木4");

	}
	

	// モデルマネージャー生成
	CModelManager::Create();

	// モデル生成
	CModel::Create(D3DXVECTOR3(0.0f, -55.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_CREVASSE");

	// カウントダウンの開始
	CLogoCountDown::Create(5);

	// プレイヤー参加情報の取得
	CManager::SEntryInfo *pEntry = CManager::GetManager()->GetEntry();

	// プレイヤー生成
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		// 現在の番号が参加しているなら
		if (pEntry[nCntPlayer].bEntry == true)
		{
			// キーボードで参加しているなら
			if (pEntry[nCntPlayer].bEntryKeyboard == true)
			{
				// プレイヤー生成
				m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_STAR", nCntPlayer);
				m_pPlayer[nCntPlayer]->SetKeyboard(pEntry[nCntPlayer].bEntryKeyboard);
			}
			else
			{
				// プレイヤー生成
				m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "XFILE_TYPE_STAR", nCntPlayer);
				m_pPlayer[nCntPlayer]->SetGamePadNum(pEntry[nCntPlayer].nGamePadNum);
			}

			// ゲームに参加している状態にする
			m_pPlayer[nCntPlayer]->SetStart(true);
		}
	}

	////敵情報読み込み
	//m_EnemyInfo.pCreate = LoadSpace::GetEnemy();
	////ウェーブ数の読み込み
	//m_EnemyInfo.nWave = LoadSpace::GetWave();
	//// テクスチャ読み込み
	//LoadAll();
	//// UIの生成
	//CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 50.0f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), 
	//	CUi::TYPE_AREA_A, CUi::ANIM_NONE, CUi::PLAYER_NONE);

	//// プレイヤー生成
	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	// プレイヤーENTRY情報の取得
	//	bool bEntry = CManager::GetEntry(nCntPlayer);

	//	// エントリーしていれば
	//	if (bEntry == true)
	//	{// プレイヤー生成
	//		m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(-630.0f, (float)CRenderer::SCREEN_HEIGHT, 0.0f), nCntPlayer);
	//	}
	//	// エントリーしていなければ
	//	else if (bEntry == false)
	//	{
	//		switch (nCntPlayer)
	//		{
	//		case CPlayer::PLAYER_1:
	//			// エントリー待ちのUI1を生成
	//			CUi::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 4) - 50.0f, 40.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f),
	//				CUi::TYPE_PRESS_ANY_BUTTON, CUi::ANIM_FLASHING, CUi::PLAYER_1_NOT_ENTRY);
	//			// エントリー待ちのUI2を生成
	//			CUi::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 4) - 50.0f, 80.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f),
	//				CUi::TYPE_TO_START, CUi::ANIM_NONE, CUi::PLAYER_1_NOT_ENTRY);
	//			break;

	//		case CPlayer::PLAYER_2:
	//			// エントリー待ちのUI1を生成
	//			CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH - 300.0f, 40.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f),
	//				CUi::TYPE_PRESS_ANY_BUTTON, CUi::ANIM_FLASHING, CUi::PLAYER_2_NOT_ENTRY);
	//			// エントリー待ちのUI2を生成
	//			CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH - 300.0f, 80.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f),
	//				CUi::TYPE_TO_START, CUi::ANIM_NONE, CUi::PLAYER_2_NOT_ENTRY);
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	//// 背景の生成
	//CBg::Create(CBg::SET_A);

	////ポインタの初期化
	//m_pPlayer[CPlayer::PLAYER_MAX] = { nullptr };
	//m_pMeshField = nullptr;
	//m_bCreateCloud = true;
	//m_bCreateBubble = false;
	//m_bDieBoss = false;

	//// 決定音
	//CSound::Play(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CGame::Uninit()
{
	//テクスチャの破棄
	//UnloadAll();

	// ポーズ状態を解除
	CManager::GetManager()->SetPause(false);

	// 決定音
	CSound::Stop();

	// プレイヤー破棄
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] != nullptr)
		{
			m_pPlayer[nCntPlayer] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CGame::Update()
{
	// ゲームが終了していないなら
	if (m_bEnd == false)
	{
		// ゲームが終了したかどうかを判定
		CheckGameEnd();
	}
	//// キーボード情報の取得
	//CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();
	//// ゲームパッド情報の取得
	//CInputJoypad *pJoypad = CManager::GetInputJoypad();

	//// ポーズ生成
	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	// ボス死亡フラグが立っていなければ
	//	if (m_bDieBoss == false)
	//	{
	//		// プレイヤーENTRY情報の取得
	//		bool bEntry = CManager::GetEntry(nCntPlayer);

	//		// エントリーしていれば
	//		if (bEntry == true)
	//		{// ポーズ生成
	//			if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_PAUSE) == true || pJoypad->GetTrigger(CInputJoypad::JOYKEY_START, nCntPlayer) == true)
	//			{
	//				// ポーズ状態の取得
	//				bool bPause = CManager::GetPause();
	//				// ポーズ中でなければ
	//				if (bPause == false)
	//				{//ポーズ画面を生成
	//					CPause::Create(nCntPlayer);
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}

	//// プレイヤーENTRY情報の取得
	//bool bEntry1P = CManager::GetEntry(CPlayer::PLAYER_1);
	//bool bEntry2P = CManager::GetEntry(CPlayer::PLAYER_2);

	//if (bEntry1P == false && bEntry2P == false)
	//{
	//	// コンティニュー演出の生成
	//	CContinue::Create(D3DXVECTOR3(750.0f, 300.0f, 0.0f), D3DXVECTOR2(40.0f, 30.0f))->Add(15);
	//}

	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	// プレイヤー生成
	//	if (m_pPlayer[nCntPlayer] == nullptr)
	//	{
	//		// プレイヤーENTRY情報の取得
	//		bool bEntry = CManager::GetEntry(nCntPlayer);

	//		// エントリーしていれば
	//		if (bEntry == true)
	//		{// プレイヤー生成
	//			m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(-630.0f, (float)CRenderer::SCREEN_HEIGHT, 0.0f), nCntPlayer);
	//		}
	//	}
	//	// プレイヤー破棄
	//	else if (m_pPlayer[nCntPlayer] != nullptr)
	//	{
	//		// プレイヤー死亡状態の取得
	//		bool bDie = m_pPlayer[nCntPlayer]->GetDie();

	//		// 死亡していれば
	//		if (bDie == true)
	//		{// プレイヤー破棄

	//			if (CContinue::GetContinue() == false)
	//			{
	//				m_pPlayer[nCntPlayer]->Uninit();
	//				m_pPlayer[nCntPlayer] = nullptr;

	//				switch (nCntPlayer)
	//				{
	//				case CPlayer::PLAYER_1:
	//					// エントリー待ちのUI1を生成
	//					CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 4, 40.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f), CUi::TYPE_PRESS_ANY_BUTTON, CUi::ANIM_FLASHING, CUi::PLAYER_1_NOT_ENTRY);
	//					// エントリー待ちのUI2を生成
	//					CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 4, 80.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f), CUi::TYPE_TO_START, CUi::ANIM_NONE, CUi::PLAYER_1_NOT_ENTRY);
	//					break;

	//				case CPlayer::PLAYER_2:
	//					// エントリー待ちのUI1を生成
	//					CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH - 300.0f, 40.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f), CUi::TYPE_PRESS_ANY_BUTTON, CUi::ANIM_FLASHING, CUi::PLAYER_2_NOT_ENTRY);
	//					// エントリー待ちのUI2を生成
	//					CUi::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH - 300.0f, 80.0f, 0.0f), D3DXVECTOR2(400.0f, 50.0f), CUi::TYPE_TO_START, CUi::ANIM_NONE, CUi::PLAYER_2_NOT_ENTRY);
	//					break;
	//				default:
	//					break;
	//				}

	//				// 不参加状態にする
	//				CManager::SetEntry(nCntPlayer, false);
	//			}
	//		}
	//	}
	//}

	////雲を生成するかどうか
	//if (m_bCreateCloud == true)
	//{
	//	//雲の生成処理
	//	CreateCloud();
	//}
	////泡エフェクトを生成するかどうか
	//if (m_bCreateBubble == true)
	//{
	//	//泡エフェクトの生成処理
	//	CreateBubble();
	//}

	////敵の生成処理	
	//CreateEnemy();
}

//-----------------------------------------------------------------------------------------------
// ゲームを終了するかどうかを判定
//-----------------------------------------------------------------------------------------------
bool CGame::CheckGameEnd()
{
	// プレイヤーの死亡数
	int nNumDie = 0;

	// プレイヤー生成
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		// 現在のプレイヤーが参加しているなら
		if (m_pPlayer[nCntPlayer] != nullptr)
		{
			// 死亡していたら
			if (m_pPlayer[nCntPlayer]->GetDie() == true)
			{// プレイヤーの死亡数を加算
				nNumDie++;
			}
		}
		else
		{// プレイヤーの死亡数を加算
			nNumDie++;
		}
	}

	// プレイヤーが全員死亡していたら
	if (CPlayer::PLAYER_MAX <= nNumDie)
	{
		// ゲーム終了フラグを立てる
		m_bEnd = true;
		// ゲーム終了ロゴの生成
		CLogoExtend::Create(D3DXVECTOR2(250.0f, 80.0f), "TEX_TYPE_END_UI", 180);
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------
// 敵の生成(外部スクリプト使用)
//-----------------------------------------------------------------------------------------------
void CGame::CreateEnemy()
{
	// 敵生成カウンターの加算
	m_EnemyInfo.nCreatenCount++;

	//敵のウェーブ数だけ生成する
	for (int nCntEnemy = 0; nCntEnemy < m_EnemyInfo.nWave; nCntEnemy++)
	{
		// 敵が出現するフレーム数に達したら && 敵の出現が終わっていないなら
		if (m_EnemyInfo.pCreate[nCntEnemy].nFrame <= m_EnemyInfo.nCreatenCount && m_EnemyInfo.count[nCntEnemy].bCreate == false)
		{
			//敵が連続で出現するまでのカウンターを加算
			m_EnemyInfo.count[nCntEnemy].nCreate++;
			//敵の連続出現間隔カウンターが最大に達したら
			if (m_EnemyInfo.count[nCntEnemy].nCreate >= m_EnemyInfo.pCreate[nCntEnemy].nInterval)
			{
				//敵の生成(位置、種類、体力、移動情報を引数に設定)
				CEnemy *pEnemy = CEnemy::Create(m_EnemyInfo.pCreate[nCntEnemy].pos, (CEnemy::TYPE)m_EnemyInfo.pCreate[nCntEnemy].nType, m_EnemyInfo.pCreate[nCntEnemy].nLife, &m_EnemyInfo.pCreate[nCntEnemy].move[0]);

				//敵の生成数カウンターを加算
				m_EnemyInfo.count[nCntEnemy].nNum++;
				//敵の連続出現間隔カウンターのリセット
				m_EnemyInfo.count[nCntEnemy].nCreate = 0;

				//敵が最大数まで生成したら
				if (m_EnemyInfo.pCreate[nCntEnemy].nNum <= m_EnemyInfo.count[nCntEnemy].nNum)
				{
					// 色の設定がされていたら
					if (m_EnemyInfo.pCreate[nCntEnemy].nColor > 0)
					{// 最後尾の敵の色を設定
						pEnemy->SetItemColor((CEnemy::COLORITEM)m_EnemyInfo.pCreate[nCntEnemy].nColor);
					}
					// このウェーブの生成をやめる
					m_EnemyInfo.count[nCntEnemy].bCreate = true;
				}
			}
		}
	}

	// ボスを出現させる
	if (m_EnemyInfo.nCreatenCount == 5260)
	{
		//CEnemyBoss::Create(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT + CEnemyBoss::SIZE_HEIGHT, 0.0f), CEnemy::TYPE_DARK_BOSS);
		// 警告音
		CSound::Play(CSound::SOUND_LABEL_BOSS);
	}

	//ロゴの生成
	CreateLogo(m_EnemyInfo.nCreatenCount);
}

//-----------------------------------------------------------------------------------------------
// ロゴの生成
//-----------------------------------------------------------------------------------------------
void CGame::CreateLogo(int nCounter)
{
	//if (nCounter == 4800)
	//{
	//	// ボス接近中のロゴ
	//	CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR2(CRenderer::SCREEN_WIDTH - 400.0f, 90.0f),
	//		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_WARNING, CLogo::ANIM_LENGTHWISE, 420);

	//	// ゲームBGMをストップ
	//	CSound::Stop(CSound::SOUND_LABEL_GAME);
	//	// 警告音
	//	CSound::Play(CSound::SOUND_LABEL_SE_WARNING);
	//}

	//if (nCounter == 4920)
	//{
	//	// ボス接近中の説明ロゴ
	//	CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(CRenderer::SCREEN_WIDTH - 760.0f, 270.0f),
	//		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLogo::TYPE_WARNING_SUB, CLogo::ANIM_HORIZONTALLY, 300);
	//}

	//if (nCounter == 4800)
	//{
	//	// ボス接近時の薄暗いフェード
	//	CFadeScene::Create(CFadeScene::TYPE_BLACK);
	//}
}

//-----------------------------------------------------------------------------------------------
// ランキングスコアの設定
//-----------------------------------------------------------------------------------------------
void CGame::SetPlayerScore()
{
	//// プレイヤーのスコアを保存
	//for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	//{
	//	if (m_pPlayer[nCntPlayer] != nullptr)
	//	{
	//		// プレイヤーENTRY情報の取得
	//		bool bEntry = CManager::GetManager()->GetEntry(nCntPlayer);

	//		// エントリーしていれば
	//		if (bEntry == true)
	//		{// プレイヤー生成
	//			// プレイヤースコアの初期化
	//			CRank::SetScore(0, nCntPlayer);

	//			CScore* pScore = m_pPlayer[nCntPlayer]->GetScore();
	//			if (pScore != nullptr)
	//			{
	//				int nSocre = pScore->GetScore();
	//				CRank::SetScore(nSocre, nCntPlayer);
	//			}
	//		}
	//	}
	//}
}
