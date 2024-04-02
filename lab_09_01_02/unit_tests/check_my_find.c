#include "check_my_find.h"
#include "my_errors.h"

#define EPS 1e-7

START_TEST(found_0)
{
    char *fstr[] = {"big knife\n", "bomb\n", "big cleaver\n"};
    double fd[] = {3, 10, 5};
    double sd[] = {1, 5, 2};
    struct subject src[3];
    for (size_t i = 0; i < 3; ++i)
    {
        src[i].name = fstr[i];
        src[i].m = fd[i];
        src[i].v = sd[i];
        src[i].r = fd[i] / sd[i];
    }
    size_t ind[3];
    size_t sind = 0;
    int rc = find("bug", src, 3, ind, &sind);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq((int)sind, 0);
}

START_TEST(found_1)
{
    char *fstr[] = {"big knife\n", "bomb\n", "big cleaver\n"};
    double fd[] = {3, 10, 5};
    double sd[] = {1, 5, 2};
    struct subject src[3];
    for (size_t i = 0; i < 3; ++i)
    {
        src[i].name = fstr[i];
        src[i].m = fd[i];
        src[i].v = sd[i];
        src[i].r = fd[i] / sd[i];
    }
    size_t ind[3];
    size_t sind = 0;
    int rc = find("bomb", src, 3, ind, &sind);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq((int)sind, 1);
    ck_assert_int_eq((int)ind[0], 1);
}

START_TEST(found_2)
{
    char *fstr[] = {"big knife\n", "bomb\n", "big cleaver\n"};
    double fd[] = {3, 10, 5};
    double sd[] = {1, 5, 2};
    struct subject src[3];
    for (size_t i = 0; i < 3; ++i)
    {
        src[i].name = fstr[i];
        src[i].m = fd[i];
        src[i].v = sd[i];
        src[i].r = fd[i] / sd[i];
    }
    size_t ind[3];
    size_t sind = 0;
    int rc = find("big", src, 3, ind, &sind);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq((int)sind, 2);
    ck_assert_int_eq((int)ind[0], 0);
    ck_assert_int_eq((int)ind[1], 2);
}

START_TEST(found_3)
{
    char *fstr[] = {"big knife\n", "bomb\n", "big cleaver\n"};
    double fd[] = {3, 10, 5};
    double sd[] = {1, 5, 2};
    struct subject src[3];
    for (size_t i = 0; i < 3; ++i)
    {
        src[i].name = fstr[i];
        src[i].m = fd[i];
        src[i].v = sd[i];
        src[i].r = fd[i] / sd[i];
    }
    size_t ind[3];
    size_t sind = 0;
    int rc = find("b", src, 3, ind, &sind);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq((int)sind, 3);
    ck_assert_int_eq((int)ind[0], 0);
    ck_assert_int_eq((int)ind[1], 1);
    ck_assert_int_eq((int)ind[2], 2);
}

START_TEST(found_all)
{
    char *fstr[] = {"big knife\n", "bomb\n", "big cleaver\n"};
    double fd[] = {3, 10, 5};
    double sd[] = {1, 5, 2};
    struct subject src[3];
    for (size_t i = 0; i < 3; ++i)
    {
        src[i].name = fstr[i];
        src[i].m = fd[i];
        src[i].v = sd[i];
        src[i].r = fd[i] / sd[i];
    }
    size_t ind[3];
    size_t sind = 0;
    int rc = find("ALL", src, 3, ind, &sind);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq((int)sind, 3);
    ck_assert_int_eq((int)ind[0], 0);
    ck_assert_int_eq((int)ind[1], 1);
    ck_assert_int_eq((int)ind[2], 2);
}

START_TEST(sorted)
{
    char *fstr[] = {"f1\n", "f2\n", "f3\n"};
    double fd[] = {2, 3, 4};
    double sd[] = {1, 1, 1};
    struct subject src[3];
    for (size_t i = 0; i < 3; ++i)
    {
        src[i].name = fstr[i];
        src[i].m = fd[i];
        src[i].v = sd[i];
        src[i].r = fd[i] / sd[i];
    }
    sort(src, 3);
    for (size_t i = 0; i < 3; ++i)
    {
        ck_assert_str_eq(src[i].name, fstr[i]);
        ck_assert_double_eq_tol(src[i].m, fd[i], EPS);
        ck_assert_double_eq_tol(src[i].v, sd[i], EPS);
    }
}

START_TEST(reversed)
{
    char *fstr[] = {"f1\n", "f2\n", "f3\n"};
    double fd[] = {4, 3, 2};
    double sd[] = {1, 1, 1};
    struct subject src[3];
    for (size_t i = 0; i < 3; ++i)
    {
        src[i].name = fstr[i];
        src[i].m = fd[i];
        src[i].v = sd[i];
        src[i].r = fd[i] / sd[i];
    }
    sort(src, 3);
    for (size_t i = 0; i < 3; ++i)
    {
        ck_assert_str_eq(src[2 - i].name, fstr[i]);
        ck_assert_double_eq_tol(src[2 - i].m, fd[i], EPS);
        ck_assert_double_eq_tol(src[2 - i].v, sd[i], EPS);
    }
}

START_TEST(unsorted)
{
    char *fstr[] = {"f1\n", "f2\n", "f3\n"};
    double fd[] = {3, 4, 2};
    double sd[] = {1, 1, 1};
    struct subject src[3];
    for (size_t i = 0; i < 3; ++i)
    {
        src[i].name = fstr[i];
        src[i].m = fd[i];
        src[i].v = sd[i];
        src[i].r = fd[i] / sd[i];
    }
    sort(src, 3);
    for (size_t i = 0; i < 3; ++i)
    {
        ck_assert_str_eq(src[i].name, fstr[(i + 2) % 3]);
        ck_assert_double_eq_tol(src[i].m, fd[(i + 2) % 3], EPS);
        ck_assert_double_eq_tol(src[i].v, sd[(i + 2) % 3], EPS);
    }
}

Suite *find_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("find");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, found_0);
    tcase_add_test(tc_pos, found_1);
    tcase_add_test(tc_pos, found_2);
    tcase_add_test(tc_pos, found_3);
    tcase_add_test(tc_pos, found_all);
    suite_add_tcase(s, tc_pos);
    return s;
}

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("sort");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, sorted);
    tcase_add_test(tc_pos, reversed);
    tcase_add_test(tc_pos, unsorted);
    suite_add_tcase(s, tc_pos);
    return s;
}