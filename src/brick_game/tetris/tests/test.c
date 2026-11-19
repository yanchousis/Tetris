#include "test.h"

int main() {
  int failed = 0;
  Suite* tetris_test[] = {test_backend(), test_fsm(), test_figures(), NULL};

  for (int i = 0; tetris_test[i] != NULL; ++i) {
    SRunner* sr = srunner_create(tetris_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
