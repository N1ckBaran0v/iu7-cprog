#include <dlfcn.h>

#include "check_my_sort.h"

#ifdef DYN_LOAD

typedef int (*compar_f)(const void *, const void *);
typedef void (*sort_f)(void *, size_t, size_t, compar_f);
extern compar_f intcmp;
extern sort_f mysort;

#else

#include "my_sort.h"

#endif

START_TEST(bigger)
{
    int a = 4;
    int b = 3;
    int ans = intcmp(&a, &b);
    ck_assert_int_eq(ans, 1);
}
END_TEST

START_TEST(equal)
{
    int a = 4;
    int b = 4;
    int ans = intcmp(&a, &b);
    ck_assert_int_eq(ans, 0);
}
END_TEST

START_TEST(less)
{
    int a = 3;
    int b = 4;
    int ans = intcmp(&a, &b);
    ck_assert_int_eq(ans, -1);
}
END_TEST

START_TEST(sort_one_elem)
{
    int a[] = {1};
    int b[] = {1};
    mysort(a, 1, sizeof(int), intcmp);
    ck_assert_int_eq(a[0], b[0]);
}
END_TEST

START_TEST(sort_sorted)
{
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3};
    mysort(a, 3, sizeof(int), intcmp);
    for (size_t i = 0; i < 3; ++i)
        ck_assert_int_eq(a[i], b[i]);
}
END_TEST

START_TEST(sort_reversed)
{
    int a[] = {3, 2, 1};
    int b[] = {1, 2, 3};
    mysort(a, 3, sizeof(int), intcmp);
    for (size_t i = 0; i < 3; ++i)
        ck_assert_int_eq(a[i], b[i]);
}
END_TEST

START_TEST(sort_random)
{
    int a[] = {3, 1, 5, 2, 4};
    int b[] = {1, 2, 3, 4, 5};
    mysort(a, 5, sizeof(int), intcmp);
    for (size_t i = 0; i < 5; ++i)
        ck_assert_int_eq(a[i], b[i]);
}
END_TEST

Suite* sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("sort");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, sort_one_elem);
    tcase_add_test(tc_pos, sort_sorted);
    tcase_add_test(tc_pos, sort_reversed);
    tcase_add_test(tc_pos, sort_random);
    suite_add_tcase(s, tc_pos);
    return s;
}

Suite* comparator_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("comparator");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, bigger);
    tcase_add_test(tc_pos, less);
    tcase_add_test(tc_pos, equal);
    suite_add_tcase(s, tc_pos);
    return s;
}