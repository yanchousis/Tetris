#include "figures.h"

void create_figure_matrix() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();

  choice_figure(ptr_w_game->figure_id, ptr_w_game->rotate,
                ptr_w_game->ptr_figure);

  ptr_w_game->figure_id_next = 1 + rand() % 7;
}

void choice_figure(int figure_id, const int rotate, int** figure) {
  if (!figure) return;
  fill_empty(figure, F_SIZE, F_SIZE);

  switch (figure_id) {
    case FIGURE_T:
      create_rotate_figure_t(figure, rotate);
      break;
    case FIGURE_I:
      create_rotate_figure_i(figure, rotate);
      break;
    case FIGURE_S:
      create_rotate_figure_s(figure);
      break;
    case FIGURE_LZ:
      create_rotate_figure_lz(figure, rotate);
      break;
    case FIGURE_RZ:
      create_rotate_figure_rz(figure, rotate);
      break;
    case FIGURE_LG:
      create_rotate_figure_lg(figure, rotate);
      break;
    case FIGURE_RG:
      create_rotate_figure_rg(figure, rotate);
      break;
    default:
      break;
  }
}

void create_rotate_figure_t(int** figure, const int rotate) {
  if (!figure) return;

  switch (rotate % 4) {
    case 0:
      figure[1][1] = 1;
      figure[2][0] = 1;
      figure[2][1] = 1;
      figure[2][2] = 1;
      break;
    case 1:
      figure[0][1] = 1;
      figure[1][0] = 1;
      figure[1][1] = 1;
      figure[2][1] = 1;
      break;
    case 2:
      figure[1][0] = 1;
      figure[1][1] = 1;
      figure[1][2] = 1;
      figure[2][1] = 1;
      break;
    case 3:
      figure[0][1] = 1;
      figure[1][2] = 1;
      figure[1][1] = 1;
      figure[2][1] = 1;
      break;
    default:
      break;
  }
}

void create_rotate_figure_i(int** figure, const int rotate) {
  if (!figure) return;

  switch (rotate % 2) {
    case 0:
      figure[1][0] = 1;
      figure[1][1] = 1;
      figure[1][2] = 1;
      figure[1][3] = 1;
      break;
    case 1:
      figure[0][1] = 1;
      figure[1][1] = 1;
      figure[2][1] = 1;
      figure[3][1] = 1;
      break;
    default:
      break;
  }
}

void create_rotate_figure_s(int** figure) {
  if (!figure) return;

  figure[1][1] = 1;
  figure[1][2] = 1;
  figure[2][1] = 1;
  figure[2][2] = 1;
}

void create_rotate_figure_lz(int** figure, const int rotate) {
  if (!figure) return;

  switch (rotate % 2) {
    case 0:
      figure[1][0] = 1;
      figure[1][1] = 1;
      figure[2][1] = 1;
      figure[2][2] = 1;
      break;
    case 1:
      figure[0][2] = 1;
      figure[1][2] = 1;
      figure[1][1] = 1;
      figure[2][1] = 1;
      break;
    default:
      break;
  }
}

void create_rotate_figure_rz(int** figure, const int rotate) {
  if (!figure) return;

  switch (rotate % 2) {
    case 0:
      figure[1][1] = 1;
      figure[1][2] = 1;
      figure[2][0] = 1;
      figure[2][1] = 1;
      break;
    case 1:
      figure[0][1] = 1;
      figure[1][1] = 1;
      figure[1][2] = 1;
      figure[2][2] = 1;
      break;
    default:
      break;
  }
}

void create_rotate_figure_lg(int** figure, const int rotate) {
  if (!figure) return;

  switch (rotate % 4) {
    case 0:
      figure[1][2] = 1;
      figure[2][0] = 1;
      figure[2][1] = 1;
      figure[2][2] = 1;
      break;
    case 1:
      figure[0][0] = 1;
      figure[0][1] = 1;
      figure[1][1] = 1;
      figure[2][1] = 1;
      break;
    case 2:
      figure[1][0] = 1;
      figure[1][1] = 1;
      figure[1][2] = 1;
      figure[2][0] = 1;
      break;
    case 3:
      figure[0][1] = 1;
      figure[1][1] = 1;
      figure[2][1] = 1;
      figure[2][2] = 1;
      break;
    default:
      break;
  }
}

void create_rotate_figure_rg(int** figure, const int rotate) {
  if (!figure) return;

  switch (rotate % 4) {
    case 0:
      figure[1][0] = 1;
      figure[2][0] = 1;
      figure[2][1] = 1;
      figure[2][2] = 1;
      break;
    case 1:
      figure[0][1] = 1;
      figure[1][1] = 1;
      figure[2][0] = 1;
      figure[2][1] = 1;
      break;
    case 2:
      figure[1][0] = 1;
      figure[1][1] = 1;
      figure[1][2] = 1;
      figure[2][2] = 1;
      break;
    case 3:
      figure[0][1] = 1;
      figure[0][2] = 1;
      figure[1][1] = 1;
      figure[2][1] = 1;
      break;
    default:
      break;
  }
}