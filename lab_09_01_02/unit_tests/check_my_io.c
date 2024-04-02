#include <stddef.h>
#include <stdlib.h>

#include "check_my_io.h"
#include "my_errors.h"

#define EPS 1e-7

START_TEST(one_value)
{
    struct subject *dst;
    size_t num = 0;
    int rc = read("func_tests/data/pos_01_src.txt", &dst, &num);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq((int)num, 1);
    ck_assert_str_eq(dst[0].name, "lonely\n");
    ck_assert_double_eq_tol(dst[0].m, 3, EPS);
    ck_assert_double_eq_tol(dst[0].v, 4, EPS);
    free(dst[0].name);
    free(dst);
}
END_TEST

START_TEST(three_values)
{
    struct subject *dst;
    size_t num = 0;
    char *fstr[] = {"big knife\n", "bomb\n", "big cleaver\n"};
    double fd[] = {3, 10, 5};
    double sd[] = {1, 5, 2};
    int rc = read("func_tests/data/pos_02_src.txt", &dst, &num);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq((int)num, 3);
    for (size_t i = 0; i < num; ++i)
    {
        ck_assert_str_eq(dst[i].name, fstr[i]);
        ck_assert_double_eq_tol(dst[i].m, fd[i], EPS);
        ck_assert_double_eq_tol(dst[i].v, sd[i], EPS);
        free(dst[i].name);
    }
    free(dst);
}
END_TEST

START_TEST(file_not_found)
{
    struct subject *dst = NULL;
    size_t num = 0;
    int rc = read("where.txt", &dst, &num);
    ck_assert_int_eq(rc, ERR_FILE_OPEN);
    ck_assert_ptr_null(dst);
}

Suite *read_struct_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;
    s = suite_create("read");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, one_value);
    tcase_add_test(tc_pos, three_values);
    suite_add_tcase(s, tc_pos);
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_pos, file_not_found);
    suite_add_tcase(s, tc_neg);
    return s;
}