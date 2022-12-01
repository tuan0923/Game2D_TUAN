//===================================================================
//
// 様々な処理をまとめたファイル (library.cpp)
// Author : SHUGO KURODA
//
//===================================================================
#include "library.h"

//*******************************************************************
// マクロ定義
//*******************************************************************
// スクリーンサイズ
#define SCREEN_WIDTH		(CRenderer::SCREEN_WIDTH)
#define SCREEN_HEIGHT		(CRenderer::SCREEN_HEIGHT)

//-----------------------------------------------------------------------------------------------
// 画面外判定
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::OutScreen2D(const D3DXVECTOR3 *pPos, const D3DXVECTOR2 size)
{
	// 画面の端から出ているかどうか
	if (pPos->x < -(size.x / 2) ||
		pPos->x > SCREEN_WIDTH + size.x / 2 ||
		pPos->y < -(size.y / 2) ||
		pPos->y > SCREEN_HEIGHT + size.y / 2)
	{
		//画面外に出た
		return true;
	}

	//まだ画面内
	return false;
}

//-----------------------------------------------------------------------------------------------
// 画面内の範囲制限
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::SteyInScreen2D(D3DXVECTOR3 *pPos, D3DXVECTOR2 size)
{
	// 画面端かどうか
    bool bScreenIn = false;    

    // 画面の左
    if (pPos->x < size.x / 2)
    {
        // 押し出す
        pPos->x = size.x / 2;
        // 押し出しフラグをtrueに
        bScreenIn = true;
    }
    // 画面の右
    if (pPos->x > SCREEN_WIDTH - size.x / 2)
    {
		// 押し出す
        pPos->x = SCREEN_WIDTH - size.x / 2;
        // 押し出しフラグをtrueに
        bScreenIn = true;
    }

    // 画面の上
	if (pPos->y < 100.0f + size.y / 2)
	{
		// 押し出す
		pPos->y = 100.0f + size.y / 2;
		// 押し出しフラグをtrueに
		bScreenIn = true;
	}

    // 画面の下
    if (pPos->y > SCREEN_HEIGHT - size.y / 2)
    {
		// 押し出す
        pPos->y = SCREEN_HEIGHT - size.y / 2;
        // 押し出しフラグをtrueに
        bScreenIn = true;
    }

    return bScreenIn;
}

//-----------------------------------------------------------------------------------------------
// 矩形の当たり判定2D
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::BoxCollision2D(const D3DXVECTOR3 *pPos1, const D3DXVECTOR3*pPos2, const D3DXVECTOR3*pSize1, const D3DXVECTOR3*pSize2)
{
	// 四面の当たり判定
	if (pPos1->x - pSize1->x / 2 <= pPos2->x + pSize2->x / 2 &&
		pPos1->x + pSize1->x / 2 >= pPos2->x - pSize2->x / 2 &&
		pPos1->y - pSize1->y / 2 <= pPos2->y + pSize2->y / 2 &&
		pPos1->y + pSize1->y / 2 >= pPos2->y - pSize2->y / 2)
	{
		// 当たった
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------
// 矩形の当たり判定3D(pPosInの中心点が真ん中)
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::BoxCollision3D(D3DXVECTOR3* pPosIn, const D3DXVECTOR3* pPosInOld, const D3DXVECTOR3* pPosOut, const D3DXVECTOR3* pSizeIn, const D3DXVECTOR3* pSizeOut)
{
	//衝突フラグ
	bool bIsPush = false;

	if (pPosInOld->x + pSizeIn->x <= pPosOut->x - pSizeOut->x		//前回の位置(X軸)がX軸の最小値以下
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//現在の位置(X軸)がX軸の最小値以上
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z軸の最大値より内側
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//Z軸の最小値より内側
		&& pPosIn->y - pSizeIn->y <= pPosOut->y + pSizeOut->y		//Y軸の最大値より内側
		&& pPosIn->y + pSizeIn->y >= pPosOut->y - pSizeOut->y)		//Y軸の最小値より内側
	{//左側の当たり判定(-X)
		pPosIn->x = (pPosOut->x - pSizeOut->x) - pSizeIn->x;
		bIsPush = true;
	}
	else if (pPosInOld->x - pSizeIn->x >= pPosOut->x + pSizeOut->x	//前回の位置(X軸)がX軸の最小値以上
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//現在の位置(X軸)がX軸の最小値以下
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z軸の最大値より内側
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//Z軸の最小値より内側
		&& pPosIn->y - pSizeIn->y <= pPosOut->y + pSizeOut->y		//Y軸の最大値より内側
		&& pPosIn->y + pSizeIn->y >= pPosOut->y - pSizeOut->y)		//Y軸の最小値より内側
	{//右側の当たり判定(+X)
		pPosIn->x = (pPosOut->x + pSizeOut->x) + pSizeIn->x;
		bIsPush = true;
	}

	if (pPosInOld->z + pSizeIn->z <= pPosOut->z - pSizeOut->z		//前回の位置(Z軸)がZ軸の最小値以下
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//現在の位置(Z軸)がZ軸の最小値以上
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X軸の最大値より内側
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X軸の最小値より内側
		&& pPosIn->y - pSizeIn->y <= pPosOut->y + pSizeOut->y		//Y軸の最大値より内側
		&& pPosIn->y + pSizeIn->y >= pPosOut->y - pSizeOut->y)		//Y軸の最小値より内側
	{//手前側の当たり判定(-Z)
		pPosIn->z = (pPosOut->z - pSizeOut->z) - pSizeIn->z;
		bIsPush = true;
	}
	else if (pPosInOld->z - pSizeIn->z >= pPosOut->z + pSizeOut->z	//前回の位置(Z軸)がZ軸の最小値以上
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//現在の位置(Z軸)がZ軸の最小値以下
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X軸の最大値より内側
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X軸の最小値より内側
		&& pPosIn->y - pSizeIn->y <= pPosOut->y + pSizeOut->y		//Y軸の最大値より内側
		&& pPosIn->y + pSizeIn->y >= pPosOut->y - pSizeOut->y)		//Y軸の最小値より内側
	{//奥側の当たり判定(+Z)
		pPosIn->z = (pPosOut->z + pSizeOut->z) + pSizeIn->z;
		bIsPush = true;
	}

	if (pPosInOld->y - pSizeIn->y >= pPosOut->y + pSizeOut->y		//前回の位置(Y軸)がY軸の最小値以上
		&& pPosIn->y - pSizeIn->y <= pPosOut->y + pSizeOut->y		//現在の位置(Y軸)がY軸の最小値以下
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X軸の最大値より内側
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X軸の最小値より内側
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z軸の最大値より内側
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z)		//Z軸の最小値より内側
	{//上側の当たり判定(+Y)
		pPosIn->y = (pPosOut->y + pSizeOut->y) + pSizeIn->y;
	}
	else if (pPosInOld->y + pSizeIn->y <= pPosOut->y - pSizeOut->y	//前回の位置(Y軸)がY軸の最小値以下
		&& pPosIn->y + pSizeIn->y >= pPosOut->y - pSizeOut->y		//現在の位置(Y軸)がY軸の最小値以上
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X軸の最大値より内側
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X軸の最小値より内側
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z軸の最大値より内側
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z)		//Z軸の最小値より内側
	{//下側の当たり判定(-Y)
		pPosIn->y = (pPosOut->y - pSizeOut->y) - pSizeIn->y;
		bIsPush = true;
	}

	return bIsPush;
}

//-----------------------------------------------------------------------------------------------
// 矩形の当たり判定3D(pPosの中心点が下)
//-----------------------------------------------------------------------------------------------
LibrarySpace::EStatePush LibrarySpace::BoxCollisionUnder3D(D3DXVECTOR3 * pPosIn, const D3DXVECTOR3 * pPosInOld, const D3DXVECTOR3 * pPosOut, const D3DXVECTOR3 * pSizeIn, const D3DXVECTOR3 * pSizeOut)
{
	//衝突状態
	EStatePush Push = PUSH_NONE;

	if (pPosInOld->x + pSizeIn->x <= pPosOut->x - pSizeOut->x		//前回の位置(X軸)がX軸の最小値以下
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//現在の位置(X軸)がX軸の最小値以上
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z軸の最大値より内側
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//Z軸の最小値より内側
		&& pPosIn->y <= pPosOut->y + pSizeOut->y		//Y軸の最大値より内側
		&& pPosIn->y >= pPosOut->y - pSizeOut->y)		//Y軸の最小値より内側
	{//左側の当たり判定(-X)
		pPosIn->x = (pPosOut->x - pSizeOut->x) - pSizeIn->x;
		Push = PUSH_X;
	}
	else if (pPosInOld->x - pSizeIn->x >= pPosOut->x + pSizeOut->x	//前回の位置(X軸)がX軸の最小値以上
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//現在の位置(X軸)がX軸の最小値以下
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z軸の最大値より内側
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//Z軸の最小値より内側
		&& pPosIn->y <= pPosOut->y + pSizeOut->y		//Y軸の最大値より内側
		&& pPosIn->y >= pPosOut->y - pSizeOut->y)		//Y軸の最小値より内側
	{//右側の当たり判定(+X)
		pPosIn->x = (pPosOut->x + pSizeOut->x) + pSizeIn->x;
		Push = PUSH_X;
	}
	else if (pPosInOld->z + pSizeIn->z <= pPosOut->z - pSizeOut->z		//前回の位置(Z軸)がZ軸の最小値以下
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//現在の位置(Z軸)がZ軸の最小値以上
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X軸の最大値より内側
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X軸の最小値より内側
		&& pPosIn->y <= pPosOut->y + pSizeOut->y		//Y軸の最大値より内側
		&& pPosIn->y >= pPosOut->y - pSizeOut->y)		//Y軸の最小値より内側
	{//手前側の当たり判定(-Z)
		pPosIn->z = (pPosOut->z - pSizeOut->z) - pSizeIn->z;
		Push = PUSH_Z;
	}
	else if (pPosInOld->z - pSizeIn->z >= pPosOut->z + pSizeOut->z	//前回の位置(Z軸)がZ軸の最小値以上
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//現在の位置(Z軸)がZ軸の最小値以下
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X軸の最大値より内側
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X軸の最小値より内側
		&& pPosIn->y <= pPosOut->y + pSizeOut->y		//Y軸の最大値より内側
		&& pPosIn->y >= pPosOut->y - pSizeOut->y)		//Y軸の最小値より内側
	{//奥側の当たり判定(+Z)
		pPosIn->z = (pPosOut->z + pSizeOut->z) + pSizeIn->z;
		Push = PUSH_Z;
	}
	else if (pPosInOld->y >= pPosOut->y + pSizeOut->y		//前回の位置(Y軸)がY軸の最小値以上
		&& pPosIn->y <= pPosOut->y + pSizeOut->y		//現在の位置(Y軸)がY軸の最小値以下
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X軸の最大値より内側
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X軸の最小値より内側
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z軸の最大値より内側
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z)		//Z軸の最小値より内側
	{//上側の当たり判定(+Y)
		pPosIn->y = (pPosOut->y + pSizeOut->y);
		Push = PUSH_JUMP;
	}
	else if (pPosInOld->y + pSizeIn->y <= pPosOut->y	//前回の位置(Y軸)がY軸の最小値以下
		&& pPosIn->y + pSizeIn->y >= pPosOut->y			//現在の位置(Y軸)がY軸の最小値以上
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X軸の最大値より内側
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X軸の最小値より内側
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z軸の最大値より内側
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z)		//Z軸の最小値より内側
	{//下側の当たり判定(-Y)
		pPosIn->y = (pPosOut->y - pSizeOut->y) - pSizeIn->y;
		Push = PUSH_Y;
	}

	return Push;
}

//-----------------------------------------------------------------------------------------------
// 球体の当たり判定
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::SphereCollision2D(const D3DXVECTOR3& posIn, const D3DXVECTOR3& posOut, const float& fsizeIn, const float& fsizeOut)
{
	//2つの座標差分を求める
	D3DXVECTOR3 Length = posIn - posOut;

	//座標差分から距離を求める
	float fLength = D3DXVec3Length(&Length);

	if (fsizeIn + fsizeOut > fLength)
	{//お互いのサイズの合計より距離が小さかったら
		return true;	//当たった
	}

	return false;		//当たってない
}

//-----------------------------------------------------------------------------------------------
// 円柱の当たり判定
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::CylinderCollision3D(const D3DXVECTOR3 & posIn, const D3DXVECTOR3 & posOut, const float & fsizeIn, const float & fsizeOut)
{
	//2つの座標差分を求める
	D3DXVECTOR2 Length = D3DXVECTOR2(posIn.x,posIn.z) - D3DXVECTOR2(posOut.x, posOut.z);

	//座標差分から距離を求める
	float fLength = D3DXVec2Length(&Length);

	if (fsizeIn + fsizeOut > fLength)
	{//お互いのサイズの合計より距離が小さかったら
		return true;	//当たった
	}

	return false;		//当たってない
}

//-----------------------------------------------------------------------------------------------
// 乱数の取得
//-----------------------------------------------------------------------------------------------
int LibrarySpace::GetRandNum(int nMax, int nMin)
{
	//最大値～最小値から乱数を取得
	int nRandNum = rand() % (nMax - nMin + 1) + nMin;

	return nRandNum;
}

//-----------------------------------------------------------------------------------------------
// 乱数(浮動小数)の取得
//-----------------------------------------------------------------------------------------------
float LibrarySpace::GetRandFloat(int nMax, int nMin, int nNumDiv)
{
	int nMaxNum = nMax * nNumDiv;
	int nMinNum = nMin * nNumDiv;
	
	//最大値～最小値から乱数を取得
	float fRandNum = (float)(rand() % (nMaxNum - nMinNum + 1) + nMinNum);
	fRandNum = fRandNum / nNumDiv;

	return fRandNum;
}

//-----------------------------------------------------------------------------------------------
// サインの取得
//-----------------------------------------------------------------------------------------------
float LibrarySpace::GetSinVec(float fRot, float fNumMul)
{
	return sinf(D3DX_PI * fRot) * fNumMul;
}

//-----------------------------------------------------------------------------------------------
// コサインの取得
//-----------------------------------------------------------------------------------------------
float LibrarySpace::GetCosVec(float fRot, float fNumMul)
{
	return cosf(D3DX_PI * fRot) * fNumMul;
}

//-----------------------------------------------------------------------------------------------
// 座標間の距離計算
//-----------------------------------------------------------------------------------------------
float LibrarySpace::SphereRange(D3DXVECTOR3 posStart, D3DXVECTOR3 posEnd)
{
	//2つの座標差分を求める
	D3DXVECTOR3 Length = posStart - posEnd;

	//座標差分から距離を求める
	float fLength = D3DXVec3Length(&Length);

	return fLength;
}
