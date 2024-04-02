#include <check.h>

#include "../inc/check_my_filter.h"
#include "../inc/check_my_io.h"
#include "../inc/check_my_sort.h"
#include "../inc/my_errors.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = input_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (no_failed == 0)
    {
        s = output_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);
        no_failed = srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    if (no_failed == 0)
    {
        s = filter_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);
        no_failed = srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    if (no_failed == 0)
    {
        s = sort_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);
        no_failed = srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    if (no_failed == 0)
    {
        s = comparator_suite();
        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);
        no_failed = srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    return (no_failed == 0) ? ERR_OK : ERR_OTHER;
}