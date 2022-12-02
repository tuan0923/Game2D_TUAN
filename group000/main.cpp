//===================================================================
//
//3D�A�N�V����(main.cpp)
//Author:�匴���r
//
//===================================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "meshfield.h"
#include "shadow.h"
#include "wall.h"
#include "light.h"
#include"fade.h"
#include"sound.h"
#include"TITLE.h"
#include"result.h"
#include"game.h"
#include"SETUMEI.h"
#include"vec.h"
#include"controller.h"
#include"Sousa.h"
//===================================================================
//�O���[�o���ϐ�
//===================================================================
LPDIRECT3D9		g_pD3D = NULL;					//Direct3D�I�u�W�F�N�g�ւ̃|�C���^�[
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;		//Device3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;						//�����̃��[�h
MODE g_NextMode = MODE_MAX;						//���̃��[�h

//===================================================================
//���C���֐�
//===================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lCmdLine, int nCmdShow)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//��ʃT�C�Y�̍\����

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						//�E�B���h�E�̃X�^�C��
		WindowProc,						//�E�B���h�E�v���V�[�W��
		0,
		0,
		hInstance,						//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),//�^�X�N�o�[�A�C�R��
		LoadCursor(NULL,IDC_ARROW),		//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		//�N���C�A���g�̈�̔w�i�F
		NULL,							//���j���[�o�[
		CLASS_NAME,						//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	//�t�@�C���A�C�R��

	};
	HWND hWnd;		//�E�B���h�E�n���h��
	MSG msg;		//���b�Z�[�W���i�[����ϐ�

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E����
	hWnd = CreateWindowEx(
		0,							//�g���E�B���h�E�X�^�C��
		CLASS_NAME,					//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,				//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,				//�E�B���h�E�̍���x���W
		CW_USEDEFAULT,				//�E�B���h�E�̍���y���W
		(rect.right - rect.left),	//�E�B���h�E�̕�
		(rect.bottom - rect.top),	//�E�B���h�E�̍���		
		NULL,						//�e�E�B���h�E�̃n���h��
		NULL,						//���j���[�n���h��or�q�E�B���h�EID
		hInstance,					//�C���X�^���X�n���h��
		NULL);						//�E�B���h�E�����f�[�^

	//����������(�_�����������̏���)
	if (FAILED(Init(hInstance, hWnd, FALSE)))
	{//���������s
		return -1;
	}

	//�E�B���h�E�\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}

			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);		//�E�B���h�E�v���V�[�W���[�փ��b�Z�[�W�𑗏o
			}
		}

		else
		{//DirectX�̏���
			//�X�V����
			Update();
			//�`�揈��
			Draw();
		}
	}

	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//===================================================================
//�E�B���h�E�v���V�[�W���[
//===================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	//�L�[�~���̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:		//esc�L�[�������ꂽ

			DestroyWindow(hWnd);//�E�B���h�E��j������([WM_DESTROY]���b�Z�[�W�𑗂�)

			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//===================================================================
//����������
//===================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//�p�����[�^�[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//�Q�[����ʕ�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//�Q�[�����
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))

	{
		//Direct3D�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs���j
		if (FAILED((g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice))))

		{
			//Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_������CPU�ōs���j
			if (FAILED((g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice))))

			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	//�L�[�{�[�h����������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�W���C�p�b�h�̏�����
	InitJoypad();

	//�R���g���[���[�̏�����
	InitController();

	//�T�E���h�̏���������
	InitSound(hWnd);

	//���[�h�̐ݒ�
	SetMode(g_mode);

	//���[�h�̐ݒ�
	lnitFade(g_mode);

	SetVec(300.0f, 600.0f);

	//�e��I�u�W�F�N�g�̏���������
	return S_OK;
}

//===================================================================
//�I������
//===================================================================
void Uninit(void)
{
	//�e��I�u�W�F�N�g�̏I������

	//�L�[�{�[�h�I������
	UninitKeyboard();

	//�W���C�p�b�h�̏I������
	UninitJoypad();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	
}

//===================================================================
//�X�V����
//===================================================================
void Update(void)
{
	//�L�[�{�[�h�X�V����
	UpdateKeyboard();

	//Joypad�̍X�V����
	UpdateJoypad();

	//�R���g���[���[�̍X�V����
	UpdateController();

	switch (g_mode)
	{
	case MODE_TITLE:	//����������
		UpdateTITLE();
		break;

	//case MODE_SCENE:	//�������
	//	UpdateScene();
	//	break;

	//case MODE_TUTORIAL:	//�`���[�g���A�����
	//	UpdateTutorial();
	//	break;

	case MODE_GAME:		//�Q�[�����
		UpdateGAME();
		break;

	case MODE_END:		//�I�����
		UpdateResult();
		break;

	case MODE_SETUMEI:	//�Q�[���������
		UpdateSetumei();
		break;

	case MODE_SOUSA:	//����������
		UpdateSousa();
		break;
	}

	//���C���[�t���[�����[�h�̐ݒ�
	if (GetKeyboardPress(DIK_F1) == true)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	if (GetKeyboardPress(DIK_F2) == true)
	{//���ɖ߂�
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//===================================================================
//�`�揈��
//===================================================================
void Draw(void)
{
	Camera*pCamera = GetCamera();
	//��ʃN���A�i�o�b�t�@�N���A�AZ�o�b�t�@�̃N���A�j
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n������
		switch (g_mode)
		{
		case MODE_TITLE:	//����������
			DrawTITLE();
			break;

		//case MODE_SCENE:	//�������
		//	DrawScene();
		//	break;

		//case MODE_TUTORIAL:	//�`���[�g���A�����
		//	DrawTutorial();
		//	break;

		case MODE_GAME:		//�Q�[�����
							//�J�����̐ݒ菈��
			SetCamera(0);

			//g_pD3DDevice->SetViewport(&pCamera->viewport);
			////��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
			//g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

			DrawGAME();


			////�J�����̐ݒ菈��
			//SetCamera(1
			//);


			//g_pD3DDevice->SetViewport(&(pCamera + 1)->viewport);
			////��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
			//g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
			//DrawGAME();
			break;

		case MODE_END:		//�I�����
			DrawResult();
			break;

		case MODE_SETUMEI:	//�Q�[���������
			DrawSetumei();
			break;

		case MODE_SOUSA:	//����������
			DrawSousa();
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();

		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===================================================================
//�f�o�C�X�̎擾
//===================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//===================================================================
//���[�h�̐ݒ�
//===================================================================
void SetMode(MODE mode)
{
	//���݂̉�ʂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE:	//����������
		UninitTITLE();
		break;

	//case MODE_SCENE:	//�������
	//	UninitScene();
	//	break;

	//case MODE_TUTORIAL:	//�`���[�g���A�����
	//	UninitTutorial();
	//	break;

	case MODE_GAME:		//�Q�[�����
		UninitGAME();
		break;

	case MODE_END:		//�I�����
		UninitResult();
		break;

	case MODE_SETUMEI:	//�Q�[���������
		UninitSetumei();
		break;

	case MODE_SOUSA:	//����������
		UninitSousa();
		break;

	}

	//�V������ʂ̏���������
	switch (mode)
	{
	case MODE_TITLE:
		lnitTITLE();
		break;

	//case MODE_SCENE:	//�������
	//	InitScene();
	//	break;

	//case MODE_TUTORIAL:	//�`���[�g���A�����
	//	InitTutorial ();
	//	break;

	case MODE_GAME:		//�Q�[�����
		lnitGAME();
		break;

	case MODE_END:		//�I�����
		lnitResult();
		break;

	case MODE_SETUMEI:	//�Q�[���������
		lnitSetumei();
		break;

	case MODE_SOUSA:	//����������
		lnitSousa();
		break;
	}

	g_mode = mode;		//���݂̉�ʂ�؂�ւ���
}

//===================================================================
//Mode�̗\��
//===================================================================
void NextMode(MODE mode)
{
	g_NextMode = mode;	//���̃��[�h��\�񂷂�
}

//===================================================================
//���[�h�̎擾
//===================================================================
MODE GetMode(void)
{
	return g_mode;
}