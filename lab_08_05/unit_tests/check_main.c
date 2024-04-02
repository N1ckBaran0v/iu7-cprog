#include <check.h>

#include "../inc/check_my_matrix.h"
#include "../inc/check_my_multiple.h"
#include "../inc/check_my_resize.h"
#include "../inc/my_errors.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = create_matrix_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (no_failed == 0)
    {
        s = mult_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);
        no_failed = srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    if (no_failed == 0)
    {
        s = resize_matrix_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);
        no_failed = srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    if (no_failed == 0)
    {
        s = to_square_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);
        no_failed = srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    if (no_failed == 0)
    {
        s = increase_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);
        no_failed = srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    return (no_failed == 0) ? ERR_OK : ERR_UNIT_TESTS;
}