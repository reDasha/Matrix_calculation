#include <check.h>

#include "s21_matrix.h"

START_TEST(simple_matrix_func) {
  matrix_t mat, result_1, result_2, result_3, mat_2;
  int m = 3, n = 2, a = 2, b = 3, c = 0, d = -1;
  s21_create_matrix(m, n, &mat);
  printf("%d\n", s21_create_matrix(m, n, NULL));
  ck_assert_int_eq(s21_create_matrix(m, n, NULL), 1);
  double arr[] = {1.0, 4.0, 2.0, 5.0, 3.0, 6.0};
  for (int i = 0, k = 0; i < m && k < (int)(sizeof(arr) / sizeof(double));
       ++i) {
    for (int j = 0; j < n; ++j, ++k) {
      mat.matrix[i][j] = arr[k];
    }
  }
  s21_print_matrix(&mat);
  s21_create_matrix(a, b, &mat_2);
  ck_assert_int_eq(s21_create_matrix(c, n, &mat), 1);
  ck_assert_int_eq(s21_create_matrix(m, d, &mat), 1);
  double arr_2[] = {1.0, -1.0, 1.0, 2.0, 3.0, 4.0};
  for (int i = 0, k = 0; i < a && k < (int)(sizeof(arr_2) / sizeof(double));
       ++i) {
    for (int j = 0; j < b; ++j, ++k) {
      mat_2.matrix[i][j] = arr_2[k];
    }
  }
  ck_assert_int_eq(s21_mult_number(&mat, 1.1, &result_1), 0);
  ck_assert_int_eq(s21_mult_number(&mat, 1.1, NULL), 1);
  s21_print_matrix(&result_1);
  ck_assert_int_eq(s21_transpose(&mat, NULL), 1);
  ck_assert_int_eq(s21_transpose(&mat, &result_3), 0);
  s21_print_matrix(&result_3);
  ck_assert_int_eq(s21_sum_matrix(&result_3, &result_3, &result_2), 0);
  ck_assert_int_eq(s21_sum_matrix(&result_3, &result_1, &result_2), 2);
  ck_assert_int_eq(s21_sum_matrix(&result_3, &result_3, NULL), 1);
  ck_assert_int_eq(s21_sub_matrix(&result_3, &result_3, &result_2), 0);
  ck_assert_int_eq(s21_sub_matrix(&result_3, &result_1, &result_2), 2);
  ck_assert_int_eq(s21_sub_matrix(&result_3, &result_3, NULL), 1);
  ck_assert_int_eq(s21_eq_matrix(&result_3, &result_2), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_3, NULL), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_3, &result_3), 1);
  ck_assert_int_eq(s21_mult_matrix(&mat, &mat_2, &result_2), 0);
  ck_assert_int_eq(s21_mult_matrix(&mat, &mat_2, NULL), 1);
  ck_assert_int_eq(s21_mult_matrix(&mat, &result_1, &result_2), 2);
  ck_assert_int_eq(s21_calc_complements(&mat, &result_1), 2);
  ck_assert_int_eq(s21_inverse_matrix(&mat, &result_3), 2);
  s21_print_matrix(&result_2);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&result_1);
  s21_remove_matrix(&result_2);
  s21_remove_matrix(&result_3);
  printf("done");
  s21_print_matrix(&result_3);
}
END_TEST

START_TEST(determinant_matrix_func) {
  matrix_t mat, result, result_2, result_3, mat_1, mat_2, mat_3;
  int m = 3, n = 3;
  s21_create_matrix(m, n, &mat);
  double arr[] = {2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0, -3.0};
  for (int i = 0, k = 0; i < m && k < 9; ++i) {
    for (int j = 0; j < n; ++j, ++k) {
      mat.matrix[i][j] = arr[k];
    }
  }
  s21_print_matrix(&mat);
  s21_get_submatrix(&mat, 1, 1, &result);
  ck_assert_int_eq(s21_get_submatrix(NULL, 1, 1, &result), 1);
  printf("minor: %f\n", s21_minor(&mat, 1, 1));
  s21_calc_complements(&mat, &result_2);
  printf("minor_matrix:\n");
  s21_print_matrix(&result_2);
  ck_assert_int_eq(s21_calc_complements(NULL, &result_2), 1);
  double det = 0.0;
  s21_determinant(&mat, &det);
  ck_assert_int_eq(s21_determinant(NULL, &det), 1);
  printf("%f\n", det);
  s21_inverse_matrix(&mat, &result_3);
  s21_print_matrix(&result_3);
  ck_assert_int_eq(s21_inverse_matrix(NULL, &result_3), 1);
  s21_create_matrix(1, 1, &mat_1);
  s21_create_matrix(1, 1, &mat_2);
  mat_1.matrix[0][0] = 42.12849;
  mat_2.matrix[0][0] = 1 / 42.12849;
  s21_inverse_matrix(&mat_1, &mat_3);
  ck_assert_double_eq(s21_eq_matrix(&mat_3, &mat_2), 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&mat_3);

  s21_remove_matrix(&mat);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_2);
  s21_remove_matrix(&result_3);
  printf("\ndone\n");
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, simple_matrix_func);
  tcase_add_test(tc1_1, determinant_matrix_func);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
