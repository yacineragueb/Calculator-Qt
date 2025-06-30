#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digit_press();
    void on_Decimal_btn_released();
    void on_unary_btns_released();
    void on_operator_btns_released();
    void on_equal_btn_released();
    void on_Clear_btn_released();
};
#endif // MAINWINDOW_H
