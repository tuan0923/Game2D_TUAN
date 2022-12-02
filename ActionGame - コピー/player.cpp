//========================================================
// player.cpp
// 2DGame
//Author: �e���A��
//========================================================
#include "main.h"
#include "enemy.h"
#include "player.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^

PLAYER g_aPlayer;	//�v���C���[�\����

//================================================
//�v���C���[�̏������ݒ�
//================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D *pVtx;	//���_���̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//player000.png",
		&g_pTexturePlayer);
	g_aPlayer.bDisp = false;
	g_aPlayer.bIsJumping = false;
	g_aPlayer.nCounterAnimPlayer = 0;
	g_aPlayer.nPatternAnimPlayer = 0;
	g_aPlayer.pos = D3DXVECTOR3(500.0f, 700.f, 0.0f);
	g_aPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x - (PLAYER_WIDTH / 2), g_aPlayer.pos.y - PLAYER_HEIGTH, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + (PLAYER_WIDTH / 2), g_aPlayer.pos.y - PLAYER_HEIGTH, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x - (PLAYER_WIDTH / 2), g_aPlayer.pos.y , 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + (PLAYER_WIDTH / 2), g_aPlayer.pos.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffPlayer->Unlock();
}
//================================================
//�|���S���̏I������
//================================================
void UninitPlayer(void)
{
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
	//�e�N�X�`���j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}
//================================================
//�v���C���[�̂̍X�V����
//================================================
void UpdatePlayer(void)
{

	VERTEX_2D *pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//�ړ�����
	if (GetKeyboardPress(DIK_D) == true)
	{ // �E��ړ�
		
		g_aPlayer.move.x += sinf(D3DX_PI * 0.5f) * 1.50f;
		g_aPlayer.move.y += cosf(D3DX_PI * 0.5f) * 1.50f;
		
		g_aPlayer.nDirectionMove = 0;
		
	}
	if (GetKeyboardPress(DIK_A) == true)
	{ // ����ړ�
		
		g_aPlayer.move.x += sinf(-D3DX_PI * 0.5f) * 1.50f;
		g_aPlayer.move.y += cosf(-D3DX_PI * 0.5f) * 1.50f;
		
		g_aPlayer.nDirectionMove = 1;
		
	}

	//�ړ��ʍX�V�i�����j
	g_aPlayer.move.x += (0.0f - g_aPlayer.move.x)*0.19f;	//�ړI�̒l-���݂̒l*�����W��

	//JUMP
	if (GetKeyboardTrigger(DIK_W) == true)
	{//SPACE�L�[������
		if (g_aPlayer.bIsJumping == false)
		{
			PlaySound(SOUND_LABEL_SE_JUMP);
			g_aPlayer.move.y = -19.0f;
			g_aPlayer.bIsJumping = true;
			if (g_aPlayer.nPatternAnimPlayer == 0 || g_aPlayer.nPatternAnimPlayer == 2)
			{//�W�����v���̃|�[�Y
				g_aPlayer.nPatternAnimPlayer += 1;

			}
		}
	}
	if (g_aPlayer.bIsJumping != true )
	{
		if (g_aPlayer.move.x >= 1.0f || g_aPlayer.move.x <= -1.0f)
		{//�ړ����Ă�����
			g_aPlayer.nCounterAnimPlayer++;
			//�W�����v���̃A�j���[�V�����Œ�
			if (g_aPlayer.nCounterAnimPlayer % 9 == 4)
			{//�p�^�[�����𑝂₷
				g_aPlayer.nPatternAnimPlayer++;
			}
			if (g_aPlayer.nPatternAnimPlayer == 4)
			{//�p�^�[������߂�
				g_aPlayer.nPatternAnimPlayer = 0;
			}
		}
		else
		{//�ړ���~
			if (g_aPlayer.nPatternAnimPlayer == 1 || g_aPlayer.nPatternAnimPlayer == 3)
			{//�p�^�[��1,3��������
				g_aPlayer.nPatternAnimPlayer ++ ;

				if (g_aPlayer.nPatternAnimPlayer == 4)
				{//�p�^�[������߂�
					g_aPlayer.nPatternAnimPlayer = 0;
				}
			}
		}
	}

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((0.0f + (0.25f*g_aPlayer.nPatternAnimPlayer)), 0.0f + (0.5f*g_aPlayer.nDirectionMove));
	pVtx[1].tex = D3DXVECTOR2((0.25f + (0.25f*g_aPlayer.nPatternAnimPlayer)), 0.0f + 0.5f*(g_aPlayer.nDirectionMove));
	pVtx[2].tex = D3DXVECTOR2((0.0f + (0.25f*g_aPlayer.nPatternAnimPlayer)), 0.5f + (0.5f*g_aPlayer.nDirectionMove));
	pVtx[3].tex = D3DXVECTOR2((0.25f + (0.25f*g_aPlayer.nPatternAnimPlayer)), 0.5f + (0.5f*g_aPlayer.nDirectionMove));

	//�O��̈ʒu��ۑ�
	g_aPlayer.posOld = g_aPlayer.pos;
	/*a_aPlayer.pos += g_aPlayer.move;*/
	//�d�͉��Z
	g_aPlayer.move.y += 1.00f;
	////�ʒu�X�V
	g_aPlayer.pos.x += g_aPlayer.move.x;
	g_aPlayer.pos.y += g_aPlayer.move.y;
	//��ʊO�ɏo�Ȃ��悤��
	if (g_aPlayer.pos.x > SCREEN_WIDTH - 17.5f)
	{
		g_aPlayer.pos.x = SCREEN_WIDTH - 17.5f;
	}
	if (g_aPlayer.pos.y > SCREEN_HEIGHT - 10.0f)
	{
		g_aPlayer.pos.y = SCREEN_HEIGHT - 10.0f;
		g_aPlayer.bIsJumping = false;
	}
	if (g_aPlayer.pos.x < 0.0f)
	{
		g_aPlayer.pos.x = 0.0f;

	}
			
	
	//�u���b�N�Ƃ̓����蔻��
	bool bIsLanding = CollisionBlock(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move,25.0f/2, 100.0f);
	if (bIsLanding == true)
	{
		g_aPlayer.bIsJumping = false;
		
	}

	//Item�̓����蔻��
	CollisionItem(&g_aPlayer.pos, 25.0f/2, 100.0f);
	//Enemy �̓����蔻��
	CollisionEnemy(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, 25.0f / 2 ,100.0f);

	
	if (g_aPlayer.pos.y >= SCREEN_HEIGHT)
	{//�n�ʂ�艺�ɂ����Ȃ�
		g_aPlayer.pos.y = SCREEN_HEIGHT;
		g_aPlayer.move.y = 0.0f;
		g_aPlayer.bIsJumping = false;
	}
	if (g_aPlayer.bDisp == true)
	{
		g_aPlayer.nCounterState--;
		if (g_aPlayer.nCounterState <= 0)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_aPlayer.bDisp = false;
		}
	}
	//���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x - (PLAYER_WIDTH / 2), g_aPlayer.pos.y - PLAYER_HEIGTH, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + (PLAYER_WIDTH / 2), g_aPlayer.pos.y - PLAYER_HEIGTH, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x - (PLAYER_WIDTH / 2), g_aPlayer.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + (PLAYER_WIDTH / 2), g_aPlayer.pos.y, 0.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

}
//================================================
// Hit Player
//================================================
void HitPlayer(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	g_aPlayer.nCounterState = 15;
	g_aPlayer.bDisp = true;
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(225, 5, 5, 5);
	pVtx[1].col = D3DCOLOR_RGBA(225, 5, 5, 5);
	pVtx[2].col = D3DCOLOR_RGBA(225, 5, 5, 5);
	pVtx[3].col = D3DCOLOR_RGBA(225, 5, 5, 5);
	
	g_pVtxBuffPlayer->Unlock();


}
//================================================
//�|���S���̕`�揈��
//================================================
void DrawPlayer(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}