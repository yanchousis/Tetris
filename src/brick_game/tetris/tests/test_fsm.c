#include "test.h"

START_TEST(test_on_start_state_start) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->state = START;
  ptr_w_game->action = Start;
  fill_start_struct();
  on_start_state();
  ck_assert_int_eq(ptr_w_game->state, SPAWN);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_on_start_state_default) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->state = START;
  ptr_w_game->action = Down;
  on_start_state();
  ck_assert_int_eq(ptr_w_game->state, START);
  ck_assert_int_eq(ptr_w_game->game.pause, 1);
}
END_TEST

START_TEST(test_on_spawn_state) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->figure_id = 1;
  ptr_w_game->figure_id_next = 2;
  ptr_w_game->state = SPAWN;
  on_spawn_state();
  ck_assert_int_eq(ptr_w_game->state, SHIFTING);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_on_shifting_state_left) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->x = 5;
  ptr_w_game->y = 0;
  ptr_w_game->state = SHIFTING;
  ptr_w_game->action = Left;
  on_shifting_state();
  ck_assert_int_eq(ptr_w_game->state, SHIFTING);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_on_shifting_state_right) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->x = 0;
  ptr_w_game->y = 0;
  ptr_w_game->state = SHIFTING;
  ptr_w_game->action = Right;
  on_shifting_state();
  ck_assert_int_eq(ptr_w_game->state, SHIFTING);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_on_shifting_state_down) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->x = 0;
  ptr_w_game->y = 0;
  ptr_w_game->state = SHIFTING;
  ptr_w_game->action = Down;
  on_shifting_state();
  ck_assert_int_eq(ptr_w_game->state, SHIFTING);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_on_shifting_state_action) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->x = 0;
  ptr_w_game->y = 0;
  ptr_w_game->rotate = 0;
  ptr_w_game->state = SHIFTING;
  ptr_w_game->action = Action;
  on_shifting_state();
  ck_assert_int_eq(ptr_w_game->state, SHIFTING);
  ck_assert_int_eq(ptr_w_game->rotate, 1);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_on_shifting_state_default) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->x = 0;
  ptr_w_game->y = 0;
  ptr_w_game->state = SHIFTING;
  ptr_w_game->action = Up;
  on_shifting_state();
  ck_assert_int_eq(ptr_w_game->state, SHIFTING);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_on_attaching_state) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->figure_id = 1;
  ptr_w_game->figure_id_next = 2;
  ptr_w_game->state = ATTACHING;
  on_attaching_state();
  ck_assert_int_eq(ptr_w_game->figure_id, 2);
  ck_assert_int_eq(ptr_w_game->state, SPAWN);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

START_TEST(test_on_gameover_state) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.score = 1000;
  ptr_w_game->game.high_score = 500;
  ptr_w_game->state = GAMEOVER;
  on_gameover_state();
  ck_assert_ptr_null(ptr_w_game->game.field);
  ck_assert_ptr_null(ptr_w_game->ptr_figure);
  ck_assert_int_eq(ptr_w_game->game.high_score, 1000);
}
END_TEST

Suite* test_fsm(void) {
  Suite* s = suite_create("fsm");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_on_start_state_start);
  tcase_add_test(tc_core, test_on_start_state_default);
  tcase_add_test(tc_core, test_on_spawn_state);
  tcase_add_test(tc_core, test_on_shifting_state_left);
  tcase_add_test(tc_core, test_on_shifting_state_right);
  tcase_add_test(tc_core, test_on_shifting_state_down);
  tcase_add_test(tc_core, test_on_shifting_state_action);
  tcase_add_test(tc_core, test_on_shifting_state_default);
  tcase_add_test(tc_core, test_on_attaching_state);
  tcase_add_test(tc_core, test_on_gameover_state);

  suite_add_tcase(s, tc_core);

  return s;
}
