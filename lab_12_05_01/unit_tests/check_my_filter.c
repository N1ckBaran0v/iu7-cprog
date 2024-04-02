#include <stdlib.h>
#include <dlfcn.h>

#include "check_my_filter.h"
#include "my_errors.h"

#ifdef DYN_LOAD

typedef int (*key_f)(const int *, const int *, int **, int **);
extern key_f key;

#else

#include "my_filter.h"

#endif

START_TEST(one_number)
{
    int a[] = {1}, buf[1];
    int *b = buf, *c = 0;
    int rc = key(a, a + 1, &b, &c);
    ck_assert_int_ne(rc, ERR_OK);
}
END_TEST

START_TEST(no_match)
{
    int a[] = {1, 2, 3, 4}, buf[4];
    int *b = buf, *c = 0;
    int rc = key(a, a + 4, &b, &c);
    ck_assert_int_ne(rc, ERR_OK);
}
END_TEST

START_TEST(one_number_pos)
{
    int a[] = {2, 1}, buf[2];
    int *b = buf, *c = 0;
    int d[] = {2};
    int rc = key(a, a + 2, &b, &c);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq((int)(c - b), 1);
    for (size_t i = 0; i < (size_t)(c - b); ++i)
        ck_assert_int_eq(b[i], d[i]);
}
END_TEST

START_TEST(few_match)
{
    int a[] = {8, 4, 2, 1}, buf[4];
    int *b = buf, *c = 0;
    int d[] = {8, 4, 2};
    int rc = key(a, a + 4, (int**)&b, &c);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq((int)(c - b), 3);
    for (size_t i = 0; i < (size_t)(c - b); ++i)
        ck_assert_int_eq(b[i], d[i]);
}
END_TEST


Suite* filter_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;
    s = suite_create("filter");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, one_number_pos);
    tcase_add_test(tc_pos, few_match);
    suite_add_tcase(s, tc_pos);
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, one_number);
    tcase_add_test(tc_neg, no_match);
    suite_add_tcase(s, tc_neg);
    return s;
}