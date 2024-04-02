#include <stdlib.h>

#include "../inc/check_my_io.h"
#include "../inc/my_io.h"
#include "../inc/my_errors.h"

START_TEST(no_file)
{
    int *a = 0, *b = 0;
    int rc = read("where", &a, &b);
    ck_assert_int_ne(rc, ERR_OK);
    free(a);
}
END_TEST

START_TEST(empty_file)
{
    int *a = 0, *b = 0;
    int rc = read("func_tests/data/neg_01_in.txt", &a, &b);
    ck_assert_int_ne(rc, ERR_OK);
    free(a);
}
END_TEST

START_TEST(success_reading)
{
    int *a = 0, *b = 0;
    int c[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int rc = read("func_tests/data/pos_02_in.txt", &a, &b);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq((int)(b - a), 10);
    for (size_t i = 0; i < (size_t)(b - a); ++i)
        ck_assert_int_eq(a[i], c[i]);
    free(a);
}
END_TEST

START_TEST(output)
{
    int a[] = {1, 2, 3, 4};
    int rc = write("func_tests/scripts/pos_01_unit.txt", a, a + 4);
    ck_assert_int_eq(rc, ERR_OK);
    int *b = 0, *c = 0;
    rc = read("func_tests/scripts/pos_01_unit.txt", &b, &c);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq((int)(c - b), 4);
    for (size_t i = 0; i < (size_t)(c - b); ++i)
        ck_assert_int_eq(b[i], a[i]);
    free(b);
}
END_TEST

Suite* input_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;
    s = suite_create("input");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, success_reading);
    suite_add_tcase(s, tc_pos);
    tc_neg = tcase_create("positives");
    tcase_add_test(tc_neg, no_file);
    tcase_add_test(tc_pos, empty_file);
    suite_add_tcase(s, tc_neg);
    return s;
}

Suite* output_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("input");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, output);
    suite_add_tcase(s, tc_pos);
    return s;
}