//----------------------------------------
//�@�x�N�g���̏���
//�@Author�F���슲��
//----------------------------------------
#include "vec.h"

//�x�N�g���̍\����
typedef struct
{
	D3DXVECTOR3 start;
	D3DXVECTOR3 end;
	D3DXVECTOR3 vec;
	float size;
	D3DXVECTOR3 nor;
}VECTOR;

VECTOR g_vecA[4];

//---------------------------------------------------
//	�x�N�g���̐ݒ�
//---------------------------------------------------
void SetVec(float X, float Z)
{
	g_vecA[0].start = D3DXVECTOR3(-X, 0.0f, Z);		//��
	g_vecA[0].end = D3DXVECTOR3(X, 0.0f, Z);		//��

	g_vecA[1].start = D3DXVECTOR3( X, 0.0f, -Z);	//��
	g_vecA[1].end = D3DXVECTOR3(-X, 0.0f, -Z);		//��

	g_vecA[2].start = D3DXVECTOR3( X, 0.0f,  Z);	//�E
	g_vecA[2].end = D3DXVECTOR3(X, 0.0f, -Z);		//�E

	g_vecA[3].start = D3DXVECTOR3(-X, 0.0f, -Z);	//��
	g_vecA[3].end = D3DXVECTOR3(-X, 0.0f, Z);		//��

}

//---------------------------------------------------
//	�x�N�g���̓����蔻��
//---------------------------------------------------
void CollisionVec(D3DXVECTOR3 pos, D3DXVECTOR3 posold, bool *bUse, float *move, D3DXVECTOR3 *rot)
{
	float nVectorData;

	//�G���A�̍L���������Ă��āA������Q�l�ɓ����蔻��p�̕����x�N�g�������
	for (int nCnt = 0; nCnt < 4; ++nCnt)
	{
		//------------------------------------------------<<vecA
		//�����v�Z
		g_vecA[nCnt].vec.x = g_vecA[nCnt].end.x - g_vecA[nCnt].start.x;
		g_vecA[nCnt].vec.z = g_vecA[nCnt].end.z - g_vecA[nCnt].start.z;

		//�傫���̌v�Z
		g_vecA[nCnt].size = (float)sqrt(g_vecA[nCnt].vec.x * g_vecA[nCnt].vec.x + g_vecA[nCnt].vec.z * g_vecA[nCnt].vec.z);

		//�x�N�g���̐��K��
		g_vecA[nCnt].vec.x = g_vecA[nCnt].vec.x / g_vecA[nCnt].size;
		g_vecA[nCnt].vec.z = g_vecA[nCnt].vec.z / g_vecA[nCnt].size;

		//------------------------------------------------<<vecB

		//�n�_
		D3DXVECTOR3 start;
		//�I�_
		D3DXVECTOR3 end;

		start = D3DXVECTOR3(pos.x, pos.y, pos.z);
		end = D3DXVECTOR3(g_vecA[nCnt].vec.x - posold.x, posold.y, g_vecA[nCnt].vec.z - posold.z);

		//����
		D3DXVECTOR3 vecB;

		//�����v�Z
		vecB.x = start.x - g_vecA[nCnt].start.x;
		vecB.z = start.z - g_vecA[nCnt].start.z;

		//�傫���v�Z
		float magnitude = (float)sqrt(vecB.x * vecB.x + vecB.z * vecB.z);

		//�x�N�g���̐��K��
		vecB.x = vecB.x / magnitude;
		vecB.z = vecB.z / magnitude;

		//----------------------------------------------------------<<�e�̐i�s
		//�i�s�x�N�g��
		D3DXVECTOR3 progress_vector;

		//�����v�Z
		progress_vector.x = end.x - start.x;
		progress_vector.z = end.z - start.z;

		//�傫���v�Z
		float progress_magnitude = (float)sqrt(progress_vector.x * progress_vector.x + progress_vector.z * progress_vector.z);

		//�x�N�g���̐��K��
		progress_vector.x = progress_vector.x / progress_magnitude;
		progress_vector.z = progress_vector.z / progress_magnitude;

		//�O�ς𗘗p���������蔻��
		nVectorData = (g_vecA[nCnt].vec.z * vecB.x) - (g_vecA[nCnt].vec.x * vecB.z);

		//���Ȃ�E���A���Ȃ獶��
		if (nVectorData < 0.0f)
		{//����������
			if (nCnt == 1 || nCnt == 0)
			{//�ړ��ʂ𔽑΂�
				*move *= -1;
			}

			//�p�x�𔽑΂�
			rot->y *= -1;
		}
	}
}
