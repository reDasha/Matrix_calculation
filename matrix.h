#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>

extern "C" {
#include "s21_matrix.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class Matrix; }
QT_END_NAMESPACE

class Matrix : public QMainWindow
{
    Q_OBJECT

public:
    Matrix(QWidget *parent = nullptr);
    ~Matrix();
    QString to_display = "";

private slots:
    void on_pushButton_transpose_clicked();
    void print_matrix_qt(matrix_t *A);
    void on_pushButton_sum_clicked();
    void on_pushButton_sub_clicked();
    void on_pushButton_AC_clicked();
    void on_pushButton_mult_by_k_clicked();
    void on_pushButton_mult_clicked();
    void on_pushButton_eq_clicked();
    void on_pushButton_det_clicked();
    void on_pushButton_inverse_clicked();
    void on_pushButton_compliments_clicked();

private:
    Ui::Matrix *ui;
};
#endif // MATRIX_H
