//-------------------------------------------
//
//�X�R�A���[score.h]
//Author:���앑
//
//-------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�v���g�^�C�v�錾
void InitScore(void);						//����������
void UninitScore(void);						//�I������
void UpdateScore(void);						//�X�V����
void DrawScore(void);						//�`�揈��
void SetScore(int nOrder,int nScore);		//�ݒ菈��
void AddScore(int order, int nValue);		//���Z����
int GetScore(int order);					//�X�R�A�̎擾

#endif