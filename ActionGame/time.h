#ifndef _TIME_H_
#define _TIME_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define TIME_WIDTH		(20.0f)		//�X�R�A�̕�
#define TIME_HEIGHT		(45.0f)		//�X�R�A�̍���
#define TIME_MAX		(3)			//�X�R�A�̍ő包��

//�v���g�^�C�v�錾
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);

#endif