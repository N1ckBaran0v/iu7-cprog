#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>

#include "check_my_snprintf.h"
#include "my_snprintf.h"

#define STR_MAX_SIZE 51

START_TEST(no_spec)
{
    char buf0[STR_MAX_SIZE];
    char buf1[STR_MAX_SIZE];
    int rc0, rc1;
    rc0 = snprintf(buf0, STR_MAX_SIZE, "Hello, world!\n");
    rc1 = my_snprintf(buf1, STR_MAX_SIZE, "Hello, world!\n");
    ck_assert_int_eq(rc0, rc1);
    ck_assert_int_eq(strcmp(buf0, buf1), 0);
}
END_TEST

START_TEST(no_buf)
{
    int rc0, rc1;
    rc0 = snprintf(NULL, 0, "Hello, world!\n");
    rc1 = my_snprintf(NULL, 0, "Hello, world!\n");
    ck_assert_int_eq(rc0, rc1);
}
END_TEST

START_TEST(c_case)
{
    char buf0[STR_MAX_SIZE];
    char buf1[STR_MAX_SIZE];
    int rc0, rc1;
    rc0 = snprintf(buf0, STR_MAX_SIZE, "%cello, world!\n", 'H');
    rc1 = my_snprintf(buf1, STR_MAX_SIZE, "%cello, world!\n", 'H');
    ck_assert_int_eq(rc0, rc1);
    ck_assert_int_eq(strcmp(buf0, buf1), 0);
}
END_TEST

START_TEST(s_case)
{
    char buf0[STR_MAX_SIZE];
    char buf1[STR_MAX_SIZE];
    int rc0, rc1;
    rc0 = snprintf(buf0, STR_MAX_SIZE, "%s, world!\n", "Hello");
    rc1 = my_snprintf(buf1, STR_MAX_SIZE, "%s, world!\n", "Hello");
    ck_assert_int_eq(rc0, rc1);
    ck_assert_int_eq(strcmp(buf0, buf1), 0);
}
END_TEST

START_TEST(d_case)
{
    char buf0[STR_MAX_SIZE];
    char buf1[STR_MAX_SIZE];
    int rc0, rc1;
    rc0 = snprintf(buf0, STR_MAX_SIZE, "%d units are ready\n", 200000);
    rc1 = my_snprintf(buf1, STR_MAX_SIZE, "%d units are ready\n", 200000);
    ck_assert_int_eq(rc0, rc1);
    ck_assert_int_eq(strcmp(buf0, buf1), 0);
}
END_TEST

START_TEST(x_case)
{
    char buf0[STR_MAX_SIZE];
    char buf1[STR_MAX_SIZE];
    int rc0, rc1;
    rc0 = snprintf(buf0, STR_MAX_SIZE, "with a %x more well on the way\n", 1000000);
    rc1 = my_snprintf(buf1, STR_MAX_SIZE, "with a %x more well on the way\n", 1000000);
    ck_assert_int_eq(rc0, rc1);
    ck_assert_int_eq(strcmp(buf0, buf1), 0);
}
END_TEST

START_TEST(hd_case)
{
    char buf0[STR_MAX_SIZE];
    char buf1[STR_MAX_SIZE];
    int rc0, rc1;
    rc0 = snprintf(buf0, STR_MAX_SIZE, "My number is %hd\n", 0);
    rc1 = my_snprintf(buf1, STR_MAX_SIZE, "My number is %hd\n", 0);
    ck_assert_int_eq(rc0, rc1);
    ck_assert_int_eq(strcmp(buf0, buf1), 0);
}
END_TEST

START_TEST(hx_case)
{
    char buf0[STR_MAX_SIZE];
    char buf1[STR_MAX_SIZE];
    int rc0, rc1;
    rc0 = snprintf(buf0, STR_MAX_SIZE, "Press \'%hx\' to pay respect!\n", 15);
    rc1 = my_snprintf(buf1, STR_MAX_SIZE, "Press \'%hx\' to pay respect!\n", 15);
    ck_assert_int_eq(rc0, rc1);
    ck_assert_int_eq(strcmp(buf0, buf1), 0);
}
END_TEST

Suite *snprintf_suite(void)
{
    
    Suite *s;
    TCase *tc_pos;
    s = suite_create("my_snprintf");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, no_spec);
    tcase_add_test(tc_pos, no_buf);
    tcase_add_test(tc_pos, c_case);
    tcase_add_test(tc_pos, s_case);
    tcase_add_test(tc_pos, d_case);
    tcase_add_test(tc_pos, x_case);
    tcase_add_test(tc_pos, hd_case);
    tcase_add_test(tc_pos, hx_case);
    suite_add_tcase(s, tc_pos);
    return s;
}
