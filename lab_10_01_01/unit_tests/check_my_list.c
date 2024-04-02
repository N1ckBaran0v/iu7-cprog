#include <stdlib.h>

#include "check_my_list.h"
#include "my_list.h"

START_TEST(pop_size_one)
{
    int i = 5;
    node_t *node = my_init(&i, sizeof(int), NULL);
    int *ptr = pop_front(&node);
    ck_assert_int_eq(*ptr, i);
}
END_TEST

START_TEST(insert_diff_cases)
{
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    node_t *n1 = my_init(&i1, sizeof(int), NULL);
    node_t *n2 = my_init(&i2, sizeof(int), NULL);
    node_t *n3 = my_init(&i3, sizeof(int), NULL);
    node_t *n4 = my_init(&i4, sizeof(int), NULL);
    node_t *list = NULL;
    insert(&list, n1, NULL);
    insert(&list, n2, NULL);
    insert(&list, n3, n1);
    insert(&list, n4, n1);
    int *ptr = pop_front(&list);
    ck_assert_int_eq(*ptr, i3);
    ptr = pop_front(&list);
    ck_assert_int_eq(*ptr, i4);
    ptr = pop_front(&list);
    ck_assert_int_eq(*ptr, i1);
    ptr = pop_front(&list);
    ck_assert_int_eq(*ptr, i2);
}
END_TEST

Suite *pop_front_suite(void)
{
    
    Suite *s;
    TCase *tc_pos;
    s = suite_create("pop_front");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, pop_size_one);
    suite_add_tcase(s, tc_pos);
    return s;
}

Suite *insert_suite(void)
{
    
    Suite *s;
    TCase *tc_pos;
    s = suite_create("insert");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, insert_diff_cases);
    suite_add_tcase(s, tc_pos);
    return s;
}

