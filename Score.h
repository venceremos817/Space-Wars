//Score


#ifndef _SCORE_H_
#define _SCORE_H_

//===== �萔��` =====
#define SCORE_DIGIT	(7)
#define MAX_NAME		(3)

//===== �\���̐錾 =====
typedef struct
{
	char szName[MAX_NAME];
	int nScore;
}SCORE;


//===== �v���g�^�C�v�錾 =====
void InitScore(void);
int GetScore(void);
void SetScore(int score);
void AddScore(int add);
//void UpdScore(void);
void DrawScore(void);
void UnInitScore(void);






#endif // !_SCORE_H_
