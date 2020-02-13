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

	if (isPlayer == true) { // �� ���ʸ� max �ʱⰪ�� -1000
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
	else if (isPlayer == false) { // ��� ���ʸ� min �ʱⰪ�� + 1000
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
	int best = -100000; //�ʱⰪ
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
		depth1_score[i] = first; //-10 ������

		second = Minmax(0, Tgraph, Tplayer, i, Tpossible_moves, -100000, 100000, 1);
		depth2_score[i] = second; //10 ������
		t = Minmax(DEPTH, Tgraph, Tplayer, i, Tpossible_moves, -100000, 100000, flag); // minmax �ȿ��� ����Ǵ°� : isPlayer �Լ����� for���� ���鼭 �ڵ�����Ǵ°� : column
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
		cout << "��?? \n";
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
		cout << "��?? \n";
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
			//cout << "�ѹ���?";
			if (check == 7)
			{
				cout << "��" << endl;
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
				//�ڡڡڡڡ�1���϶��ڡڡڡڡڡڡڡڡڡڡ� 
				//���� ������
				if (j < 7)
				{
					if (Tgraph[j + 1][i] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "���� ������ ones \n";
						ones++;
					}
					if (Tgraph[j + 1][i] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "���� ������ oppones \n";
						//cout << j << "\t" << i << "\n";
						//cout << Tgraph[j + 1][i] << "\n";
						oppones++;
					}
				}
				//���� ���� 
				if (j > 0)
				{
					if (Tgraph[j - 1][i] == -10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "���� ���� ones \n";
						ones++;
					}
					if (Tgraph[j + 1][i] == 10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "���� ���� oppones \n";
						oppones++;
					}
				}
				//����
				if (i > 0)
				{

					if (Tgraph[j][i + 1] == -10 && possible_moves[j] >= -1)
					{
						//cout << "���� ones \n";
						ones++;
					}
					if (Tgraph[j][i + 1] == 10 && possible_moves[j] >= -1)
					{
						//cout << "���� oppones \n";
						oppones++;
					}
				}
				//������ �밢�� ��
				if (i < 7 && j < 7)
				{
					if (Tgraph[j + 1][i + 1] == -10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "������ �밢�� �� ones \n";
						ones++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "������ �밢�� �� oppones \n";
						oppones++;
					}

				}
				//������ �밢�� ��
				if (i >0 && j > 0)
				{
					if (Tgraph[j - 1][i - 1] == -10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "������ �밢�� �� ones \n";
						ones++;
					}
					if (Tgraph[j - 1][i - 1] == 10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "������ �밢�� �� oppones \n";
						oppones++;
					}

				}
				//���� �밢�� ��
				if (j < 7 && i>0)
				{
					if (Tgraph[j + 1][i - 1] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "���� �밢�� �� ones \n";
						ones++;
					}
					if (Tgraph[j + 1][i - 1] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "���� �밢�� �� oppones \n";
						oppones++;
					}
				}
				//���� �밢�� �Ʒ�
				if (j > 0 && i < 7)
				{
					if (Tgraph[j - 1][i + 1] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "�ަU �밢�� �Ʒ� ones \n";
						ones++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "���� �밢�� �Ʒ� oppones \n";
						oppones++;
					}
				}
				//�ڡڡڡڡڡڡڡڡڡڡڡڡ�2���ϋ�
				//���� ���ʿ� �ΰ��� ���� ���
				if (j>1)
				{
					if (Tgraph[j - 2][i] == -10 && Tgraph[j - 1][i] == -10 && possible_moves[j] == possible_moves[j - 2] + 1)
					{
						//cout << "���� ���ʿ� �ΰ� twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j - 2][i] == 10 && Tgraph[j - 1][i] == 10 && possible_moves[j] == possible_moves[j - 2] + 1)
					{
						//cout << "���� ���ʿ� �ΰ� opptwos \n";
						oppones--;
						opptwos++;
					}

				}
				//���� �����ʿ� �ΰ��� ���� ���
				if (j<6)
				{
					if (Tgraph[j + 2][i] == -10 && Tgraph[j + 1][i] == -10 && possible_moves[j] == possible_moves[j + 2] + 1)
					{
						//cout << "���� �����ʿ� �ΰ� twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j + 2][i] == 10 && Tgraph[j + 1][i] == 10 && possible_moves[j] == possible_moves[j + 2] + 1)
					{
						//cout << "���� �����ʿ� �ΰ� opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//���� ������ , ���ʿ� �Ѱ� �Ѱ���
				if (j<7 && j>0)
				{
					if (Tgraph[j + 1][i] == -10 && Tgraph[j - 1][i] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "���� ������ �Ѱ� ���ʿ� �Ѱ� twos \n";
						ones--;
						ones--;
						twos++;
					}
					if (Tgraph[j + 1][i] == 10 && Tgraph[j - 1][i] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "���� ������ �Ѱ� ���ʿ� �Ѱ� opptwos \n";
						oppones--;
						oppones--;
						opptwos++;
					}
				}
				//���� �����϶�, ���� �ؿ��� �ΰ�
				if (i<6)
				{
					if (Tgraph[j][i + 2] == -10 && Tgraph[j][i + 1] == -10 && possible_moves[j] >= -1)
					{
						//cout << "���� �ΰ� twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j][i + 2] == 10 && Tgraph[j][i + 1] == 10 && possible_moves[j] >= -1)
					{
						//cout << "���� �ΰ� opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//������ �밢�������� �� ���ʿ� 2��
				if (j<6 && i<6)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j + 2][i + 2] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "������ �밢������ ���� 2�� twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j + 2][i + 2] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "������ �밢������ ���� 2�� opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//������ �밢�� ������ �� ������ �Ѱ�, ���� �Ѱ� ���� ��. ones �ι� ���ٰ�
				if (j<7 && i<7 && j>0 && i>0)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j - 1][i - 1] == -10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "������ �밢������ �����U �Ѱ� ���� �Ѱ� 2�� twos \n";
						ones--;
						ones--;
						twos++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j + 2][i + 2] == 10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "������ �밢������ �����U�Ѱ� ���� �Ѱ� 2�� opptwos \n";
						oppones--;
						oppones--;
						opptwos++;
					}
				}
				//������ �밢�� ������ ��, �ؿ��ʿ� 2��
				if (j>1 && i>1)
				{
					if (Tgraph[j - 1][i - 1] == -10 && Tgraph[j - 2][i - 2] == -10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "������ �밢������ ���� 2�� twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j - 1][i - 1] == 10 && Tgraph[j - 2][i - 2] == 10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "������ �밢������ ���� 2�� opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//���� �밢�� ������ ��, ���� 2��
				if (j>1 && i<6)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j - 2][i + 2] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "���� �밢�� ���� ���� 2�� twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j - 2][i + 2] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "���� �밢�� ���� ���� 2�� opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//���� �밢�� ����, ���� 1�� �Ʒ��� 1�� ones �ι� ���ٰ�
				if (j>0 && i<7 && j<7 && i>0)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j + 1][i - 1] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "���� �밢�� ����, ���� 1�� �Ʒ��� 1�� twos \n";
						ones--;
						ones--;
						twos++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j + 1][i - 1] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "���� �밢�� ����, ���� 1�� �Ʒ��� 1�� opptwos \n";
						oppones--;
						oppones--;
						opptwos++;
					}
				}
				//���� �밢�� ����, �Ʒ��� 2��
				if (j<6 && i>1)
				{
					if (Tgraph[j + 1][i - 1] == -10 && Tgraph[j + 2][i - 2] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "���� �밢�� ���� �Ʒ��� 2�� twos \n";
						ones--;
						twos++;
					}
					if (Tgraph[j + 1][i - 1] == 10 && Tgraph[j + 2][i - 2] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "���� �밢�� ���� �Ʒ��� 2�� opptwos \n";
						oppones--;
						opptwos++;
					}
				}
				//�ڡڡڡڡڡڡڡڡڡڡڡڡ�3���ϋ�
				//�����϶�, ������ 3��������
				if (j<5)
				{
					if (Tgraph[j + 1][i] == -10 && Tgraph[j + 2][i] == -10 && Tgraph[j + 3][i] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "�����϶�, ������ 3�������� threes \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j + 1][i] == 10 && Tgraph[j + 2][i] == 10 && Tgraph[j + 3][i] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "�����϶�, ������ 3�������� oppthrees \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//������ ��, ���� 1�� ������ 2������ ��,
				if (j>0 && j<6)
				{
					if (Tgraph[j - 1][i] == -10 && Tgraph[j + 1][i] == -10 && Tgraph[j + 2][i] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "������ ��, ���� 1�� ������ 2������ ��, threes \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 1][i] == 10 && Tgraph[j + 1][i] == 10 && Tgraph[j + 2][i] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "������ ��, ���� 1�� ������ 2������ ��, oppthrees \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//�����ϋ�, �ަU 2�� �����U 1��������.
				if (j>1 && j<7)
				{
					if (Tgraph[j - 2][i] == -10 && Tgraph[j - 1][i] == -10 && Tgraph[j + 1][i] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "�����ϋ�, �ަU 2�� �����U 1��������., threes \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 2][i] == 10 && Tgraph[j - 1][i] == 10 && Tgraph[j + 1][i] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "�����ϋ�, �ަU 2�� �����U 1��������., oppthrees \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//�����ϋ�, ����3�� ������.
				if (j>2)
				{
					if (Tgraph[j - 3][i] == -10 && Tgraph[j - 2][i] == -10 && Tgraph[j - 1][i] == -10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "�����ϋ�, ����3�� ������.., threes \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 3][i] == 10 && Tgraph[j - 2][i] == 10 && Tgraph[j - 1][i] == 10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "�����ϋ�, ����3�� ������., oppthrees \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//�����϶� �ؿ� 3��
				if (i<5)
				{
					if (Tgraph[j][i + 1] == -10 && Tgraph[j][i + 2] == -10 && Tgraph[j][i + 3] == -10 && possible_moves[j] >= -1)
					{
						//cout << "�����϶� �ؿ� 3�� threes \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j][i + 1] == 10 && Tgraph[j][i + 2] == 10 && Tgraph[j][i + 3] == 10 && possible_moves[j] >= -1)
					{
						//cout << "�����϶� �ؿ� 3�� oppthrees \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//������ �밢�� ���� 3��
				if (i<5 && j<5)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j + 2][i + 2] == -10 && Tgraph[j + 3][i + 3] == -10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "������ �밢���ϋ� ���� 3�� \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j + 2][i + 2] == 10 && Tgraph[j + 3][i + 3] == 10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "������ �밢���ϋ� ���� 3�� \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//������ �밢�� ���� 2�� �Ʒ��� 1��
				if (i<6 && j<6 && i>0 && j>0)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j + 2][i + 2] == -10 && Tgraph[j - 1][i - 1] == -10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "������ �밢�� ���� 2�� �Ʒ��� 1�� \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j + 2][i + 2] == 10 && Tgraph[j - 1][i - 1] == 10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "������ �밢�� ���� 2�� �Ʒ��� 1�� \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//������ �밢�� ���� 1�� �Ʒ��� 2��
				if (i<7 && j<7 && i>1 && j>1)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j - 2][i - 2] == -10 && Tgraph[j - 1][i - 1] == -10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "������ �밢�� ���� 1�� �Ʒ��� 2�� \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j - 2][i - 2] == 10 && Tgraph[j - 1][i - 1] == 10 && possible_moves[j] == possible_moves[j + 1] - 1)
					{
						//cout << "������ �밢�� ���� 2�� �Ʒ��� 1�� \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//������ �밢��  �Ʒ��� 3��
				if (i>2 && j>2)
				{
					if (Tgraph[j - 1][i - 1] == -10 && Tgraph[j - 2][i - 2] == -10 && Tgraph[j - 3][i - 3] == -10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "������ �밢��  �Ʒ��� 3�� \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 1][i - 1] == 10 && Tgraph[j - 2][i - 2] == 10 && Tgraph[j - 3][i - 3] == 10 && possible_moves[j] == possible_moves[j - 1] + 1)
					{
						//cout << "������ �밢��  �Ʒ��� 3�� \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//�ަU �밢�� ���� 3��
				if (j>2 && i<5)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j - 2][i + 2] == -10 && Tgraph[j - 3][i + 3] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "�ަU �밢�� ���� 3�� \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j - 2][i + 2] == 10 && Tgraph[j - 3][i + 3] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "�ަU �밢�� ���� 3�� \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//���� �밢�� ���� 2�� �Ʒ��� 1��
				if (j>0 && i>1 && i<7 && j<6)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j + 1][i - 1] == -10 && Tgraph[j + 2][i - 2] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "���� �밢�� ���� 2�� �Ʒ��� 1�� \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j + 1][i - 1] == 10 && Tgraph[i + 2][j - 2] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "���� �밢�� ���� 2�� �Ʒ��� 1�� \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//���� �밢�� ���� 1�� �Ʒ��� 2��
				if (j>1 && i>0 && i<6 && j<7)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j - 2][i + 2] == -10 && Tgraph[j + 1][i - 1] == -10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "���� �밢�� ���� 1�� �Ʒ��� 2�� \n";
						ones--;
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j - 2][i + 2] == 10 && Tgraph[j + 1][i - 1] == 10 && possible_moves[j] == possible_moves[j - 1] - 1)
					{
						//cout << "���� �밢�� ���� 1�� �Ʒ��� 2�� \n";
						oppones--;
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}
				//���� �밢�� �Ʒ��� 3��
				if (j<5 && i>2)
				{
					if (Tgraph[j + 1][i - 1] == -10 && Tgraph[j + 2][i - 2] == -10 && Tgraph[j + 3][i - 3] == -10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "���� �밢�� �Ʒ��� 3�� \n";
						ones--;
						twos--;
						threes++;
					}
					if (Tgraph[j + 1][i - 1] == 10 && Tgraph[j + 2][i - 2] == 10 && Tgraph[j + 3][i - 3] == 10 && possible_moves[j] == possible_moves[j + 1] + 1)
					{
						//cout << "���� �밢�� �Ʒ��� 3�� \n";
						oppones--;
						opptwos--;
						oppthrees++;
					}
				}




			}
			// �ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�4�� �ϋ�
			if (Tgraph[j][i] == -10 || Tgraph[j][i] == 10)
			{


				if (j<5)
				{

					if (Tgraph[j + 1][i] == -10 && Tgraph[j + 2][i] == -10 && Tgraph[j + 3][i] == -10)
					{

						
						if (Tgraph[j][i] == -10)
						{
							//cout << "�����϶�, ������ 3�������� threes \n";
							fours++;
						}

					}
					if (Tgraph[j + 1][i] == 10 && Tgraph[j + 2][i] == 10 && Tgraph[j + 3][i] == 10)
					{
						
						if (Tgraph[j][i] == 10)
						{
							//cout << "�����϶�, ������ 3�������� oppthrees \n";
							oppfours++;
						}
					}
				}

				//�����϶� �ؿ� 3��
				if (i<5)
				{
					if (Tgraph[j][i + 1] == -10 && Tgraph[j][i + 2] == -10 && Tgraph[j][i + 3] == -10 && possible_moves[j] >= -1)
					{
						
						if (Tgraph[j][i] == -10)
						{
							//cout << "�����϶� �ؿ� 3�� threes \n";
							fours++;
						}
					}
					if (Tgraph[j][i + 1] == 10 && Tgraph[j][i + 2] == 10 && Tgraph[j][i + 3] == 10 && possible_moves[j] >= -1)
					{
						//cout << "�����϶� �ؿ� 3�� oppthrees \n";
						if (Tgraph[j][i] == 10)
						{
							//cout << "�����϶� �ؿ� 3�� oppthrees \n";
							oppfours++;
						}
					}
				}
				//������ �밢�� ���� 3��
				if (i<5 && j<5)
				{
					if (Tgraph[j + 1][i + 1] == -10 && Tgraph[j + 2][i + 2] == -10 && Tgraph[j + 3][i + 3] == -10)
					{
						
						if (Tgraph[j][i] == -10)
						{
							//cout << "������ �밢���ϋ� ���� 3�� \n";
							fours++;
						}
					}
					if (Tgraph[j + 1][i + 1] == 10 && Tgraph[j + 2][i + 2] == 10 && Tgraph[j + 3][i + 3] == 10)
					{
						//cout << "������ �밢���ϋ� ���� 3�� \n";
						if (Tgraph[j][i] == 10)
						{
							//cout << "������ �밢���ϋ� ����opp 3�� \n";
							oppfours++;
						}
					}
				}

				//�ަU �밢�� ���� 3��
				if (j>2 && i<5)
				{
					if (Tgraph[j - 1][i + 1] == -10 && Tgraph[j - 2][i + 2] == -10 && Tgraph[j - 3][i + 3] == -10)
					{
						
						if (Tgraph[j][i] == -10)
						{
							//cout << "���� �밢���� �� ���� 3�� \n";
							fours++;
						}
					}
					if (Tgraph[j - 1][i + 1] == 10 && Tgraph[j - 2][i + 2] == 10 && Tgraph[j - 3][i + 3] == 10)
					{
						//cout << "�ަU �밢�� ���� 3�� \n";
						if (Tgraph[j][i] == 10)
						{
							//cout << "�ަU �밢�� ����opp 3�� \n";
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
//�۵� ����
/*1. AichooseColumn
�� ������ Minmax ���� ����Ѵ�. �� �߿��� max ���� ������ ���� ã�Ƽ� return �Ѵ�. (�Ŀ� main���� �� col���� ���� �ΰ��ϸ��.)
*/
/*2. Minmax
isPlayer : true - �ڱ��ڽ�(�Ʊ�)
false- ����(����)
depth�� 0�� ������ ���� ����̹Ƿ�, "myColumn�� �δ� ��"�� ���� evaluate�� �ǽ��ؾ���.(myColumn���� �� ���� ���)
depth�� 0�� �ƴϸ�, Minmax �˰��� ���(depth�� 1 ���̰�, �÷��̾� ���´� �ٲٰ�)
���� ��Ÿ �ƿ����� ���Ŀ� �� ����!
evaluate���� ���� �а��� �� ��Ȳ���� graph ������ ���� ��ġ�� ������� ���̴�! �װ��� Ȱ���� ��.

*/