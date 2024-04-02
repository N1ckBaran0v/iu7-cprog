#include "check_my_list.h"
#include "my_list.h"

START_TEST(one_str)
{
    list_t *str1 = list_init("test");
    list_t *str2 = list_init("test");
    list_t *ans1 = list_init("testtest");
    str1 = list_cat(str1, str2);
    ck_assert_int_eq(list_cmp(str1, ans1), 0);
    list_free(str1);
    list_free(str2);
    list_free(ans1);
}
END_TEST

START_TEST(two_strs)
{
    list_t *str3 = list_init("test m");
    list_t *str4 = list_init("e please");
    list_t *ans2 = list_init("test me please");
    str3 = list_cat(str3, str4);
    ck_assert_int_eq(list_cmp(str3, ans2), 0);
    list_free(str3);
    list_free(str4);
    list_free(ans2);
}
END_TEST

START_TEST(no_spaces)
{
    list_t *str = list_init("test must not be changed");
    list_t *ans = list_init("test must not be changed");
    str = list_sps(str);
    ck_assert_int_eq(list_cmp(str, ans), 0);
    list_free(str);
    list_free(ans);
}
END_TEST

START_TEST(some_spaces)
{
    list_t *str = list_init("test       must    be changed");
    list_t *ans = list_init("test must be changed");
    str = list_sps(str);
    ck_assert_int_eq(list_cmp(str, ans), 0);
    list_free(str);
    list_free(ans);
}
END_TEST

START_TEST(not_found)
{
    list_t *str = list_init("you will never find this");
    list_t *ans = list_init("haha");
    int rc = list_pos(str, ans);
    ck_assert_int_eq(rc, -1);
    list_free(str);
    list_free(ans);
}
END_TEST

START_TEST(found_start)
{
    list_t *str = list_init("find me please");
    list_t *ans = list_init("find me");
    int rc = list_pos(str, ans);
    ck_assert_int_eq(rc, 0);
    list_free(str);
    list_free(ans);
}
END_TEST

START_TEST(found_mid)
{
    list_t *str = list_init("find me please");
    list_t *ans = list_init(" me ");
    int rc = list_pos(str, ans);
    ck_assert_int_eq(rc, 4);
    list_free(str);
    list_free(ans);
}
END_TEST

START_TEST(found_end)
{
    list_t *str = list_init("find me please");
    list_t *ans = list_init("ease");
    int rc = list_pos(str, ans);
    ck_assert_int_eq(rc, 10);
    list_free(str);
    list_free(ans);
}
END_TEST

Suite *list_cat_suite(void)
{
    
    Suite *s;
    TCase *tc_pos;
    s = suite_create("cat");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, one_str);
    tcase_add_test(tc_pos, two_strs);
    suite_add_tcase(s, tc_pos);
    return s;
}

Suite *list_sps_suite(void)
{
    
    Suite *s;
    TCase *tc_pos;
    s = suite_create("sps");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, no_spaces);
    tcase_add_test(tc_pos, some_spaces);
    suite_add_tcase(s, tc_pos);
    return s;
}

Suite *list_pos_suite(void)
{
    
    Suite *s;
    TCase *tc_pos, *tc_neg;
    s = suite_create("pos");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, found_start);
    tcase_add_test(tc_pos, found_mid);
    tcase_add_test(tc_pos, found_end);
    suite_add_tcase(s, tc_pos);
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, not_found);
    suite_add_tcase(s, tc_neg);
    return s;
}

