#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <math.h>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>

#include "rpn.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QStandardItemModel *model;
    int idModel;
    rpn Rpn;

public slots:
    void messageError(QString err);

private slots:
    void setFormStyle();
    void dataChangeModel(QModelIndex index);
    void getId(QModelIndex index);
    void on_btn_equal_clicked();
    void on_btn_0_clicked();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_stepen_clicked();
    void on_btn_razdel_clicked();
    void on_btn_umnozh_clicked();
    void on_btn_minus_clicked();
    void on_btn_plus_clicked();
    void on_btn_skob1_clicked();
    void on_btn_skob2_clicked();
    void on_btn_sin_clicked();
    void on_btn_cos_clicked();
    void on_btn_tg_clicked();
    void on_btn_ctg_clicked();
    void on_btn_point_clicked();
    void on_btn_e_clicked();
    void on_btn_Pi_clicked();
    void on_btn_addPer_clicked();
    void on_btn_plusminus_clicked();
    void on_btn_log_clicked();
    void on_btn_skob2_2_clicked();
    void on_btn_skob2_3_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
