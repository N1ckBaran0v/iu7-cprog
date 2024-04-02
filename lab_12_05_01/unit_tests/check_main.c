#include <check.h>
#include <dlfcn.h>

#include "check_my_filter.h"
#include "check_my_io.h"
#include "check_my_sort.h"

#include "my_errors.h"

#ifdef DYN_LOAD

typedef int (*compar_f)(const void *, const void *);
typedef void (*sort_f)(void *, size_t, size_t, compar_f);
typedef int (*key_f)(const int *, const int *, int **, int **);
typedef int (*read_f)(const char *, int **, int **);
typedef int (*write_f)(const char *, const int *, const int *);
compar_f intcmp;
sort_f mysort;
key_f key;
read_f read;
write_f write;

int main(void)
{
    int rc = ERR_OK;
    void *lib = dlopen("out/libsort.so", RTLD_NOW);

    if (lib)
    {
        intcmp = dlsym(lib, "intcmp");
        mysort = dlsym(lib, "mysort");
        key = dlsym(lib, "key");
        read = dlsym(lib, "read");
        write = dlsym(lib, "write");
        if (intcmp && mysort && key && read && write)
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

            rc = (no_failed == 0) ? ERR_OK : ERR_OTHER;
        }
        else
            rc = ERR_LOAD_LIB;
    }
    else
        rc = ERR_LOAD_LIB;
    return rc;
}

#else

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

#endif