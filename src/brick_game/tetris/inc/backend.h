#ifndef BACKEND_H__
#define BACKEND_H__

#include "../../../api/api.h"
#include "figures.h"
#include "fsm.h"
#include "objects.h"

#ifdef MAIN_TETRIS
#define FILENAME "brick_game/tetris/score/tetris_high_score.txt"
#else
#define FILENAME "score/tetris_high_score.txt"
#endif

#define SPAWN_X 3
#define SPAWN_Y -1

int** create_array_2d(const int, const int);
void fill_empty(int**, const int, const int);

void spawn_figure();
void fill_field_fig();
void clear_figure();
void move_down_all_field(int start);

void check_down();
int check_down_border(int i);
int check_down_fig(int i, int j);
int check_up_border(int i);
void check_left();
int check_left_border(int j);
int check_left_fig(int i, int j);
void check_right();
int check_right_border(int j);
int check_right_fig(int i, int j);
void check_rotate();
void check_line();
void check_speed();
void check_score();
void check_gameover();

void fill_start_struct();
void fill_spawn_struct();

int get_high_score();

#endif