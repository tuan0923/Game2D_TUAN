#ifndef _HIGHSCORE_H_		//���̃}�N����`������Ȃ�������
#define _HIGHSCORE_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//�}�N����`
#define MAX_HIGHSCORE		(8)			//�ő�X�R�A��

//�v���g�^�C�v�錾
void InitHighScore(void);
void UninitHighScore(void);
void UpdateHighScore(void);
void DrawHighScore(void);
void SetHighScore(int nScore);
void AddHighScore(int nValue);
int GetHighScore(void);
void SaveHighScore(void);
void LoadHighScore(void);
#endif 

