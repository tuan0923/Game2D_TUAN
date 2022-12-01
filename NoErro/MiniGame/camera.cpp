//===================================================================
//
//	カメラ処理[camera.cpp]
//	Author:SHUGO KURODA
//
//===================================================================
#include "manager.h"
#include "renderer.h"

#include "input_keyboard.h"
#include "input_mouse.h"
#include "camera.h"

// 追加
#include "title.h"
#include "enemy_boss.h"

//======================================================
//	マクロ定義
//======================================================
#define CAMERA_POS_MOVE		(3.0f)		//視点の移動量
#define CAMERA_ROT_MOVE		(0.03f)		//回転の移動量

//======================================================
//	コンストラクタ
//======================================================
CCamera::CCamera() :m_move(0.0f, 0.0f, 0.0f), m_posV(0.0f, 0.0f, 0.0f), m_posR(0.0f, 0.0f, 0.0f), m_vecU(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f),
					m_pPosTracking(nullptr), m_posVDest(0.0f, 0.0f, 0.0f), m_posRDest(0.0f, 0.0f, 0.0f), m_fDistance(0.0f), m_bTracking(false)
{
}

//======================================================
//	デストラクタ
//======================================================
CCamera::~CCamera()
{
}

//======================================================
//	生成処理
//	const D3DXVECTOR3& posV → 生成する視点位置
//	const D3DXVECTOR3& posR → 生成する注視点位置
//	const D3DXVECTOR3& rot → 生成する視点角度
//======================================================
CCamera *CCamera::Create(const D3DXVECTOR3& posV, const D3DXVECTOR3& posR, const D3DXVECTOR3& rot)
{
	//インスタンス生成
	CCamera *pCamera = new CCamera;

	// 視点位置設定
	pCamera->m_posV = posV;

	// 注視点位置設定
	pCamera->m_posR = posR;

	// 視点角度設定
	pCamera->m_rot = rot;

	// 初期化
	pCamera->Init();

	return pCamera;
}

//======================================================
//	初期化処理
//======================================================
HRESULT CCamera::Init()
{
	//上方向ベクトルの設定
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//固定

	//注視点までの距離
	D3DXVECTOR3 Distance = D3DXVECTOR3((m_posV.x + m_posR.x), (m_posV.y + m_posR.y), (m_posV.z + m_posR.z));
	m_rot = D3DXVECTOR3(atan2f(Distance.z, Distance.y), 0.0f, 0.0f);

	//視点から注視点までの距離を初期化する
	m_fDistance = sqrtf(Distance.x * Distance.x + Distance.z * Distance.z);
	m_fDistance = sqrtf(Distance.y * Distance.y + m_fDistance * m_fDistance);

	return S_OK;
}

//======================================================
//	終了処理
//======================================================
void CCamera::Uninit()
{
}

//======================================================
//	更新処理
//======================================================
void CCamera::Update()
{
	//マウスの移動量情報の取得
	CInputKeyboard *pKeyboard = CManager::GetManager()->GetInputKeyboard();

	//注視点の旋回
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_E) == true)
	{//右回転
		m_rot.y += CAMERA_ROT_MOVE;

		m_posR.x = m_posV.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y - cosf(m_rot.x) * m_fDistance;
	}
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_Q) == true)
	{//左回転
		m_rot.y -= CAMERA_ROT_MOVE;

		m_posR.x = m_posV.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y - cosf(m_rot.x) * m_fDistance;
	}
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_Y) == true)
	{//上回転
		m_rot.x -= CAMERA_ROT_MOVE;

		m_posR.x = m_posV.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y - cosf(m_rot.x) * m_fDistance;
	}
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_H) == true)
	{//下回転
		m_rot.x += CAMERA_ROT_MOVE;

		m_posR.x = m_posV.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y - cosf(m_rot.x) * m_fDistance;
	}

	//視点の旋回
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_Z) == true)
	{//右回転
		m_rot.y += CAMERA_ROT_MOVE;

		m_posV.x = m_posR.x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y + cosf(m_rot.x) * m_fDistance;
	}
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_C) == true)
	{//左回転
		m_rot.y -= CAMERA_ROT_MOVE;

		m_posV.x = m_posR.x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y + cosf(m_rot.x) * m_fDistance;
	}
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_T) == true)
	{//上回転
		m_rot.x += CAMERA_ROT_MOVE;

		m_posV.x = m_posR.x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y + cosf(m_rot.x) * m_fDistance;
	}
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_G) == true)
	{//下回転
		m_rot.x -= CAMERA_ROT_MOVE;

		m_posV.x = m_posR.x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y + cosf(m_rot.x) * m_fDistance;
	}

	////視点の移動
	//if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_UP) == true)
	//{//前移動
	//	m_posV.x += sinf(m_rot.y) * CAMERA_POS_MOVE;
	//	m_posV.z += cosf(m_rot.y) * CAMERA_POS_MOVE;

	//	m_posR.x = m_posV.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	//	m_posR.z = m_posV.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	//	m_posR.y = m_posV.y - cosf(m_rot.x) * m_fDistance;
	//}
	//if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_DOWN) == true)
	//{//後移動
	//	m_posV.x -= sinf(m_rot.y) * CAMERA_POS_MOVE;
	//	m_posV.z -= cosf(m_rot.y) * CAMERA_POS_MOVE;

	//	m_posR.x = m_posV.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	//	m_posR.z = m_posV.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	//	m_posR.y = m_posV.y - cosf(m_rot.x) * m_fDistance;
	//}

	//カメラ位置の更新
	m_posR.x = m_posV.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posR.z = m_posV.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	m_posR.y = m_posV.y - cosf(m_rot.x) * m_fDistance;

	// カメラが追従中の場合
	if (m_bTracking == true)
	{
		// 追従
		m_posRDest.x = m_pPosTracking->x + sinf(m_rot.x) * sinf(m_rot.y);
		m_posRDest.z = (m_pPosTracking->z - 70.0f) + sinf(m_rot.x) * cosf(m_rot.y);
		m_posRDest.y = (m_pPosTracking->y - 50.0f) + cosf(m_rot.x);
		m_posVDest.x = m_pPosTracking->x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posVDest.z = (m_pPosTracking->z - 70.0f) + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posVDest.y = (m_pPosTracking->y - 50.0f) + cosf(m_rot.x) * m_fDistance;

		// カメラ位置の更新
		m_posR.x += (m_posRDest.x - m_posR.x) * 0.3f;
		m_posR.z += (m_posRDest.z - m_posR.z) * 0.3f;
		m_posR.y += (m_posRDest.y - m_posR.y) * 0.3f;
		m_posV.x += (m_posVDest.x - m_posV.x) * 0.3f;
		m_posV.z += (m_posVDest.z - m_posV.z) * 0.3f;
		m_posV.y += (m_posVDest.y - m_posV.y) * 0.3f;
	}

	//}
	//if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_RIGHT) == true)
	//{//右移動
	//	m_posV.x += sinf(m_rot.y + (D3DX_PI / 2)) * CAMERA_POS_MOVE;
	//	m_posV.z += cosf(m_rot.y + (D3DX_PI / 2)) * CAMERA_POS_MOVE;

	//	m_posR.x = m_posV.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	//	m_posR.z = m_posV.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	//	m_posR.y = m_posV.y - cosf(m_rot.x) * m_fDistance;
	//}
	//if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_LEFT) == true)
	//{//左移動
	//	m_posV.x += sinf(m_rot.y - (D3DX_PI / 2)) * CAMERA_POS_MOVE;
	//	m_posV.z += cosf(m_rot.y - (D3DX_PI / 2)) * CAMERA_POS_MOVE;

	//	m_posR.x = m_posV.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	//	m_posR.z = m_posV.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	//	m_posR.y = m_posV.y - cosf(m_rot.x) * m_fDistance;
	//}
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_R) == true)
	{//上移動
		m_posV.y -= sinf(m_rot.x) * CAMERA_POS_MOVE;

		m_posR.x = m_posV.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y - cosf(m_rot.x) * m_fDistance;
	}
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_F) == true)
	{//下移動
		m_posV.y += sinf(m_rot.x) * CAMERA_POS_MOVE;

		m_posR.x = m_posV.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y - cosf(m_rot.x) * m_fDistance;
	}

	//if (m_posV.y <= D3DX_PI / 2)
	//{//地面のカメラ当たり判定
	//	m_posV.y = D3DX_PI / 2;
	//}

	//角度の正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//======================================================
//	設定処理
//======================================================
void CCamera::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)CRenderer::SCREEN_WIDTH / (float)CRenderer::SCREEN_HEIGHT,
		10.0f,
		6400.0f);			//視界の設定

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
