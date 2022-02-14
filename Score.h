//Score


#ifndef _SCORE_H_
#define _SCORE_H_

//===== 定数定義 =====
#define SCORE_DIGIT	(7)
#define MAX_NAME		(3)

//===== 構造体宣言 =====
typedef struct
{
	char szName[MAX_NAME];
	int nScore;
}SCORE;


//===== プロトタイプ宣言 =====
void InitScore(void);
int GetScore(void);
void SetScore(int score);
void AddScore(int add);
//void UpdScore(void);
void DrawScore(void);
void UnInitScore(void);






#endif // !_SCORE_H_
