#include "../inc/check_my_multiple.h"
#include "../inc/my_multiple.h"
#include "../inc/my_errors.h"

START_TEST(id_matrixes)
{
    matrix *m1, *m2;
    m1 = create_matrix(2, 2);
    m2 = create_matrix(2, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            m1->buf[i][j] = m2->buf[i][j] = 0;
    int rc = mult(&m1, m2, 0, 0);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_uint_eq((unsigned)m1->n, 2);
    ck_assert_uint_eq((unsigned)m1->m, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            ck_assert_int_eq((int)(m1->buf[i][j]), (int)(i == j));
    free_matrix(m1);
    free_matrix(m2);
}
END_TEST

START_TEST(one_id_matrix)
{
    matrix *m1, *m2;
    m1 = create_matrix(2, 2);
    m2 = create_matrix(2, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            m1->buf[i][j] = m2->buf[i][j] = 2;
    int rc = mult(&m1, m2, 0, 1);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_uint_eq((unsigned)m1->n, 2);
    ck_assert_uint_eq((unsigned)m1->m, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            ck_assert_int_eq((int)(m1->buf[i][j]), 2);
    free_matrix(m1);
    free_matrix(m2);
}
END_TEST

START_TEST(simple_mult)
{
    matrix *m1, *m2;
    m1 = create_matrix(2, 2);
    m2 = create_matrix(2, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            m1->buf[i][j] = m2->buf[i][j] = 1;
    int rc = mult(&m1, m2, 1, 1);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_uint_eq((unsigned)m1->n, 2);
    ck_assert_uint_eq((unsigned)m1->m, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            ck_assert_int_eq((int)(m1->buf[i][j]), 2);
    free_matrix(m1);
    free_matrix(m2);
}
END_TEST

START_TEST(matr_square)
{
    matrix *m1, *m2;
    m1 = create_matrix(2, 2);
    m2 = create_matrix(2, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            m1->buf[i][j] = m2->buf[i][j] = 1;
    int rc = mult(&m1, m2, 2, 0);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_uint_eq((unsigned)m1->n, 2);
    ck_assert_uint_eq((unsigned)m1->m, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            ck_assert_int_eq((int)(m1->buf[i][j]), 2);
    free_matrix(m1);
    free_matrix(m2);
}
END_TEST

START_TEST(difficult_mult)
{
    matrix *m1, *m2;
    m1 = create_matrix(2, 2);
    m2 = create_matrix(2, 2);
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            m1->buf[i][j] = i * 2 + j + 1;
            m2->buf[i][j] = (i + 1) * (j + 1);
        }
    }
    int rc = mult(&m1, m2, 2, 3);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_uint_eq((unsigned)m1->n, 2);
    ck_assert_uint_eq((unsigned)m1->m, 2);
    ck_assert_int_eq((int)(m1->buf[0][0]), 675);
    ck_assert_int_eq((int)(m1->buf[0][1]), 1350);
    ck_assert_int_eq((int)(m1->buf[1][0]), 1475);
    ck_assert_int_eq((int)(m1->buf[1][1]), 2950);
    free_matrix(m1);
    free_matrix(m2);
}
END_TEST

Suite* mult_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("multiple");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, id_matrixes);
    tcase_add_test(tc_pos, one_id_matrix);
    tcase_add_test(tc_pos, simple_mult);
    tcase_add_test(tc_pos, matr_square);
    tcase_add_test(tc_pos, difficult_mult);
    suite_add_tcase(s, tc_pos);
    return s;
}