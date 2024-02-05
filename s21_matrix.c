#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (result == NULL || (rows <= 0 || columns <= 0)) {
    res = INCORRECT_MATRIX;
  } else {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; ++i) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
    result->rows = rows;
    result->columns = columns;
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->rows; ++i) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int cmp = SUCCESS;
  if (A == NULL || B == NULL || A->rows != B->rows ||
      A->columns != B->columns || A->columns <= 0 || A->rows <= 0 ||
      B->columns <= 0 || B->rows <= 0) {
    cmp = FAILURE;
  } else {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.0000001) {
          cmp = FAILURE;
          break;
        }
      }
    }
  }
  return cmp;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (result == NULL || A == NULL || B == NULL || B->columns <= 0 ||
      B->rows <= 0 || A->columns <= 0 || A->rows <= 0) {
    res = INCORRECT_MATRIX;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    res = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (result == NULL || A == NULL || B == NULL || B->columns <= 0 ||
      B->rows <= 0 || A->columns <= 0 || A->rows <= 0) {
    res = INCORRECT_MATRIX;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    res = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (result == NULL || A == NULL || A->columns <= 0 || A->rows <= 0) {
    res = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (result == NULL || A == NULL || B == NULL || B->columns <= 0 ||
      B->rows <= 0 || A->columns <= 0 || A->rows <= 0) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    res = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < B->columns; ++j) {
        for (int k = 0; k < B->rows; ++k) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (result == NULL || A == NULL || A->columns <= 0 || A->rows <= 0) {
    res = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->columns; ++i) {
      for (int j = 0; j < A->rows; ++j) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (A == NULL || result == NULL || A->columns <= 0 || A->rows <= 0) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    if (A->rows == 1) {
      result->matrix[0][0] = A->matrix[0][0];
    } else {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->columns; ++j) {
          result->matrix[i][j] = s21_minor(A, i, j) * pow(-1, i + j);
        }
      }
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || result == NULL || A->columns <= 0 || A->rows <= 0)
    return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else {
    for (int i = 0; i < A->rows; ++i) {
      matrix_t temp = {0};
      double result_2 = 0.0;
      s21_get_submatrix(A, 0, i, &temp);
      s21_determinant(&temp, &result_2);
      s21_remove_matrix(&temp);
      *result += (pow(-1, i) * A->matrix[0][i] * result_2);
    }
  }
  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->columns <= 0 || A->rows <= 0)
    return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  double det = 0.0;
  s21_determinant(A, &det);
  if (fabs(det) < 1e-6) return CALCULATION_ERROR;
  if (A->rows == 1) {
    s21_calc_complements(A, result);
    result->matrix[0][0] = (1 / det);
  } else {
    matrix_t calc_res, transp_res;
    s21_calc_complements(A, &calc_res);
    s21_transpose(&calc_res, &transp_res);
    s21_remove_matrix(&calc_res);
    s21_mult_number(&transp_res, 1 / det, result);
    s21_remove_matrix(&transp_res);
  }
  return OK;
}

// вспомогательные
void s21_print_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      if (i == A->rows - 1 && j == A->columns - 1) {
        printf("%f", A->matrix[i][j]);
        break;
      }
      printf("%f ", A->matrix[i][j]);
    }
    if (i != i - 1) printf("\n");
  }
  printf("\n");
}

int s21_get_submatrix(matrix_t *A, int m, int n, matrix_t *result) {
  if (A == NULL || result == NULL) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  int k = 0, l = 0;
  s21_create_matrix(A->rows - 1, A->rows - 1, result);
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->rows; ++j) {
      if (i != m && j != n) {
        result->matrix[k][l] = A->matrix[i][j];
        ++l;
        if (l == result->rows) {
          l = 0;
          ++k;
        }
      }
    }
  }
  return OK;
}

double s21_minor(matrix_t *A, int i, int j) {
  double minor = 0.0;
  matrix_t result;
  s21_get_submatrix(A, i, j, &result);
  s21_determinant(&result, &minor);
  s21_remove_matrix(&result);
  return minor;
}
