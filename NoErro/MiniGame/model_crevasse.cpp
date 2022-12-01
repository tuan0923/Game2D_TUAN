//-----------------------------------------------------------------------------------------------
//
// クレバス(地面の亀裂)処理[model_crevasse.cpp]
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
#include "title.h"
#include "model_crevasse.h"

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CCrevasse::CCrevasse() :m_PosOld(0.0f, 0.0f, 0.0f)
{
	//オブジェクトの種類設定
	SetType(EObject::OBJ_OBSTACLE);
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CCrevasse::~CCrevasse()
{
}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CCrevasse *CCrevasse::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name)
{
	// ポインタクラスを宣言
	CCrevasse* pCrevasse = new CCrevasse;

	if (pCrevasse != nullptr)
	{
		// 位置設定
		pCrevasse->SetPosition(pos);
		// 角度設定
		pCrevasse->SetRotation(rot);
		// Xファイルの設定
		pCrevasse->BindXFile(CManager::GetManager()->GetXFile()->GetXFile(name));
		// 初期化
		pCrevasse->Init();
	}

	return pCrevasse;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CCrevasse::Init()
{
	// 初期化
	CModel::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CCrevasse::Uninit()
{
	CModel::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CCrevasse::Update()
{
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CCrevasse::Draw()
{
	//描画処理
	CModel::Draw();
}

//-----------------------------------------------------------------------------------------------
// 全ての障害物の当たり判定
//-----------------------------------------------------------------------------------------------
void CCrevasse::CollisionAll(D3DXVECTOR3* pPosPlayer, D3DXVECTOR3* pPosPlayerOld, D3DXVECTOR3* pSizePlayer)
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
				CCrevasse *pObstacle = (CCrevasse*)pObject;

				// 当たり判定
				pObstacle->Collision(pPosPlayer, pPosPlayerOld, pSizePlayer);
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// 当たり判定
//-----------------------------------------------------------------------------------------------
bool CCrevasse::Collision(D3DXVECTOR3* pPosPlayer, D3DXVECTOR3* pPosPlayerOld, D3DXVECTOR3* pSizePlayer)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	//サイズ取得
	D3DXVECTOR3 size = GetSizeMax();

	// 矩形の当たり判定3D
	if (LibrarySpace::BoxCollision3D(pPosPlayer, pPosPlayerOld, &pos, pSizePlayer, &size))
	{//ダメージ処理
		return true;	//当たった
	}

	return false;	//当たってない
}
