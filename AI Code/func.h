#pragma once

#ifndef func_H
#define func_H
#define MAP_SIZE 8
#define CHARTOINT 97
#define BW 76.5
int possible_n(int graph[MAP_SIZE][MAP_SIZE], int possible_moves[MAP_SIZE]);
int win(int graph[MAP_SIZE][MAP_SIZE], int possible_moves[MAP_SIZE], int win_place[MAP_SIZE]);
int score_t(int graph[MAP_SIZE][MAP_SIZE], int possible_moves[MAP_SIZE], int result[MAP_SIZE]);
int Minmax(int depth, int graph[MAP_SIZE][MAP_SIZE], bool isPlayer, int myColumn, int possible_moves[MAP_SIZE], int alpha, int beta, int flag);
int AichooseColumn(int graph[MAP_SIZE][MAP_SIZE], bool isPlayer, int possible_moves[MAP_SIZE], int flag);

//int max_score(int *score);
int evaluate2(int graph[8][8], int possible_moves[8]);
int evaluate(int graph[8][8], int possible_move[8], int *col, bool isplayer, int flag);
#endif