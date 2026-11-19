#ifndef TEST_H__
#define TEST_H__

#include <check.h>

#include "../../../api/api.h"
#include "../inc/backend.h"

Suite* test_backend(void);
Suite* test_fsm(void);
Suite* test_figures(void);

#endif
