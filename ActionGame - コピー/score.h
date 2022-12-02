#ifndef _SCORE_H_
#define _SCORE_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define SCORE_WIDTH		(20.0f)		//�X�R�A�̕�
#define SCORE_HEIGHT	(45.0f)		//�X�R�A�̍���
#define SCORE_MAX		(8)			//�X�R�A�̍ő包��

//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void SetScore(int nScore, D3DXVECTOR3 pos, float width, float height);
void DrawScore(void);
void AddScore(int nValue);
int GetScore(void);


#endif