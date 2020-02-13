#define _CRT_SECURE_NO_WARNINGS

//빌드 후 명령 xcopy "C:\Users\pumak\OneDrive\바탕 화면\Lecture\AI\four_in_a_row\interface\사목놀이 인터페이스\201310932.*" "C:\Users\pumak\OneDrive\바탕 화면\Lecture\AI\four_in_a_row\interface\사목놀이 인터페이스\Debug\" /s /i /y

#include <stdio.h>
#include <iostream>
#include <time.h>
#include "func.h"
#include <algorithm>
using namespace std;
int main()
{
	FILE *fp;
	FILE *rp;
	fp = fopen("C:\\Users\\rlat3\\source\\repos\\interface\\an.sgf", "r+");
	rp = fopen("C:\\Users\\rlat3\\source\\repos\\interface\\re.sgf", "w+");

	int left_moves = 0;


	int graph[MAP_SIZE][MAP_SIZE] = { 0 }, psuedo_graph[MAP_SIZE][MAP_SIZE] = { 0 }, x = 0, y = 0, person = 0;
	int result[8] = { 0 };
	int win_place[8] = { 0 };
	// # 1 int score_t_L[8] = { 0 }, score_t_S[8] = { 0 };
	//int L_S[2] = { 0 , 1000};

	char a = 0, b = 0, c = 0;
	int possible_moves[8] = { -1, -1, -1, -1, -1, -1, -1, -1 }, psuedo_possible_moves[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
	int largest[2] = { 0 };

	while (fscanf(fp, ";%c[%c%c]", &a, &b, &c) != EOF) {
		person = (int)a - BW; //B = -10, W = 10;
		x = (int)b - CHARTOINT;
		y = (int)c - CHARTOINT;
		graph[x][y] = person;
		psuedo_graph[x][y] = person;
		fprintf(rp, ";%c[%c%c]", a, b, c); //an.sgf에 돌 번호 저장
	}

	if (possible_n(graph, possible_moves) == 0) {
		//proceed
		for (int i = 0; i < MAP_SIZE; i++) {
			psuedo_possible_moves[i] = possible_moves[i];
		}
	}
	else {
		throw exception();
	}

	/*for (int s = 0; s < MAP_SIZE; s++) {
	left_moves += possible_moves[s] + 1; // left_moves becomes depth, always start from black
	}*/



	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%d \t", graph[j][i]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Possible moves:");

	for (int i = 0; i < 8; i++)
	{
		printf("%d", possible_moves[i]);
	}
	printf("\n");
	printf("\n");
	char d;
	char e;
	char f;



	if (person == 10 || a == 0) // 선공
	{
		d = 66, e = 97, f = 97;
		int as = 0;
		as = AichooseColumn(psuedo_graph, true, psuedo_possible_moves, 0);
		//evaluate(graph, possible_moves, &as);


		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				printf("%d \t", graph[j][i]);
			}
			printf("\n");
		}
		printf("\n");
		printf("Possible moves:");

		for (int i = 0; i < 8; i++)
		{
			printf("%d", possible_moves[i]);
		}
		printf("\n");
		printf("chosen column : %d", as);
		e = (int)as + CHARTOINT;//row
		f = possible_moves[as] + CHARTOINT;//col possible_moves : 7이면 최하단 0이면 최상단
		fprintf(rp, ";%c[%c%c]", d, e, f); //an.sgf에 돌 번호 저장
	}



	else
	{
		d = 87, e = 97, f = 97;
		int as = 0;
		as = AichooseColumn(psuedo_graph, true, psuedo_possible_moves, 1);
		//evaluate(graph, possible_moves, &as);


		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				printf("%d \t", graph[j][i]);
			}
			printf("\n");
		}
		printf("\n");
		printf("Possible moves:");

		for (int i = 0; i < 8; i++)
		{
			printf("%d", possible_moves[i]);
		}
		printf("\n");
		printf("chosen column : %d", as);
		e = (int)as + CHARTOINT;//row
		f = possible_moves[as] + CHARTOINT;//col possible_moves : 7이면 최하단 0이면 최상단
		fprintf(rp, ";%c[%c%c]", d, e, f); //an.sgf에 돌 번호 저장
	}





	//fprintf(fp, ";B[ad]", d, e, f);



	//# 2 win moves
	//win(graph, possible_moves, win_place);
	/*if (win_place[0] == 1) {
	printf("You Win!");
	throw exception();
	}*/



	fclose(fp);
	fclose(rp);

	return 0;
}