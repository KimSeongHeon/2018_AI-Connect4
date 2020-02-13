#include <stdio.h>
#include <iostream>
#include <time.h>
#include <algorithm>
#include "func.h"
#define DEPTH 5

using namespace std;
int possible_n(int graph[MAP_SIZE][MAP_SIZE], int possible_moves[MAP_SIZE]) {
	int cnt = 0;
	for (int i = 0; i < 8; i++) {
		for (int l = 0; l < 8; l++) {
			if (graph[i][7 - l] == 0) {
				possible_moves[i] = 7 - l;
				break;
			}
		}
	}
	for (int t = 0; t < 8; t++) {
		if (possible_moves[t] == -1) {
			cnt++;
		}
	}
	if (cnt > 8) {
		return -1;
	}
	return 0;
}

int Minmax(int depth, int graph[MAP_SIZE][MAP_SIZE], bool isPlayer, int myColumn, int possible_moves[MAP_SIZE], int alpha, int beta, int flag) {
	//printf("myColumn :%d", myColumn);
	//printf("%d",isPlayer);
	int temp = 0;
	int Tgraph[8][8], Tpossible_moves[8];
	for (int i = 0; i < MAP_SIZE; i++) {
		Tpossible_moves[i] = possible_moves[i];
		for (int j = 0; j < MAP_SIZE; j++) {
			Tgraph[j][i] = graph[j][i];
		}
	}
	int bestValue;
	bool Tplayer = !isPlayer;
	if (depth == 0) {
		int b = 0;
		int as;
		if (isPlayer == true) {
			if (Tpossible_moves[myColumn] > 0) {
				if (flag == 0)
				{
					Tgraph[myColumn][Tpossible_moves[myColumn]] = 10;
				}
				if (flag == 1)
				{
					Tgraph[myColumn][Tpossible_moves[myColumn]] = -10;
				}
				Tpossible_moves[myColumn] -= 1;
			}
		}
		else {

			if (Tpossible_moves[myColumn] > 0) {
				if (flag == 0)
				{
					Tgraph[myColumn][Tpossible_moves[myColumn]] = -10;
				}
				if (flag == 1)
				{
					Tgraph[myColumn][Tpossible_moves[myColumn]] = 10;
				}
				Tpossible_moves[myColumn] -= 1;
			}
		}

		as = evaluate(Tgraph, Tpossible_moves, &b, isPlayer, flag);
		//printf("%d ", as = evaluate(Tgraph, Tpossible_moves, &b,isPlayer));
		//printf("%d  ", as=evaluate2(graph, possible_moves));
		return as;
	}

	if (isPlayer == true) { // 내 차례면 max 초기값은 -1000
		int bestValue = -100000;

		if (Tpossible_moves[myColumn] > 0) {
			if (flag == 0)
			{
				Tgraph[myColumn][Tpossible_moves[myColumn]] = 10;
			}
			if (flag == 1)
			{
				Tgraph[myColumn][Tpossible_moves[myColumn]] = -10;
			}
			Tpossible_moves[myColumn] -= 1;
		}
		for (int i = 0; i < MAP_SIZE; i++) {
			//printf("detph cutting : %d to %d\n ", depth, depth - 1);
			int val = Minmax(depth - 1, Tgraph, Tplayer, i, Tpossible_moves, alpha, beta, flag);
			alpha = max(alpha, val);
			if (beta <= alpha)break;
			//bestValue = min(bestValue, val);
			



		}
		//printf("alpha : %d\n", alpha);
		//return bestValue;
		return alpha;
	}
	else if (isPlayer == false) { // 상대 차례면 min 초기값은 + 1000
		int bestValue = 100000;
		if (Tpossible_moves[myColumn] > 0) {
			if (flag == 0)
			{
				Tgraph[myColumn][Tpossible_moves[myColumn]] = -10;
			}
			if (flag == 1)
			{
				Tgraph[myColumn][Tpossible_moves[myColumn]] = 10;
			}
			Tpossible_moves[myColumn] -= 1;
		}
		for (int i = 0; i < MAP_SIZE; i++) {

			int val = Minmax(depth - 1, Tgraph, Tplayer, i, Tpossible_moves, alpha, beta, flag);
			//bestValue = min(bestValue, val);
			beta = min(beta, val);
			if (beta <= alpha)break;

		}
		//printf("beta : %d\n", beta);
		
		return beta;
	}
}


int AichooseColumn(int graph[MAP_SIZE][MAP_SIZE], bool isPlayer, int possible_moves[MAP_SIZE], int flag) {
	srand(time(NULL));
	int best = -100000; //초기값
	int col = 0;
	int t;
	int min = 0;
	int check = 0;
	int first,second;
	bool Tplayer = !isPlayer;
	int score[8] = { 0 };
	int depth1_score[8] = { 0 };
	int depth2_score[8] = { 0 };
	for (int i = 0; i < MAP_SIZE; i++) {
		int Tgraph[8][8], Tpossible_moves[8];
		for (int k = 0; k < MAP_SIZE; k++) {
			Tpossible_moves[k] = possible_moves[k];
			for (int j = 0; j < MAP_SIZE; j++) {
				Tgraph[j][k] = graph[j][k];
			}
		}
	    first = Minmax(0, Tgraph, Tplayer, i, Tpossible_moves, -100000, 100000, 0);
		depth1_score[i] = first; //-10 뒀을떄

		second = Minmax(0, Tgraph, Tplayer, i, Tpossible_moves, -100000, 100000, 1);
		depth2_score[i] = second; //10 뒀을때
		t = Minmax(DEPTH, Tgraph, Tplayer, i, Tpossible_moves, -100000, 100000, flag); // minmax 안에서 변경되는것 : isPlayer 함수내부 for문을 돌면서 자동변경되는것 : column
																					   //printf("Minmax %d: %d\n", i, t);

		score[i] = t;


	}
	int temp1;
	int temp2;
	int f_num[8] = { 0,1,2,3,4,5,6,7 };
	int s_num[8] = { 0,1,2,3,4,5,6,7 };

	for (int i = 0; i < 7; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			if (depth1_score[i] < depth1_score[j]) {
				temp1 = depth1_score[j];
				temp2 = f_num[j];
				depth1_score[j] = depth1_score[i];
				f_num[j] = f_num[i];
				depth1_score[i] = temp1;
				f_num[i] = temp2;

			}
		}
	}
	for (int i = 0; i < 7; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			if (depth2_score[i] < depth2_score[j]) {
				temp1 = depth2_score[j];
				temp2 = s_num[j];
				depth2_score[j] = depth2_score[i];
				s_num[j] = s_num[i];
				depth2_score[i] = temp1;
				s_num[i] = temp2;

			}
		}
	}

	
	
	
	
	

	

	if (depth1_score[0] - depth1_score[1] > 9000)
	{
		cout << "됨?? \n";
		for (int i = 0; i < 8; i++)
		{
			cout << depth1_score[i] << "\t";
		}
		cout << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << f_num[i] << "\t";
		}
		cout << "depth 1 : " << f_num[0] <<endl;
		cout << "\n";
		if (possible_moves[f_num[0]] > -1)
		{
			return f_num[0];
		}
		
		
	}
	

	if (depth2_score[0] - depth2_score[1] > 9000)
	{
		cout << "됨?? \n";
		for (int i = 0; i < 8; i++)
		{
			cout << depth2_score[i] << "\t";
		}
		cout << "\n";
		for (int i = 0; i < 8; i++)
		{
			cout << s_num[i] << "\t";
		}
		cout << "depth 2 : " << s_num[0] << endl;
		cout << "\n";
		if (possible_moves[s_num[0]] > -1)
		{
			return s_num[0];
		}
		
		
	}
	int num[8] = { 0,1,2,3,4,5,6,7 };

	for (int i = 0; i < 7; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			if (score[i] < score[j]) {
				temp1 = score[j];
				temp2 = num[j];
				score[j] = score[i];
				num[j] = num[i];
				score[i] = temp1;
				num[i] = temp2;

			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		cout << score[i] << "\t";
	}
	cout << "\n";
	for (int i = 0; i < 8; i++)
	{
		cout << num[i] << "\t";
	}

	col = num[0];
	check = 0;
	while (1)
	{
		if (possible_moves[col] <= -1)
		{
			col = num[check + 1];
			check++;
		}
		else
		{
			//cout << "한번쯤?";
			if (check == 7)
			{
				cout << "끝" << endl;
			}
			break;
		}
	}

	cout << "\n" << "col : " << col << "\n";

	//cout << "best :" << best << "\n";
	//cout << "col :" << col << "\n";
	return col;
}


int evaluate(int graph[8][8], int possible_moves[8], int *col, bool isplayer, int flag)
{
	srand(time(NULL));
	int score = 0;
	int fours = 0;
	int oppfours = 0;
	int threes = 0;
	int oppthrees = 0;
	int opptwos = 0;
	int oppones = 0;
	int twos = 0;
	int ones = 0;

	int Tgraph[8][8], Tpossible_moves[8];
	for (int i = 0; i < MAP_SIZE; i++) {
		Tpossible_moves[i] = possible_moves[i];
		for (int j = 0; j < MAP_SIZE; j++) {
			Tgraph[j][i] = graph[j][i];
		}
	}

	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout<<Tgraph[j][i]<<"\t";
		}
		cout << "\n";
		
	}
	cout << "\n";*/
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			if (Tgraph[j][i] == 0)
			{
				//★★★★★1개일때★★★★★★★★★★★ 
				//가로 오른쪽
				if (j < 7)
				{
					if (Tgraph[j + 1][i] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "가로 오른쪽 ones \n";
						ones++;
					}
					if (Tgraph[j + 1][i] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "가로 오른쪽 oppones \n";
						//cout << j << "\t" << i << "\n";
						//cout << Tgraph[j + 1][i] << "\n";
						oppones++;
					}
				}
				//가로 왼쪽 
				if (j > 0)
				{
					if (Tgraph[j - 1][i] == -10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "가로 왼쪽 ones \n";
						ones++;
					}
					if (Tgraph[j + 1][i] == 10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "가로 왼쪽 oppones \n";
						oppones++;
					}
				}
				//세로
				if (i > 0)
				{

					if (Tgraph[j][i + 1] == -10 && possible_moves[j] >= -1)
					{
						//cout << "세로 ones \n";
						ones++;
					}
					if (Tgraph[j][i + 1] == 10 && possible_moves[j] >= -1)
					{
						//cout << "세로 oppones \n";
						oppones++;
					}
				}
				//오른쪽 대각선 밑
				if (i < 7 && j < 7)
				{
					if (Tgraph[j + 1][i + 1] == -10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "오른쪽 대각선 밑 ones \n";
						ones++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "오른쪽 대각선 밑 oppones \n";
						oppones++;
					}

				}
				//오른쪽 대각선 위
				if (i >0 && j > 0)
				{
					if (Tgraph[j - 1][i - 1] == -10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "오른쪽 대각선 위 ones \n";
						ones++;
					}
					if (Tgraph[j - 1][i - 1] == 10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "오른쪽 대각선 위 oppones \n";
						oppones++;
					}

				}
				//왼쪽 대각선 위
				if (j < 7 && i>0)
				{
					if (Tgraph[j + 1][i - 1] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "왼쪽 대각선 위 ones \n";
						ones++;
					}
					if (Tgraph[j + 1][i - 1] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "왼쪽 대각선 위 oppones \n";
						oppones++;
					}
				}
				//왼쪽 대각선 아래
				if (j > 0 && i < 7)
				{
					if (Tgraph[j - 1][i + 1] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪾 대각선 아래 ones \n";
						ones++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪽 대각선 아래 oppones \n";
						oppones++;
					}
				}
				//★★★★★★★★★★★★★2개일떄
				//가로 왼쪽에 두개가 있을 경우
				if (j>1)
				{
					if (Tgraph[j - 2][i] == -10 && Tgraph[j - 1][i] == -10 && possible_moves[j] == possible_moves[j - 2] + 1)
					{
						//cout << "가로 왼쪽에 두개 twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j - 2][i] == 10 && Tgraph[j - 1][i] == 10 && possible_moves[j] == possible_moves[j - 2] + 1)
					{
						//cout << "가로 왼쪽에 두개 opptwos \n";
						oppones--;
						opptwos++;
					}

				}
				//가로 오른쪽에 두개가 있을 경우
				if (j<6)
				{
					if (Tgraph[j + 2][i] == -10 && Tgraph[j + 1][i] == -10 && possible_moves[j] == possible_moves[j + 2] + 1)
					{
						//cout << "가로 오른쪽에 두개 twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j + 2][i] == 10 && Tgraph[j + 1][i] == 10 && possible_moves[j] == possible_moves[j + 2] + 1)
					{
						//cout << "가로 오른쪽에 두개 opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//가로 오른쪽 , 왼쪽에 한개 한개씩
				if (j<7 && j>0)
				{
					if (Tgraph[j + 1][i] == -10 && Tgraph[j - 1][i] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "가로 오른쪽 한개 왼쪽에 한개 twos \n";
						ones--;
						ones--;
						twos++;
					}
					if (Tgraph[j + 1][i] == 10 && Tgraph[j - 1][i] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "가로 오른쪽 한개 왼쪽에 한개 opptwos \n";
						oppones--;
						oppones--;
						opptwos++;
					}
				}
				//세로 방향일때, 세로 밑에서 두개
				if (i<6)
				{
					if (Tgraph[j][i + 2] == -10 && Tgraph[j][i + 1] == -10 && possible_moves[j] >= -1)
					{
						//cout << "세로 두개 twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j][i + 2] == 10 && Tgraph[j][i + 1] == 10 && possible_moves[j] >= -1)
					{
						//cout << "세로 두개 opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//오른쪽 대각선방향일 때 위쪽에 2개
				if (j<6 && i<6)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j + 2][i + 2] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "오른쪽 대각선방향 위쪽 2개 twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j + 2][i + 2] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "오른쪽 대각선방향 위쪽 2개 opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//오른쪽 대각선 방향일 때 오른쪽 한개, 왼쪽 한개 있을 떄. ones 두번 뺴줄것
				if (j<7 && i<7 && j>0 && i>0)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j - 1][i - 1] == -10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "오른쪽 대각선방향 오른쪾 한개 왼쪽 한개 2개 twos \n";
						ones--;
						ones--;
						twos++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j + 2][i + 2] == 10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "오른쪽 대각선방향 오른쪾한개 왼쪽 한개 2개 opptwos \n";
						oppones--;
						oppones--;
						opptwos++;
					}
				}
				//오른쪽 대각선 방향일 때, 밑에쪽에 2개
				if (j>1 && i>1)
				{
					if (Tgraph[j - 1][i - 1] == -10 && Tgraph[j - 2][i - 2] == -10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "오른쪽 대각선방향 밑쪽 2개 twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j - 1][i - 1] == 10 && Tgraph[j - 2][i - 2] == 10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "오른쪽 대각선방향 밑쪽 2개 opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//왼쪽 대각선 방향일 때, 위쪽 2개
				if (j>1 && i<6)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j - 2][i + 2] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪽 대각선 방향 위쪽 2개 twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j - 2][i + 2] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪽 대각선 방향 위쪽 2개 opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//왼쪽 대각선 방향, 위쪽 1개 아래쪽 1개 ones 두번 뺴줄것
				if (j>0 && i<7 && j<7 && i>0)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j + 1][i - 1] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪽 대각선 방향, 위쪽 1개 아래쪽 1개 twos \n";
						ones--;
						ones--;
						twos++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j + 1][i - 1] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪽 대각선 방향, 위쪽 1개 아래쪽 1개 opptwos \n";
						oppones--;
						oppones--;
						opptwos++;
					}
				}
				//왼쪽 대각선 방향, 아래쪽 2개
				if (j<6 && i>1)
				{
					if (Tgraph[j + 1][i - 1] == -10 && Tgraph[j + 2][i - 2] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "왼쪽 대각선 방향 아래쪽 2개 twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j + 1][i - 1] == 10 && Tgraph[j + 2][i - 2] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "왼쪽 대각선 방향 아래쪽 2개 opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//★★★★★★★★★★★★★3개일떄
				//가로일때, 오른쪽 3개있을떄
				if (j<5)
				{
					if (Tgraph[j + 1][i] == -10 && Tgraph[j + 2][i] == -10 && Tgraph[j + 3][i] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "가로일때, 오른쪽 3개있을떄 threes \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j + 1][i] == 10 && Tgraph[j + 2][i] == 10 && Tgraph[j + 3][i] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "가로일때, 오른쪽 3개있을떄 oppthrees \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//가로일 때, 왼쪽 1개 오른쪽 2개있을 떄,
				if (j>0 && j<6)
				{
					if (Tgraph[j - 1][i] == -10 && Tgraph[j + 1][i] == -10 && Tgraph[j + 2][i] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "가로일 때, 왼쪽 1개 오른쪽 2개있을 떄, threes \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 1][i] == 10 && Tgraph[j + 1][i] == 10 && Tgraph[j + 2][i] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "가로일 때, 왼쪽 1개 오른쪽 2개있을 떄, oppthrees \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//가로일떄, 왼쪾 2개 오른쪾 1개있을떄.
				if (j>1 && j<7)
				{
					if (Tgraph[j - 2][i] == -10 && Tgraph[j - 1][i] == -10 && Tgraph[j + 1][i] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "가로일떄, 왼쪾 2개 오른쪾 1개있을떄., threes \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 2][i] == 10 && Tgraph[j - 1][i] == 10 && Tgraph[j + 1][i] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "가로일떄, 왼쪾 2개 오른쪾 1개있을떄., oppthrees \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//가로일떄, 왼쪽3개 있을떄.
				if (j>2)
				{
					if (Tgraph[j - 3][i] == -10 && Tgraph[j - 2][i] == -10 && Tgraph[j - 1][i] == -10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "가로일떄, 왼쪽3개 있을떄.., threes \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 3][i] == 10 && Tgraph[j - 2][i] == 10 && Tgraph[j - 1][i] == 10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "가로일떄, 왼쪽3개 있을떄., oppthrees \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//세로일때 밑에 3개
				if (i<5)
				{
					if (Tgraph[j][i + 1] == -10 && Tgraph[j][i + 2] == -10 && Tgraph[j][i + 3] == -10 && possible_moves[j] >= -1)
					{
						//cout << "세로일때 밑에 3개 threes \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j][i + 1] == 10 && Tgraph[j][i + 2] == 10 && Tgraph[j][i + 3] == 10 && possible_moves[j] >= -1)
					{
						//cout << "세로일때 밑에 3개 oppthrees \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//오른쪽 대각선 위로 3개
				if (i<5 && j<5)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j + 2][i + 2] == -10 && Tgraph[j + 3][i + 3] == -10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "오른쪽 대각선일떄 위로 3개 \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j + 2][i + 2] == 10 && Tgraph[j + 3][i + 3] == 10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "오른쪽 대각선일떄 위로 3개 \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//오른쪽 대각선 위로 2개 아래로 1개
				if (i<6 && j<6 && i>0 && j>0)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j + 2][i + 2] == -10 && Tgraph[j - 1][i - 1] == -10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "오른쪽 대각선 위로 2개 아래로 1개 \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j + 2][i + 2] == 10 && Tgraph[j - 1][i - 1] == 10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "오른쪽 대각선 위로 2개 아래로 1개 \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//오른쪽 대각선 위로 1개 아래로 2개
				if (i<7 && j<7 && i>1 && j>1)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j - 2][i - 2] == -10 && Tgraph[j - 1][i - 1] == -10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "오른쪽 대각선 위로 1개 아래로 2개 \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j - 2][i - 2] == 10 && Tgraph[j - 1][i - 1] == 10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "오른쪽 대각선 위로 2개 아래로 1개 \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//오른쪽 대각선  아래로 3개
				if (i>2 && j>2)
				{
					if (Tgraph[j - 1][i - 1] == -10 && Tgraph[j - 2][i - 2] == -10 && Tgraph[j - 3][i - 3] == -10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "오른쪽 대각선  아래로 3개 \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 1][i - 1] == 10 && Tgraph[j - 2][i - 2] == 10 && Tgraph[j - 3][i - 3] == 10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "오른쪽 대각선  아래로 3개 \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//왼쪾 대각선 위로 3개
				if (j>2 && i<5)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j - 2][i + 2] == -10 && Tgraph[j - 3][i + 3] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪾 대각선 위로 3개 \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j - 2][i + 2] == 10 && Tgraph[j - 3][i + 3] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪾 대각선 위로 3개 \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//왼쪽 대각선 위로 2개 아래로 1개
				if (j>0 && i>1 && i<7 && j<6)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j + 1][i - 1] == -10 && Tgraph[j + 2][i - 2] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪽 대각선 위로 2개 아래로 1개 \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j + 1][i - 1] == 10 && Tgraph[i + 2][j - 2] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪽 대각선 위로 2개 아래로 1개 \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//왼쪽 대각선 위로 1개 아래로 2개
				if (j>1 && i>0 && i<6 && j<7)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j - 2][i + 2] == -10 && Tgraph[j + 1][i - 1] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪽 대각선 위로 1개 아래로 2개 \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j - 2][i + 2] == 10 && Tgraph[j + 1][i - 1] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "왼쪽 대각선 위로 1개 아래로 2개 \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//왼쪽 대각선 아래로 3개
				if (j<5 && i>2)
				{
					if (Tgraph[j + 1][i - 1] == -10 && Tgraph[j + 2][i - 2] == -10 && Tgraph[j + 3][i - 3] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "왼쪽 대각선 아래로 3개 \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j + 1][i - 1] == 10 && Tgraph[j + 2][i - 2] == 10 && Tgraph[j + 3][i - 3] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "왼쪽 대각선 아래로 3개 \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}




			}
			// ★★★★★★★★★★★★★★★★★★★4개 일떄
			if (Tgraph[j][i] == -10 || Tgraph[j][i] == 10)
			{


				if (j<5)
				{

					if (Tgraph[j + 1][i] == -10 && Tgraph[j + 2][i] == -10 && Tgraph[j + 3][i] == -10)
					{

						
						if (Tgraph[j][i] == -10)
						{
							//cout << "가로일때, 오른쪽 3개있을떄 threes \n";
							fours++;
						}

					}
					if (Tgraph[j + 1][i] == 10 && Tgraph[j + 2][i] == 10 && Tgraph[j + 3][i] == 10)
					{
						
						if (Tgraph[j][i] == 10)
						{
							//cout << "가로일때, 오른쪽 3개있을떄 oppthrees \n";
							oppfours++;
						}
					}
				}

				//세로일때 밑에 3개
				if (i<5)
				{
					if (Tgraph[j][i + 1] == -10 && Tgraph[j][i + 2] == -10 && Tgraph[j][i + 3] == -10 && possible_moves[j] >= -1)
					{
						
						if (Tgraph[j][i] == -10)
						{
							//cout << "세로일때 밑에 3개 threes \n";
							fours++;
						}
					}
					if (Tgraph[j][i + 1] == 10 && Tgraph[j][i + 2] == 10 && Tgraph[j][i + 3] == 10 && possible_moves[j] >= -1)
					{
						//cout << "세로일때 밑에 3개 oppthrees \n";
						if (Tgraph[j][i] == 10)
						{
							//cout << "세로일때 밑에 3개 oppthrees \n";
							oppfours++;
						}
					}
				}
				//오른쪽 대각선 위로 3개
				if (i<5 && j<5)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j + 2][i + 2] == -10 && Tgraph[j + 3][i + 3] == -10)
					{
						
						if (Tgraph[j][i] == -10)
						{
							//cout << "오른쪽 대각선일떄 위로 3개 \n";
							fours++;
						}
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j + 2][i + 2] == 10 && Tgraph[j + 3][i + 3] == 10)
					{
						//cout << "오른쪽 대각선일떄 위로 3개 \n";
						if (Tgraph[j][i] == 10)
						{
							//cout << "오른쪽 대각선일떄 위로opp 3개 \n";
							oppfours++;
						}
					}
				}

				//왼쪾 대각선 위로 3개
				if (j>2 && i<5)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j - 2][i + 2] == -10 && Tgraph[j - 3][i + 3] == -10)
					{
						
						if (Tgraph[j][i] == -10)
						{
							//cout << "왼쪽 대각선일 떄 위로 3개 \n";
							fours++;
						}
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j - 2][i + 2] == 10 && Tgraph[j - 3][i + 3] == 10)
					{
						//cout << "왼쪾 대각선 위로 3개 \n";
						if (Tgraph[j][i] == 10)
						{
							//cout << "왼쪾 대각선 위로opp 3개 \n";
							oppfours++;
						}
					}
				}

			}


		}
	}

	score = fours * 10000 + threes * 100 + twos * 10 + ones * 1 + oppfours * (-10000) + oppthrees * (-100) + opptwos * (-10) + oppones * (-1);
	/*switch (depth)
	{
	case 1:
		score = score * 5;
		break;
	case 2:
		score = score * 4;
		break;
	case 3:
		score = score * 3;
		break;
	case 4:
		score = score * 2;
		break;
	default:
		score = score;
		break;
	}*/
	
	//cout << "\n score:"<<-score;
	//cout << "\n fours : "<<fours<<"\t" << threes << "\t" << twos << "\t" << ones ;
	//cout << "\n oppfours :"<<oppfours<<"\t" << oppthrees << "\t" << opptwos << "\t" << oppones <<"\n";
	if (flag == 1)
	{
		return -score;
	}
	if (flag == 0)
	{
		return score;
	}

	/*if (isplayer == true)
	{
	int dmax = 0;
	int num = 0;
	int n = 0;
	int temp[8] = { 0 };
	printf("score:");
	for (int i = 0; i < 8; i++)
	{
	printf("%d", score[i]);
	}
	printf("\n");
	for (int i = 0; i < 8; i++)
	{
	if (score[i]>dmax)

	dmax = score[i];
	}
	}
	for (int i = 0; i < 8; i++)
	{

	if (dmax == score[i])
	{
	temp[n] = i;
	n++;
	}
	}
	for (int i = 0; i < 8; i++)
	{
	printf("%d", temp[i]);
	}
	printf("\n n : %d", n);
	num = temp[rand() % n];
	printf("\n %d", temp[rand() % n]);
	printf("\n num:%d", num);
	*col = num;
	return dmax;

	}
	else
	{
	int dmin = score[0];
	int num = 0;
	int n = 0;
	int temp[8] = { 0 };
	printf("score:");
	for (int i = 0; i < 8; i++)
	{
	printf("%d", score[i]);
	}
	printf("\n");
	for (int i = 0; i < 8; i++)
	{
	if (score[i]<dmin)
	{
	dmin = score[i];
	}
	}
	for (int i = 0; i < 8; i++)
	{

	if (dmin == score[i])
	{
	temp[n] = i;
	n++;
	}
	}
	for (int i = 0; i < 8; i++)
	{
	printf("%d", temp[i]);
	}
	printf("\n n : %d", n);
	num = temp[rand() % n];
	printf("\n %d", temp[rand() % n]);
	printf("\n num:%d", num);
	*col = num;

	return dmin;
	}*/

}
//20181109  
//작동 개요
/*1. AichooseColumn
각 열마다 Minmax 값을 계산한다. 그 중에서 max 값을 가지는 열을 찾아서 return 한다. (후에 main에서 이 col에다 돌을 두게하면됨.)
*/
/*2. Minmax
isPlayer : true - 자기자신(아군)
false- 상대방(적군)
depth가 0일 때에는 말단 노드이므로, "myColumn에 두는 수"에 대한 evaluate를 실시해야함.(myColumn열에 둘 때의 기댓값)
depth가 0이 아니면, Minmax 알고리즘 재귀(depth는 1 줄이고, 플레이어 상태는 바꾸고)
알파 베타 컷오프는 추후에 할 예정!
evaluate에서 판을 읽고자 할 상황에는 graph 변수에 돌의 위치가 담겨있을 것이다! 그것을 활용할 것.

*/