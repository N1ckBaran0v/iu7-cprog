#include "../inc/check_my_matrix.h"
#include "../inc/my_matrix.h"

START_TEST(square_1)
{
    matrix* matr;
    matr = create_matrix(1, 1);
    ck_assert_ptr_nonnull(matr);
    ck_assert_uint_eq((unsigned)matr->n, 1);
    ck_assert_uint_eq((unsigned)matr->m, 1);
    free_matrix(matr);
}
END_TEST

START_TEST(square_3)
{
    matrix* matr;
    matr = create_matrix(3, 3);
    ck_assert_ptr_nonnull(matr);
    ck_assert_uint_eq((unsigned)matr->n, 3);
    ck_assert_uint_eq((unsigned)matr->m, 3);
    free_matrix(matr);
}
END_TEST

START_TEST(not_square)
{
    matrix* matr;
    matr = create_matrix(4, 2);
    ck_assert_ptr_nonnull(matr);
    ck_assert_uint_eq((unsigned)matr->n, 4);
    ck_assert_uint_eq((unsigned)matr->m, 2);
    free_matrix(matr);
}
END_TEST

START_TEST(equal)
{
    matrix *m1, *m2;
    m1 = create_matrix(2, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            m1->buf[i][j] = i + j + 1;
    m2 = resize_matrix(m1, 2);
    ck_assert_uint_eq((unsigned)m2->n, 2);
    ck_assert_uint_eq((unsigned)m2->m, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            ck_assert_int_eq((int)(m2->buf[i][j]), (int)(i + j + 1));
    free_matrix(m2);
}
END_TEST

START_TEST(not_equal)
{
    matrix *m1, *m2;
    m1 = create_matrix(2, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            m1->buf[i][j] = i + j + 1;
    m2 = resize_matrix(m1, 3);
    ck_assert_uint_eq((unsigned)m2->n, 2);
    ck_assert_uint_eq((unsigned)m2->m, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            ck_assert_int_eq((int)(m2->buf[i][j]), (int)(i + j + 1));
    free_matrix(m2);
}
END_TEST

Suite* create_matrix_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("init");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, square_1);
    tcase_add_test(tc_pos, square_3);
    tcase_add_test(tc_pos, not_square);
    suite_add_tcase(s, tc_pos);
    return s;
}

Suite* resize_matrix_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("resize");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, equal);
    tcase_add_test(tc_pos, not_equal);
    suite_add_tcase(s, tc_pos);
    return s;
}