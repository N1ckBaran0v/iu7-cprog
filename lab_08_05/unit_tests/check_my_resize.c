#include "../inc/check_my_resize.h"
#include "../inc/my_resize.h"
#include "../inc/my_errors.h"

START_TEST(square)
{
    matrix *m1;
    m1 = create_matrix(2, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            m1->buf[i][j] = i * 2 + j + 1;
    to_square(m1);
    ck_assert_uint_eq((unsigned)m1->n, 2);
    ck_assert_uint_eq((unsigned)m1->m, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            ck_assert_int_eq((int)(m1->buf[i][j]), (int)(i * 2 + j + 1));
    free_matrix(m1);
}
END_TEST

START_TEST(rows)
{
    matrix *m1;
    m1 = create_matrix(5, 2);
    m1->buf[0][0] = 3;
    m1->buf[0][1] = 2;
    m1->buf[1][0] = 3;
    m1->buf[1][1] = 3;
    m1->buf[2][0] = 2;
    m1->buf[2][1] = 3;
    m1->buf[3][0] = 3;
    m1->buf[3][1] = 2;
    m1->buf[4][0] = 3;
    m1->buf[4][1] = 2;
    to_square(m1);
    ck_assert_uint_eq((unsigned)m1->n, 2);
    ck_assert_uint_eq((unsigned)m1->m, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            ck_assert_int_eq((int)(m1->buf[i][j]), (int)(3 - (i == 1 && j == 1)));
    free_matrix(m1);
}
END_TEST

START_TEST(columns)
{
    matrix *m1;
    m1 = create_matrix(2, 5);
    m1->buf[0][0] = 3;
    m1->buf[0][1] = 2;
    m1->buf[0][2] = 3;
    m1->buf[0][3] = 2;
    m1->buf[0][4] = 2;
    m1->buf[1][0] = 2;
    m1->buf[1][1] = 3;
    m1->buf[1][2] = 3;
    m1->buf[1][3] = 3;
    m1->buf[1][4] = 3;
    to_square(m1);
    ck_assert_uint_eq((unsigned)m1->n, 2);
    ck_assert_uint_eq((unsigned)m1->m, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            ck_assert_int_eq((int)(m1->buf[i][j]), (int)(3 - (i == 1 && j == 0)));
    free_matrix(m1);
}
END_TEST

START_TEST(equal_size)
{
    matrix *m1, *m2;
    m1 = create_matrix(2, 2);
    m2 = create_matrix(2, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            m1->buf[i][j] = m2->buf[i][j] = 0;
    int rc = increase(&m1, &m2);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_uint_eq((unsigned)m1->n, 2);
    ck_assert_uint_eq((unsigned)m1->m, 2);
    ck_assert_uint_eq((unsigned)m2->n, 2);
    ck_assert_uint_eq((unsigned)m2->m, 2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            ck_assert_int_eq((int)(m1->buf[i][j]), (int)(m2->buf[i][j]));
    free_matrix(m1);
    free_matrix(m2);
}
END_TEST

START_TEST(first_less)
{
    matrix *m1, *m2;
    m1 = create_matrix(2, 2);
    m2 = create_matrix(3, 3);
    m1->buf[0][0] = 2;
    m1->buf[0][1] = -7;
    m1->buf[1][0] = -5;
    m1->buf[1][1] = 4;
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            m2->buf[i][j] = i + j + 1;
    int rc = increase(&m1, &m2);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_uint_eq((unsigned)m1->n, 3);
    ck_assert_uint_eq((unsigned)m1->m, 3);
    ck_assert_uint_eq((unsigned)m2->n, 3);
    ck_assert_uint_eq((unsigned)m2->m, 3);
    ck_assert_int_eq((int)m1->buf[0][0], 2);
    ck_assert_int_eq((int)m1->buf[0][1], -7);
    ck_assert_int_eq((int)m1->buf[0][2], 2);
    ck_assert_int_eq((int)m1->buf[1][0], -5);
    ck_assert_int_eq((int)m1->buf[1][1], 4);
    ck_assert_int_eq((int)m1->buf[1][2], 4);
    ck_assert_int_eq((int)m1->buf[2][0], 3);
    ck_assert_int_eq((int)m1->buf[2][1], 5);
    ck_assert_int_eq((int)m1->buf[2][2], 5);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            ck_assert_int_eq((int)(m2->buf[i][j]), (int)(i + j + 1));
    free_matrix(m1);
    free_matrix(m2);
}
END_TEST

START_TEST(second_less)
{
    matrix *m1, *m2;
    m1 = create_matrix(2, 2);
    m2 = create_matrix(3, 3);
    m1->buf[0][0] = 2;
    m1->buf[0][1] = -7;
    m1->buf[1][0] = -5;
    m1->buf[1][1] = 4;
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            m2->buf[i][j] = i + j + 1;
    int rc = increase(&m2, &m1);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_uint_eq((unsigned)m1->n, 3);
    ck_assert_uint_eq((unsigned)m1->m, 3);
    ck_assert_uint_eq((unsigned)m2->n, 3);
    ck_assert_uint_eq((unsigned)m2->m, 3);
    ck_assert_int_eq((int)m1->buf[0][0], 2);
    ck_assert_int_eq((int)m1->buf[0][1], -7);
    ck_assert_int_eq((int)m1->buf[0][2], 2);
    ck_assert_int_eq((int)m1->buf[1][0], -5);
    ck_assert_int_eq((int)m1->buf[1][1], 4);
    ck_assert_int_eq((int)m1->buf[1][2], 4);
    ck_assert_int_eq((int)m1->buf[2][0], 3);
    ck_assert_int_eq((int)m1->buf[2][1], 5);
    ck_assert_int_eq((int)m1->buf[2][2], 5);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            ck_assert_int_eq((int)(m2->buf[i][j]), (int)(i + j + 1));
    free_matrix(m1);
    free_matrix(m2);
}
END_TEST

Suite* to_square_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("delete rows/columns");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, square);
    tcase_add_test(tc_pos, rows);
    tcase_add_test(tc_pos, columns);
    suite_add_tcase(s, tc_pos);
    return s;
}

Suite* increase_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("add rows/columns");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, equal_size);
    tcase_add_test(tc_pos, first_less);
    tcase_add_test(tc_pos, second_less);
    suite_add_tcase(s, tc_pos);
    return s;
}