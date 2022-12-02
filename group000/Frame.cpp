//============================================================
//
//�I��������(Frame.cpp)
//AUTHOR:���X�ؗ��l
//
//=============================================================
#include "main.h"
#include"input.h"
#include"fade.h"
#include"sound.h"
#include"controller.h"
//==============================================================
//�O���[�o���ϐ�
//==============================================================
LPDIRECT3DTEXTURE9 g_pTextureFrame = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;//���_�o�b�t�@�ւ̂ۂ���
D3DXVECTOR3 g_FramePos;
int Count = 0;
//==============================================================
//�I�����̏���������
//==============================================================
void lnitFrame(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Frame.png",
		&g_pTextureFrame);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFrame,
		NULL);

	VERTEX_2D*pVtx;		//���_���փ|�C���^

	g_FramePos = D3DXVECTOR3(800.0f, 550.0f, 0.0f);

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̕`��
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffFrame->Unlock();
}

//==============================================================
//��������̏I��
//==============================================================
void UninitFrame(void)
{
	//�T�E���h�̒�~
	StopSound();
	//�e�N�X�`���̔j��
	if (g_pTextureFrame != NULL)
	{
		g_pTextureFrame->Release();
		g_pTextureFrame = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFrame != NULL)
	{
		g_pVtxBuffFrame->Release();
		g_pVtxBuffFrame = NULL;
	}
}

//==============================================================
//��������̍X�V����
//==============================================================
void UpdateFrame(void)
{
	// �t�F�[�h���̎擾
	FADE fade = GetFade();
	//����L�[(W�L�[�������ꂽ���ǂ���)
	if (GetKeyboardTrigger(DIK_W) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_DPAD_UP) == true)
	{
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_Frame);
		VERTEX_2D*pVtx;
		g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(420.0f, 400.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(860.0f, 400.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(420.0f, 485.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(860.0f, 485.0f, 0.0f);
		pVtx += 4;//�|�C���^���S���i�߂�
		Count = 0;
	}
	//����L�[(ENTER�L�[�������ꂽ���ǂ���)
	else if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A) == true && fade == FADE_NONE)
		{
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_Score);

			//���[�h�ݒ�
			SetFade(MODE_SOUSA);
		}




	//����L�[(S�L�[�������ꂽ���ǂ���)
	if (GetKeyboardTrigger(DIK_S) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_DPAD_DOWN) == true)
	{
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_Frame);
		VERTEX_2D*pVtx;
		g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(420.0f, 515.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(860.0f, 515.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(420.0f, 600.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(860.0f, 600.0f, 0.0f);
		pVtx += 4;//�|�C���^���S���i�߂�
		Count++;
	}
	//����L�[(ENTER�L�[�������ꂽ���ǂ���)
	if (Count > 0)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A) == true && fade == FADE_NONE)
		{
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_Score);

			//���[�h�ݒ�
			SetFade(MODE_SETUMEI);
			Count = 0;
		}
	}
}

//==============================================================
//��������̕`�揈��
//==============================================================
void DrawFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFrame);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//�I�����̐ݒ菈��
void SetFrame(D3DXVECTOR3 pos)
{

	VERTEX_2D*pVtx;
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);


	g_FramePos = pos;

	pVtx[0].pos = D3DXVECTOR3(420.0f, 400.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(860.0f, 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(420.0f, 485.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(860.0f, 485.0f, 0.0f);

	pVtx += 4;//�|�C���^���S���i�߂�

	g_pVtxBuffFrame->Unlock();
}