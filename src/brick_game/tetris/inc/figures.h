#ifndef FIGURES_H__
#define FIGURES_H__

#include "objects.h"

void create_figure_matrix();
void choice_figure(int figure_id, const int rotate, int** figure);
void fill_empty(int**, const int, const int);

void create_rotate_figure_t(int** figure, const int rotate);
void create_rotate_figure_i(int** figure, const int rotate);
void create_rotate_figure_s(int** figure);
void create_rotate_figure_lz(int** figure, const int rotate);
void create_rotate_figure_rz(int** figure, const int rotate);
void create_rotate_figure_lg(int** figure, const int rotate);
void create_rotate_figure_rg(int** figure, const int rotate);

#endif