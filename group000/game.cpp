//============================================================
//
//�Q�[���̏���(game.cpp)
//AUTHOR:���X�ؗ��l
//
//=============================================================
#include "main.h"
#include "input.h"
#include"TITLE.h"
#include"game.h"
#include"sound.h"
#include"Time.h"
#include"meshfield.h"
#include"shadow.h"
#include"player.h"
#include"wall.h"
#include"camera.h"
#include"light.h"
#include"score.h"
#include"time.h"
#include"disc.h"
#include"vec.h"
#include"model.h"
#include"Field.h"
#include"ink.h"
#include "mob.h"
#include"enemy.h"
#include "goal.h"

//==============================================================
//�Q�[���̏���������
//==============================================================
void lnitGAME(void)
{
	
	//���b�V���t�B�[���h�̏������ݒ�
	//InitMeshfield();

	//	�S�[������������
	InitGoal(350.0f, 600.0f);

	//�e�̏������ݒ�
	InitShadow();
	
	//�C���N�̏���������
	lnitInk();

	//�f�B�X�N�̏�����
	InitDisc();

	//�v���C���[�̏������ݒ�
	InitPlayer();

	//2�l�ڂ̃v���C���[�̏������ݒ�
	InitMob();

	//���f���̏������ݒ�
	//InitModel();

	//�G�l�~�[�̏������ݒ�
	InitEnemy();

    //���f���̏���������
	InitField();

	//�J�����̏������ݒ�
	InitCamera();

	//���C�g�̏������ݒ�
	InitLight();

	//�^�C�}�[����������
	InitTime();

	//�X�R�A����������
	InitScore();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_GAME);
	
}
//==============================================================
//�Q�[���̏I������
//==============================================================
void UninitGAME(void)
{
	//�T�E���h�̒�~
	StopSound();
	
	//�J�����̏I���ݒ�
	UninitCamera();

	//���b�V���t�B�[���h�̏I���ݒ�
	//UninitMeshfield();

	//�f�B�X�N�̏I������
	UninitDisc();

	//�v���C���[�̏I������
	UninitPlayer();

	//2�l�ڂ̃v���C���[�̏I���ݒ�
	UninitMob();

	//���f���̏I���ݒ�
	//UninitModel();

	//�G�l�~�[�̏I������
	UninitEnemy();

	//���f���̏I���ݒ�
	UninitField();

	//�e�̏I������
	UninitShadow();

	//�C���N�̏I������
	UninitInk();

	//�S�[���̏I������
	UninitGoal();

	//���C�g�̏I���ݒ�
	UninitLight();

	//�^�C�}�[�I������
	UninitTime();

	//�X�R�A�I������
	//UninitScore();
}

//==============================================================
//�Q�[���̕`�揈��
//==============================================================
void DrawGAME(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�r���[�|�[�g
	D3DVIEWPORT9 viewport;

	pDevice->GetViewport(&viewport);
	
	Camera * pCamera = GetCamera();

	for (int nCnt = 0; nCnt < 2; nCnt++,pCamera++)
	{
		pDevice->SetViewport(&pCamera->viewport);

		//��ʂ̃N���A
		pDevice->Clear(0,
			NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0),
			1.0f,
			0);

		SetCamera(nCnt);
		

		//�f�B�X�N�̕`�揈��
		DrawDisc();

		//���f���̕`�揈��
		//DrawModel();

		//�G�l�~�[�̕`�揈��
		DrawEnemy();

		//���f���̕`�揈��
		DrawField();

		//�S�[���`�揈��
		DrawGoal();

		//�e�̕`�揈��
		DrawShadow();

		//�C���N�̕`�揈��
		DrawInk();

		//�v���C���[�̕`�揈��
		DrawPlayer();

		//2�l�ڂ̃v���C���[�̕`��ݒ�
		DrawMob();

		//�^�C�}�[�`�揈��
		DrawTime();

		//�X�R�A�`�揈��
		DrawScore();
	}
		pDevice->SetViewport(&viewport);
}

//==============================================================
//�Q�[���̍X�V����
//==============================================================
void UpdateGAME(void)
{
	
	//���b�V���t�B�[���h�̍X�V�ݒ�
	//UpdateMeshfield();

	//�S�[���X�V����
	UpdateGoal();

	//�e�̍X�V�ݒ�
	UpdateShadow();

	//�C���N�̍X�V����
	UpdateInk();

	//�f�B�X�N�̍X�V����
	UpdateDisc();

	//�v���C���[�X�V����
	UpdatePlayer();

	//2�l�ڂ̃v���C���[�̍X�V�ݒ�
	UpdateMob();

	//���f���̍X�V�ݒ�
	//UpdateModel();

	//�G�l�~�[�̍X�V����
	UpdateEnemy();

	//���f���̍X�V�ݒ�
	UpdateField();

	//�J�����̍X�V�ݒ�
	UpdateCamera();

	//�ǂ̍X�V�ݒ�
	//UpdateWall();

	//���C�g�̍X�V�ݒ�
	UpdateLight();

	//�^�C�}�[�X�V����
	UpdateTime();

	//�X�R�A�X�V����
	UpdateScore();

	

	//����L�[(ENTER�L�[�������ꂽ���ǂ���)
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		//���[�h�ݒ�
 		SetMode(MODE_END);

	}
}