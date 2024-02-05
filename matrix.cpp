#include "matrix.h"
#include "ui_matrix.h"

Matrix::Matrix(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Matrix)
{
    ui->setupUi(this);
}

Matrix::~Matrix()
{
    delete ui;
}


void Matrix::on_pushButton_transpose_clicked()
{
    ui->display->setText("");
    matrix_t mat, result;
    int m = ui->lineEdit_m1->text().toInt();
    int n = ui->lineEdit_n1->text().toInt();
    s21_create_matrix(m, n, &mat);

    QString input_str = ui->lineEdit_arr1->text();
    QStringList input_arr = input_str.split(" ", Qt::SkipEmptyParts);
     for (int i = 0, k = 0; i < m && k < m*n;
           ++i) {
        for (int j = 0; j < n; ++j, ++k) {
          mat.matrix[i][j] = input_arr[k].toDouble();
        }
      }
    if (s21_transpose(&mat, &result) < 1) {
        print_matrix_qt(&result);
    } else {
        to_display = QString("incorrect data");
    }
    ui->display->setText("A'\n");
    ui->display->setText(ui->display->text() + to_display);
    s21_remove_matrix(&mat);
    s21_remove_matrix(&result);
    to_display = "";
}

void Matrix::print_matrix_qt(matrix_t *A) {
    ui->display->setText("");
    for (int i = 0; i < A->rows; ++i) {
       for (int j = 0; j < A->columns; ++j) {
         to_display.append(QString::number(A->matrix[i][j]));
         to_display.append(' ');
         to_display.append(' ');
       }
       to_display.append('\n');
     }
    to_display.append('\n');
}

void Matrix::on_pushButton_sum_clicked()
{
    ui->display->setText("");
    matrix_t mat1, mat2, result;
    int m1 = ui->lineEdit_m1->text().toInt();
    int n1 = ui->lineEdit_n1->text().toInt();
    s21_create_matrix(m1, n1, &mat1);

    QString input_str1 = ui->lineEdit_arr1->text();
    QStringList input_arr1 = input_str1.split(" ", Qt::SkipEmptyParts);
     for (int i = 0, k = 0; i < m1 && k < m1*n1;
           ++i) {
        for (int j = 0; j < n1; ++j, ++k) {
          mat1.matrix[i][j] = input_arr1[k].toDouble();
        }
      }
     int m2 = ui->lineEdit_m2->text().toInt();
     int n2 = ui->lineEdit_n2->text().toInt();
     s21_create_matrix(m2, n2, &mat2);

     QString input_str2 = ui->lineEdit_arr2->text();
     QStringList input_arr2 = input_str2.split(" ", Qt::SkipEmptyParts);
      for (int i = 0, k = 0; i < m1 && k < m2*n2;
            ++i) {
         for (int j = 0; j < n2; ++j, ++k) {
           mat2.matrix[i][j] = input_arr2[k].toDouble();
         }
       }
    if (s21_sum_matrix(&mat1, &mat2, &result) < 1) {
            print_matrix_qt(&result);
    } else {
        to_display = QString("incorrect data");
    }
    ui->display->setText("A + B\n");
    ui->display->setText(ui->display->text() + to_display);

   s21_remove_matrix(&mat1);
   s21_remove_matrix(&mat2);
   s21_remove_matrix(&result);
   to_display = "";
}


void Matrix::on_pushButton_sub_clicked()
{
    ui->display->setText("");
    matrix_t mat1, mat2, result;
    int m1 = ui->lineEdit_m1->text().toInt();
    int n1 = ui->lineEdit_n1->text().toInt();
    s21_create_matrix(m1, n1, &mat1);

    QString input_str1 = ui->lineEdit_arr1->text();
    QStringList input_arr1 = input_str1.split(" ", Qt::SkipEmptyParts);
     for (int i = 0, k = 0; i < m1 && k < m1*n1;
           ++i) {
        for (int j = 0; j < n1; ++j, ++k) {
          mat1.matrix[i][j] = input_arr1[k].toDouble();
        }
      }
     int m2 = ui->lineEdit_m2->text().toInt();
     int n2 = ui->lineEdit_n2->text().toInt();
     s21_create_matrix(m2, n2, &mat2);

     QString input_str2 = ui->lineEdit_arr2->text();
     QStringList input_arr2 = input_str2.split(" ", Qt::SkipEmptyParts);
      for (int i = 0, k = 0; i < m1 && k < m2*n2;
            ++i) {
         for (int j = 0; j < n2; ++j, ++k) {
           mat2.matrix[i][j] = input_arr2[k].toDouble();
         }
       }
    if (s21_sub_matrix(&mat1, &mat2, &result) < 1) {
        print_matrix_qt(&result);
    } else {
        to_display = QString("incorrect data");
    }
    ui->display->setText("A - B\n");
    ui->display->setText(ui->display->text() + to_display);

   s21_remove_matrix(&mat1);
   s21_remove_matrix(&mat2);
   s21_remove_matrix(&result);
   to_display = "";
}


void Matrix::on_pushButton_AC_clicked()
{
    ui->display->setText("");
}


void Matrix::on_pushButton_mult_by_k_clicked()
{
    ui->display->setText("");
    matrix_t mat, result;
    int k = ui->lineEdit_k->text().toInt();
    int m = ui->lineEdit_m1->text().toInt();
    int n = ui->lineEdit_n1->text().toInt();
    s21_create_matrix(m, n, &mat);

    QString input_str = ui->lineEdit_arr1->text();
    QStringList input_arr = input_str.split(" ", Qt::SkipEmptyParts);
     for (int i = 0, k = 0; i < m && k < m*n;
           ++i) {
        for (int j = 0; j < n; ++j, ++k) {
          mat.matrix[i][j] = input_arr[k].toDouble();
        }
      }
     if (s21_mult_number(&mat, k, &result) < 1) {
        print_matrix_qt(&result);
     } else {
         to_display = QString("incorrect data");
     }
     ui->display->setText("A * k\n");
     ui->display->setText(ui->display->text() + to_display);

    s21_remove_matrix(&mat);
    s21_remove_matrix(&result);
    to_display = "";
}


void Matrix::on_pushButton_mult_clicked()
{
    ui->display->setText("");
    matrix_t mat1, mat2, result;
    int m1 = ui->lineEdit_m1->text().toInt();
    int n1 = ui->lineEdit_n1->text().toInt();
    s21_create_matrix(m1, n1, &mat1);

    QString input_str1 = ui->lineEdit_arr1->text();
    QStringList input_arr1 = input_str1.split(" ", Qt::SkipEmptyParts);
     for (int i = 0, k = 0; i < m1 && k < m1*n1;
           ++i) {
        for (int j = 0; j < n1; ++j, ++k) {
          mat1.matrix[i][j] = input_arr1[k].toDouble();
        }
      }
     int m2 = ui->lineEdit_m2->text().toInt();
     int n2 = ui->lineEdit_n2->text().toInt();
     s21_create_matrix(m2, n2, &mat2);

     QString input_str2 = ui->lineEdit_arr2->text();
     QStringList input_arr2 = input_str2.split(" ", Qt::SkipEmptyParts);
      for (int i = 0, k = 0; i < m1 && k < m2*n2;
            ++i) {
         for (int j = 0; j < n2; ++j, ++k) {
           mat2.matrix[i][j] = input_arr2[k].toDouble();
         }
       }
    if (s21_mult_matrix(&mat1, &mat2, &result) < 1) {
        print_matrix_qt(&result);
    } else {
        to_display = QString("incorrect data");
    }
    ui->display->setText("A * B\n");
    ui->display->setText(ui->display->text() + to_display);
   s21_remove_matrix(&mat1);
   s21_remove_matrix(&mat2);
   s21_remove_matrix(&result);
   to_display = "";
}


void Matrix::on_pushButton_eq_clicked()
{
    ui->display->setText("");
    matrix_t mat1, mat2;
    int m1 = ui->lineEdit_m1->text().toInt();
    int n1 = ui->lineEdit_n1->text().toInt();
    s21_create_matrix(m1, n1, &mat1);

    QString input_str1 = ui->lineEdit_arr1->text();
    QStringList input_arr1 = input_str1.split(" ", Qt::SkipEmptyParts);
     for (int i = 0, k = 0; i < m1 && k < m1*n1;
           ++i) {
        for (int j = 0; j < n1; ++j, ++k) {
          mat1.matrix[i][j] = input_arr1[k].toDouble();
        }
      }
     int m2 = ui->lineEdit_m2->text().toInt();
     int n2 = ui->lineEdit_n2->text().toInt();
     s21_create_matrix(m2, n2, &mat2);

     QString input_str2 = ui->lineEdit_arr2->text();
     QStringList input_arr2 = input_str2.split(" ", Qt::SkipEmptyParts);
      for (int i = 0, k = 0; i < m1 && k < m2*n2;
            ++i) {
         for (int j = 0; j < n2; ++j, ++k) {
           mat2.matrix[i][j] = input_arr2[k].toDouble();
         }
       }

    if (s21_eq_matrix(&mat1, &mat2)) {
        to_display = QString("equal");
    } else {
        to_display = QString("not equal");
    }
    ui->display->setText(ui->display->text() + to_display);
   s21_remove_matrix(&mat1);
   s21_remove_matrix(&mat2);
   to_display = "";
}


void Matrix::on_pushButton_det_clicked()
{
    ui->display->setText("");
    matrix_t mat;
    double det = 0.0;
    int m = ui->lineEdit_m1->text().toInt();
    int n = ui->lineEdit_n1->text().toInt();
    s21_create_matrix(m, n, &mat);

    QString input_str = ui->lineEdit_arr1->text();
    QStringList input_arr = input_str.split(" ", Qt::SkipEmptyParts);
     for (int i = 0, k = 0; i < m && k < m*n;
           ++i) {
        for (int j = 0; j < n; ++j, ++k) {
          mat.matrix[i][j] = input_arr[k].toDouble();
        }
      }
     if (s21_determinant(&mat, &det)) {
         to_display = QString("incorrect data");
     } else {
         to_display = QString::number(det, 'g', 7);
     }
     ui->display->setText("|A|\n");
     ui->display->setText(ui->display->text() + to_display);
    s21_remove_matrix(&mat);
    to_display = "";
}


void Matrix::on_pushButton_inverse_clicked()
{
    ui->display->setText("");
    matrix_t mat, result;
    int m = ui->lineEdit_m1->text().toInt();
    int n = ui->lineEdit_n1->text().toInt();
    s21_create_matrix(m, n, &mat);

    QString input_str = ui->lineEdit_arr1->text();
    QStringList input_arr = input_str.split(" ", Qt::SkipEmptyParts);
     for (int i = 0, k = 0; i < m && k < m*n;
           ++i) {
        for (int j = 0; j < n; ++j, ++k) {
          mat.matrix[i][j] = input_arr[k].toDouble();
        }
      }
     if (s21_inverse_matrix(&mat, &result) < 1) {
        print_matrix_qt(&result);
     } else {
         to_display = QString("incorrect data");
     }
     ui->display->setText("inverse matrix\n");
     ui->display->setText(ui->display->text() + to_display);
    s21_remove_matrix(&mat);
    s21_remove_matrix(&result);
    to_display = "";
}

void Matrix::on_pushButton_compliments_clicked()
{
    ui->display->setText("");
    matrix_t mat, result;
    int m = ui->lineEdit_m1->text().toInt();
    int n = ui->lineEdit_n1->text().toInt();
    s21_create_matrix(m, n, &mat);

    QString input_str = ui->lineEdit_arr1->text();
    QStringList input_arr = input_str.split(" ", Qt::SkipEmptyParts);
     for (int i = 0, k = 0; i < m && k < m*n;
           ++i) {
        for (int j = 0; j < n; ++j, ++k) {
          mat.matrix[i][j] = input_arr[k].toDouble();
        }
      }
     if (s21_calc_complements(&mat, &result) < 1) {
        print_matrix_qt(&result);
     } else {
         to_display = QString("incorrect data");
     }
     ui->display->setText("matrix of algebraic complements\n");
     ui->display->setText(ui->display->text() + to_display);
    s21_remove_matrix(&mat);
    s21_remove_matrix(&result);
    to_display = "";
}
