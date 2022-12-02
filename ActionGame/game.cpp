//========================================================
// game.cpp
// 2DGame
//Author: �e���A��
//========================================================
#include "game.h"
#include "input.h"
#include "main.h"
#include "fade.h"

LPDIRECT3DTEXTURE9 g_pTextureGame = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGame = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//================================================
//�Q�[����ʂ̏���������
//================================================
void InitGame(void)
{
	//�w�i����������
	InitBG();

	InitTime();
	//�|���S���̏������ݒ�
	InitPlayer();

	InitBlock();

	InitEnemy();

	InitItem();

	InitScore();
	
	InitExplosion();
	PlaySound(SOUND_LABEL_BGM001);
}
//================================================
//�Q�[����ʂ̏I������
//================================================
void UninitGame(void)
{
	//�w�i�̏I������
	UninitBG();

	UninitTime();
	//�e��I�u�W�F�N�g�̏I������
	UninitPlayer();

	UninitBlock();
	
	UninitEnemy();

	UninitItem();

	UninitScore();
	 
	UninitExplosion();
	////�T�E���h�̒�~
	StopSound();


}
//================================================
//�Q�[����ʂ̍X�V����
//================================================
void UpdateGame(void)
{
	//�w�i�X�V����
	UpdateBG();

	//�e��I�u�W�F�N�g�̍X�V����
	UpdatePlayer();

	UpdateBlock();

	UpdateEnemy();

	UpdateItem();

	UpdateExplosion();

	UpdateScore();

	UpdateTime();

	FADE pFade;
	pFade = GetFade();
	if (GetKeyboardTrigger(DIK_RETURN) == true && pFade == FADE_NONE)
	{
		SetFade(MODE_RESULT);
	}

}
//================================================
//�Q�[����ʂ̕`�揈��
//================================================
void DrawGame(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��
	DrawBG();

	DrawBlock();

	DrawExplosion();
	//�v���C���[�̕`�揈��
	DrawPlayer();

	DrawEnemy();

	DrawItem();

	DrawScore();

	DrawTime();
}