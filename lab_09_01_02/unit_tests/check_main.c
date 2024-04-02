#include <check.h>

#include "check_my_find.h"
#include "check_my_io.h"
#include "my_errors.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = read_struct_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (no_failed == 0)
    {
        s = find_suite();
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

    return (no_failed == 0) ? ERR_OK : ERR_UNIT_TESTS;
}