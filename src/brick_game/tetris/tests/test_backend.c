#include "test.h"

START_TEST(test_create_array_2d) {
  int** arr = create_array_2d(10, 10);
  ck_assert_ptr_nonnull(arr);
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      ck_assert_int_eq(arr[i][j], 0);
    }
  }
  destroy_array_2d(&arr);
  ck_assert_ptr_null(arr);
}
END_TEST

START_TEST(test_create_array_2d_null) {
  int** arr = create_array_2d(0, 0);
  ck_assert_ptr_nonnull(arr);
  destroy_array_2d(&arr);
}
END_TEST

START_TEST(test_fill_empty) {
  int** arr = create_array_2d(5, 5);
  arr[0][0] = 1;
  arr[2][2] = 1;
  fill_empty(arr, 5, 5);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      ck_assert_int_eq(arr[i][j], 0);
    }
  }
  destroy_array_2d(&arr);
}
END_TEST

START_TEST(test_fill_empty_null) { fill_empty(NULL, 5, 5); }
END_TEST

START_TEST(test_static_wide_game_info) {
  WideGameInfo_t* ptr1 = static_wide_game_info();
  WideGameInfo_t* ptr2 = static_wide_game_info();
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_int_eq(ptr1->state, START);
}
END_TEST

START_TEST(test_get_high_score) {
  int score = get_high_score();
  ck_assert_int_ge(score, 0);
}
END_TEST

START_TEST(test_spawn_figure) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->figure_id = 1;
  ptr_w_game->rotate = 0;
  spawn_figure();
  ck_assert_int_gt(ptr_w_game->figure_id_next, 0);
  ck_assert_int_le(ptr_w_game->figure_id_next, 7);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_fill_spawn_struct) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->x = 10;
  ptr_w_game->y = 10;
  ptr_w_game->rotate = 5;
  fill_spawn_struct();
  ck_assert_int_eq(ptr_w_game->x, 3);
  ck_assert_int_eq(ptr_w_game->y, -1);
  ck_assert_int_eq(ptr_w_game->rotate, 0);
}
END_TEST

START_TEST(test_fill_start_struct) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = NULL;
  ptr_w_game->ptr_figure = NULL;
  fill_start_struct();
  ck_assert_ptr_nonnull(ptr_w_game->game.field);
  ck_assert_ptr_nonnull(ptr_w_game->ptr_figure);
  ck_assert_int_eq(ptr_w_game->game.pause, 0);
  ck_assert_int_eq(ptr_w_game->game.score, 0);
  ck_assert_int_eq(ptr_w_game->game.speed, 300);
  ck_assert_int_eq(ptr_w_game->game.level, 1);
  ck_assert_int_gt(ptr_w_game->figure_id, 0);
  ck_assert_int_le(ptr_w_game->figure_id, 7);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_down_border) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->y = HIGH_POLE - 4;
  int result = check_down_border(3);
  ck_assert_int_eq(result, 1);
  ptr_w_game->y = 0;
  result = check_down_border(0);
  ck_assert_int_eq(result, 0);

  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->y = 17;
  choice_figure(FIGURE_S, 0, ptr_w_game->ptr_figure);
  check_down();

  destroy_array_2d(&ptr_w_game->ptr_figure);
  destroy_array_2d(&ptr_w_game->game.field);
}
END_TEST

START_TEST(test_check_down_border_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  int result = check_down_border(0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_check_down_fig) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->y = 10;
  ptr_w_game->x = 0;
  ptr_w_game->game.field[15][0] = 1;
  int result = check_down_fig(4, 0);
  ck_assert_int_eq(result, 1);
  ptr_w_game->game.field[15][0] = 0;
  result = check_down_fig(4, 0);
  ck_assert_int_eq(result, 0);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_down_fig_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  int result = check_down_fig(0, 0);
  ck_assert_int_eq(result, 0);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.field = NULL;
  result = check_down_fig(0, 0);
  ck_assert_int_eq(result, 0);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_left_border) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->x = 0;
  int result = check_left_border(0);
  ck_assert_int_eq(result, 1);
  ptr_w_game->x = 5;
  result = check_left_border(0);
  ck_assert_int_eq(result, 0);

  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->x = -1;
  choice_figure(FIGURE_S, 0, ptr_w_game->ptr_figure);
  check_left(1);

  destroy_array_2d(&ptr_w_game->ptr_figure);
  destroy_array_2d(&ptr_w_game->game.field);
}
END_TEST

START_TEST(test_check_left_border_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  int result = check_left_border(0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_check_left_fig) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->y = 10;
  ptr_w_game->x = 5;
  ptr_w_game->game.field[10][4] = 1;
  int result = check_left_fig(0, 0);
  ck_assert_int_eq(result, 1);
  ptr_w_game->game.field[10][4] = 0;
  result = check_left_fig(0, 0);
  ck_assert_int_eq(result, 0);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_left_fig_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  int result = check_left_fig(0, 0);
  ck_assert_int_eq(result, 0);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.field = NULL;
  result = check_left_fig(0, 0);
  ck_assert_int_eq(result, 0);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_right_border) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->x = WIDTH_POLE - 4;
  int result = check_right_border(3);
  ck_assert_int_eq(result, 1);
  ptr_w_game->x = 0;
  result = check_right_border(0);
  ck_assert_int_eq(result, 0);

  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->x = 7;
  choice_figure(FIGURE_S, 0, ptr_w_game->ptr_figure);
  check_right(2);

  destroy_array_2d(&ptr_w_game->ptr_figure);
  destroy_array_2d(&ptr_w_game->game.field);
}
END_TEST

START_TEST(test_check_right_border_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  int result = check_right_border(0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_check_right_fig) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->y = 10;
  ptr_w_game->x = 5;
  ptr_w_game->game.field[10][7] = 1;
  int result = check_right_fig(0, 1);
  ck_assert_int_eq(result, 1);
  ptr_w_game->game.field[10][7] = 0;
  result = check_right_fig(0, 1);
  ck_assert_int_eq(result, 0);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_right_fig_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  int result = check_right_fig(0, 0);
  ck_assert_int_eq(result, 0);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.field = NULL;
  result = check_right_fig(0, 0);
  ck_assert_int_eq(result, 0);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_up_border) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->y = -1;
  int result = check_up_border(0);
  ck_assert_int_eq(result, 1);
  ptr_w_game->y = 0;
  result = check_up_border(0);
  ck_assert_int_eq(result, 0);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_up_border_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  int result = check_up_border(0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_check_down) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->ptr_figure[3][0] = 1;
  ptr_w_game->y = 0;
  int old_y = ptr_w_game->y;
  check_down();
  ck_assert_int_eq(ptr_w_game->y, old_y + 1);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_down_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  check_down();
}
END_TEST

START_TEST(test_check_left) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->x = 5;
  ptr_w_game->y = 0;
  int old_x = ptr_w_game->x;
  check_left();
  ck_assert_int_eq(ptr_w_game->x, old_x - 1);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_left_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  check_left();
}
END_TEST

START_TEST(test_check_right) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->x = 0;
  ptr_w_game->y = 0;
  int old_x = ptr_w_game->x;
  check_right();
  ck_assert_int_eq(ptr_w_game->x, old_x + 1);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_right_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  check_right();
}
END_TEST

START_TEST(test_check_rotate) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->figure_id = FIGURE_T;
  ptr_w_game->x = 3;
  ptr_w_game->y = 10;
  ptr_w_game->rotate = 0;
  choice_figure(ptr_w_game->figure_id, ptr_w_game->rotate,
                ptr_w_game->ptr_figure);
  check_rotate();
  ck_assert_int_eq(ptr_w_game->rotate, 0);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_rotate_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  check_rotate();
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.field = NULL;
  check_rotate();
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_rotate_boundary) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->x = -1;
  ptr_w_game->y = 0;
  ptr_w_game->rotate = 0;
  check_rotate();
  ck_assert_int_ge(ptr_w_game->x, -1);
  ptr_w_game->x = WIDTH_POLE;
  ptr_w_game->y = 0;
  ptr_w_game->rotate = 0;
  check_rotate();
  ck_assert_int_le(ptr_w_game->x, WIDTH_POLE);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_gameover) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  fill_start_struct();
  fill_spawn_struct();
  ptr_w_game->figure_id = FIGURE_T;
  choice_figure(ptr_w_game->figure_id, ptr_w_game->rotate,
                ptr_w_game->ptr_figure);
  ptr_w_game->game.field[1][3] = 1;
  ptr_w_game->game.field[1][4] = 1;
  ptr_w_game->game.field[1][5] = 1;
  check_gameover();
  ck_assert_int_eq(ptr_w_game->state, GAMEOVER);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_gameover_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  check_gameover();
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.field = NULL;
  check_gameover();
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_move_down_all_field) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  for (int j = 0; j < WIDTH_POLE; ++j) {
    ptr_w_game->game.field[0][j] = 1;
  }
  move_down_all_field(5);
  for (int j = 0; j < WIDTH_POLE; ++j) {
    ck_assert_int_eq(ptr_w_game->game.field[1][j], 1);
    ck_assert_int_eq(ptr_w_game->game.field[0][j], 0);
  }
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_move_down_all_field_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  move_down_all_field(5);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.field = NULL;
  move_down_all_field(5);
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  move_down_all_field(0);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_line) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.score = 0;
  for (int j = 0; j < WIDTH_POLE; ++j) {
    ptr_w_game->game.field[HIGH_POLE - 1][j] = 1;
  }
  int old_score = ptr_w_game->game.score;
  check_line();
  ck_assert_int_gt(ptr_w_game->game.score, old_score);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_line_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  check_line();
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.field = NULL;
  check_line();
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_line_multiple) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.score = 0;
  for (int j = 0; j < WIDTH_POLE; ++j) {
    ptr_w_game->game.field[HIGH_POLE - 1][j] = 1;
    ptr_w_game->game.field[HIGH_POLE - 2][j] = 1;
  }
  check_line();
  ck_assert_int_eq(ptr_w_game->game.score, 300);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_speed) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  fill_start_struct();
  ptr_w_game->game.score = 0;
  check_speed();
  ck_assert_int_eq(ptr_w_game->game.level, 1);
  ck_assert_int_eq(ptr_w_game->game.speed, 320);

  ptr_w_game->game.score = 600;
  check_speed();
  ck_assert_int_eq(ptr_w_game->game.level, 2);
  ck_assert_int_eq(ptr_w_game->game.speed, 300);

  ptr_w_game->game.score = 5400;
  check_speed();
  ck_assert_int_eq(ptr_w_game->game.level, 10);
  ck_assert_int_eq(ptr_w_game->game.speed, 160);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_check_score) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.score = 1000;
  ptr_w_game->game.high_score = 500;
  check_score();
  ck_assert_int_eq(ptr_w_game->game.high_score, 1000);
}
END_TEST

START_TEST(test_update_current_state) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  fill_start_struct();
  ptr_w_game->figure_id_next = 1;
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.pause, 0);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_clear_figure) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->ptr_figure[0][0] = 1;
  ptr_w_game->x = 0;
  ptr_w_game->y = 0;
  ptr_w_game->game.field[0][0] = 1;
  clear_figure();
  ck_assert_int_eq(ptr_w_game->game.field[0][0], 0);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_clear_figure_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  clear_figure();
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.field = NULL;
  clear_figure();
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_fill_field_fig) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->ptr_figure[0][0] = 1;
  ptr_w_game->x = 0;
  ptr_w_game->y = 0;
  fill_field_fig();
  ck_assert_int_eq(ptr_w_game->game.field[0][0], 1);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_fill_field_fig_null) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = NULL;
  fill_field_fig();
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.field = NULL;
  fill_field_fig();
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_input) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->action = Start;
  ptr_w_game->state = START;
  userInput(ptr_w_game->action, 0);
  ptr_w_game->action = Pause;
  userInput(ptr_w_game->action, 0);
  ptr_w_game->action = Start;
  userInput(ptr_w_game->action, 0);
  ptr_w_game->state = GAMEOVER;
  userInput(ptr_w_game->action, 0);
  ptr_w_game->state = SPAWN;
  userInput(ptr_w_game->action, 0);
  ptr_w_game->state = ATTACHING;
  userInput(ptr_w_game->action, 0);
  ptr_w_game->state = GAMEOVER;
  ptr_w_game->action = Down;
  userInput(ptr_w_game->action, 0);
}
END_TEST

START_TEST(test_rotate_collide) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  choice_figure(FIGURE_I, 0, ptr_w_game->ptr_figure);

  ptr_w_game->x = -1;
  check_rotate();
  ptr_w_game->x = 7;
  check_rotate();
  ptr_w_game->y = -2;
  check_rotate();
  ptr_w_game->y = 20;
  check_rotate();

  destroy_array_2d(&ptr_w_game->ptr_figure);
  destroy_array_2d(&ptr_w_game->game.field);
}
END_TEST

Suite* test_backend(void) {
  Suite* s = suite_create("backend");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_create_array_2d);
  tcase_add_test(tc_core, test_create_array_2d_null);
  tcase_add_test(tc_core, test_fill_empty);
  tcase_add_test(tc_core, test_fill_empty_null);
  tcase_add_test(tc_core, test_static_wide_game_info);
  tcase_add_test(tc_core, test_get_high_score);
  tcase_add_test(tc_core, test_spawn_figure);
  tcase_add_test(tc_core, test_fill_spawn_struct);
  tcase_add_test(tc_core, test_fill_start_struct);
  tcase_add_test(tc_core, test_check_down_border);
  tcase_add_test(tc_core, test_check_down_border_null);
  tcase_add_test(tc_core, test_check_down_fig);
  tcase_add_test(tc_core, test_check_down_fig_null);
  tcase_add_test(tc_core, test_check_left_border);
  tcase_add_test(tc_core, test_check_left_border_null);
  tcase_add_test(tc_core, test_check_left_fig);
  tcase_add_test(tc_core, test_check_left_fig_null);
  tcase_add_test(tc_core, test_check_right_border);
  tcase_add_test(tc_core, test_check_right_border_null);
  tcase_add_test(tc_core, test_check_right_fig);
  tcase_add_test(tc_core, test_check_right_fig_null);
  tcase_add_test(tc_core, test_check_up_border);
  tcase_add_test(tc_core, test_check_up_border_null);
  tcase_add_test(tc_core, test_check_down);
  tcase_add_test(tc_core, test_check_down_null);
  tcase_add_test(tc_core, test_check_left);
  tcase_add_test(tc_core, test_check_left_null);
  tcase_add_test(tc_core, test_check_right);
  tcase_add_test(tc_core, test_check_right_null);
  tcase_add_test(tc_core, test_check_rotate);
  tcase_add_test(tc_core, test_check_rotate_null);
  tcase_add_test(tc_core, test_check_rotate_boundary);
  tcase_add_test(tc_core, test_check_gameover);
  tcase_add_test(tc_core, test_check_gameover_null);
  tcase_add_test(tc_core, test_move_down_all_field);
  tcase_add_test(tc_core, test_move_down_all_field_null);
  tcase_add_test(tc_core, test_check_line);
  tcase_add_test(tc_core, test_check_line_null);
  tcase_add_test(tc_core, test_check_line_multiple);
  tcase_add_test(tc_core, test_check_speed);
  tcase_add_test(tc_core, test_check_score);
  tcase_add_test(tc_core, test_update_current_state);
  tcase_add_test(tc_core, test_clear_figure);
  tcase_add_test(tc_core, test_clear_figure_null);
  tcase_add_test(tc_core, test_fill_field_fig);
  tcase_add_test(tc_core, test_fill_field_fig_null);
  tcase_add_test(tc_core, test_input);
  tcase_add_test(tc_core, test_rotate_collide);

  suite_add_tcase(s, tc_core);

  return s;
}
