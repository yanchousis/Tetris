#include "test.h"

START_TEST(test_choice_figure) {
  int** figure = create_array_2d(F_SIZE, F_SIZE);
  choice_figure(FIGURE_T, 0, figure);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[2][0], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);

  choice_figure(FIGURE_I, 0, figure);
  ck_assert_int_eq(figure[1][0], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[1][3], 1);

  choice_figure(FIGURE_S, 0, figure);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);

  choice_figure(FIGURE_LZ, 0, figure);
  ck_assert_int_eq(figure[1][0], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);

  choice_figure(FIGURE_RZ, 0, figure);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][0], 1);
  ck_assert_int_eq(figure[2][1], 1);

  choice_figure(FIGURE_LG, 0, figure);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][0], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);

  choice_figure(FIGURE_RG, 0, figure);
  ck_assert_int_eq(figure[1][0], 1);
  ck_assert_int_eq(figure[2][0], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);

  destroy_array_2d(&figure);
}
END_TEST

START_TEST(test_choice_figure_null) { choice_figure(FIGURE_T, 0, NULL); }
END_TEST

START_TEST(test_choice_figure_default) {
  int** figure = create_array_2d(F_SIZE, F_SIZE);
  choice_figure(100, 0, figure);
  for (int i = 0; i < F_SIZE; ++i) {
    for (int j = 0; j < F_SIZE; ++j) {
      ck_assert_int_eq(figure[i][j], 0);
    }
  }
  destroy_array_2d(&figure);
}
END_TEST

START_TEST(test_create_rotate_figure_t) {
  int** figure = create_array_2d(F_SIZE, F_SIZE);
  create_rotate_figure_t(figure, 0);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[2][0], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_t(figure, 1);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[1][0], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[2][1], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_t(figure, 2);
  ck_assert_int_eq(figure[1][0], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][1], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_t(figure, 3);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][1], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_t(figure, 4);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[2][0], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_t(figure, -1);

  destroy_array_2d(&figure);
}
END_TEST

START_TEST(test_create_rotate_figure_t_null) {
  create_rotate_figure_t(NULL, 0);
}
END_TEST

START_TEST(test_create_rotate_figure_i) {
  int** figure = create_array_2d(F_SIZE, F_SIZE);
  create_rotate_figure_i(figure, 0);
  ck_assert_int_eq(figure[1][0], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[1][3], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_i(figure, 1);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[3][1], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_i(figure, 2);
  ck_assert_int_eq(figure[1][0], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[1][3], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_i(figure, -1);

  destroy_array_2d(&figure);
}
END_TEST

START_TEST(test_create_rotate_figure_i_null) {
  create_rotate_figure_i(NULL, 0);
}
END_TEST

START_TEST(test_create_rotate_figure_s) {
  int** figure = create_array_2d(F_SIZE, F_SIZE);
  create_rotate_figure_s(figure);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);
  destroy_array_2d(&figure);
}
END_TEST

START_TEST(test_create_rotate_figure_s_null) { create_rotate_figure_s(NULL); }
END_TEST

START_TEST(test_create_rotate_figure_lz) {
  int** figure = create_array_2d(F_SIZE, F_SIZE);
  create_rotate_figure_lz(figure, 0);
  ck_assert_int_eq(figure[1][0], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_lz(figure, 1);
  ck_assert_int_eq(figure[0][2], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][1], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_lz(figure, -1);

  destroy_array_2d(&figure);
}
END_TEST

START_TEST(test_create_rotate_figure_lz_null) {
  create_rotate_figure_lz(NULL, 0);
}
END_TEST

START_TEST(test_create_rotate_figure_rz) {
  int** figure = create_array_2d(F_SIZE, F_SIZE);
  create_rotate_figure_rz(figure, 0);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][0], 1);
  ck_assert_int_eq(figure[2][1], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_rz(figure, 1);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][2], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_rz(figure, -1);

  destroy_array_2d(&figure);
}
END_TEST

START_TEST(test_create_rotate_figure_rz_null) {
  create_rotate_figure_rz(NULL, 0);
}
END_TEST

START_TEST(test_create_rotate_figure_lg) {
  int** figure = create_array_2d(F_SIZE, F_SIZE);
  create_rotate_figure_lg(figure, 0);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][0], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_lg(figure, 1);
  ck_assert_int_eq(figure[0][0], 1);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[2][1], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_lg(figure, 2);
  ck_assert_int_eq(figure[1][0], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][0], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_lg(figure, 3);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_lg(figure, -1);

  destroy_array_2d(&figure);
}
END_TEST

START_TEST(test_create_rotate_figure_lg_null) {
  create_rotate_figure_lg(NULL, 0);
}
END_TEST

START_TEST(test_create_rotate_figure_rg) {
  int** figure = create_array_2d(F_SIZE, F_SIZE);
  create_rotate_figure_rg(figure, 0);
  ck_assert_int_eq(figure[1][0], 1);
  ck_assert_int_eq(figure[2][0], 1);
  ck_assert_int_eq(figure[2][1], 1);
  ck_assert_int_eq(figure[2][2], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_rg(figure, 1);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[2][0], 1);
  ck_assert_int_eq(figure[2][1], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_rg(figure, 2);
  ck_assert_int_eq(figure[1][0], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[1][2], 1);
  ck_assert_int_eq(figure[2][2], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_rg(figure, 3);
  ck_assert_int_eq(figure[0][1], 1);
  ck_assert_int_eq(figure[0][2], 1);
  ck_assert_int_eq(figure[1][1], 1);
  ck_assert_int_eq(figure[2][1], 1);

  fill_empty(figure, F_SIZE, F_SIZE);
  create_rotate_figure_rg(figure, -1);

  destroy_array_2d(&figure);
}
END_TEST

START_TEST(test_create_rotate_figure_rg_null) {
  create_rotate_figure_rg(NULL, 0);
}
END_TEST

START_TEST(test_create_figure_matrix) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->figure_id = 1;
  ptr_w_game->rotate = 0;
  create_figure_matrix();
  ck_assert_int_gt(ptr_w_game->figure_id_next, 0);
  ck_assert_int_le(ptr_w_game->figure_id_next, 7);
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
}
END_TEST

Suite* test_figures(void) {
  Suite* s = suite_create("figures");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_choice_figure);
  tcase_add_test(tc_core, test_choice_figure_null);
  tcase_add_test(tc_core, test_choice_figure_default);
  tcase_add_test(tc_core, test_create_rotate_figure_t);
  tcase_add_test(tc_core, test_create_rotate_figure_t_null);
  tcase_add_test(tc_core, test_create_rotate_figure_i);
  tcase_add_test(tc_core, test_create_rotate_figure_i_null);
  tcase_add_test(tc_core, test_create_rotate_figure_s);
  tcase_add_test(tc_core, test_create_rotate_figure_s_null);
  tcase_add_test(tc_core, test_create_rotate_figure_lz);
  tcase_add_test(tc_core, test_create_rotate_figure_lz_null);
  tcase_add_test(tc_core, test_create_rotate_figure_rz);
  tcase_add_test(tc_core, test_create_rotate_figure_rz_null);
  tcase_add_test(tc_core, test_create_rotate_figure_lg);
  tcase_add_test(tc_core, test_create_rotate_figure_lg_null);
  tcase_add_test(tc_core, test_create_rotate_figure_rg);
  tcase_add_test(tc_core, test_create_rotate_figure_rg_null);
  tcase_add_test(tc_core, test_create_figure_matrix);

  suite_add_tcase(s, tc_core);

  return s;
}
