//-----------------------------------------------------------------------------------------------
//
// 障害物処理[model_obstacle.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"

#include "load.h"
#include "sound.h"

#include "game.h"
#include "library.h"
#include "effect.h"
#include "logo.h"
#include "score.h"
#include "fade_scene.h"

#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "logo.h"

// 追加
#include "x_file.h"
#include "model_obstacle.h"

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CObstacle::CObstacle() :m_PosOld(0.0f, 0.0f, 0.0f)
{
	//オブジェクトの種類設定
	SetType(EObject::OBJ_OBSTACLE);
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CObstacle::~CObstacle()
{
}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CObstacle *CObstacle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name)
{
	// ポインタクラスを宣言
	CObstacle* pObstacle = new CObstacle;

	if (pObstacle != nullptr)
	{
		// 位置設定
		pObstacle->SetPosition(pos);
		// 角度設定
		pObstacle->SetRotation(rot);
		// Xファイルの設定
		pObstacle->BindXFile(CManager::GetManager()->GetXFile()->GetXFile(name));
		// 初期化
		pObstacle->Init();
	}

	return pObstacle;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CObstacle::Init()
{
	// 初期化
	CModel::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CObstacle::Uninit()
{
	CModel::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CObstacle::Update()
{
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CObstacle::Draw()
{
	//描画処理
	CModel::Draw();
}

//-----------------------------------------------------------------------------------------------
// 全ての障害物の当たり判定
//-----------------------------------------------------------------------------------------------
void CObstacle::CollisionAll(D3DXVECTOR3* pPosIn, int nNumPlayer)
{
	for (int nCntObject = 0; nCntObject < CObject::MAX_OBJECT; nCntObject++)
	{
		// オブジェクトのポインタ取得
		CObject *pObject = CObject::GetObject(nCntObject);

		if (pObject != nullptr)
		{
			// オブジェクトの種類取得
			CObject::EObject objType = pObject->GetObjType();

			//プレイヤーの弾と敵の判定
			if (objType == OBJ_OBSTACLE)
			{
				//オブジェクトポインタをキャスト
				CObstacle *pObstacle = (CObstacle*)pObject;

				// 当たり判定
				pObstacle->Collision(pPosIn, nNumPlayer);
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// 当たり判定
//-----------------------------------------------------------------------------------------------
bool CObstacle::Collision(D3DXVECTOR3* pPosPlayer, int nNumPlayer)
{
	bool bPush = false;

	// プレイヤー情報の取得
	CPlayer *pPlayer = CManager::GetManager()->GetGame()->GetPlayer(nNumPlayer);

	if (pPlayer != nullptr)
	{
		// プレイヤーの過去の位置取得
		D3DXVECTOR3 posPlayerOld = pPlayer->GetPositionOld();
		// プレイヤーのサイズ取得
		D3DXVECTOR3 sizePlayer = pPlayer->GetSizeMax();

		// 位置取得
		D3DXVECTOR3 pos = GetPosition();
		//サイズ取得
		D3DXVECTOR3 size = GetSizeMax();

		// 押し出し判定
		switch (LibrarySpace::BoxCollisionUnder3D(pPosPlayer, &posPlayerOld, &pos, &sizePlayer, &size))
		{
		case LibrarySpace::PUSH_X:
			pPlayer->SetMoveX(0.0f);
			break;

		case LibrarySpace::PUSH_Z:
			pPlayer->SetMoveZ(0.0f);
			break;

		case LibrarySpace::PUSH_Y:
			pPlayer->SetMoveY(0.0f);
			break;

		case LibrarySpace::PUSH_JUMP:
			pPlayer->SetMoveY(0.0f);
			pPlayer->SetJumping(false);
			break;

		default:
			break;
		}
	}

	return bPush;	//当たってない
}
