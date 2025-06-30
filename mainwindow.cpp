#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug";

double firstNumber;
bool isTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Calculator");
    this->setFixedSize(this->size().width(), this->size().height());
    this->setStyleSheet("background: #fff;");

    connect(ui->btn_0, &QPushButton::released , this, &MainWindow::digit_press);
    connect(ui->btn_1, &QPushButton::released , this, &MainWindow::digit_press);
    connect(ui->btn_2, &QPushButton::released , this, &MainWindow::digit_press);
    connect(ui->btn_3, &QPushButton::released , this, &MainWindow::digit_press);
    connect(ui->btn_4, &QPushButton::released , this, &MainWindow::digit_press);
    connect(ui->btn_5, &QPushButton::released , this, &MainWindow::digit_press);
    connect(ui->btn_6, &QPushButton::released , this, &MainWindow::digit_press);
    connect(ui->btn_7, &QPushButton::released , this, &MainWindow::digit_press);
    connect(ui->btn_8, &QPushButton::released , this, &MainWindow::digit_press);
    connect(ui->btn_9, &QPushButton::released , this, &MainWindow::digit_press);

    connect(ui->PlusMinus_btn, &QPushButton::released, this, &MainWindow::on_unary_btns_released);
    connect(ui->Percent_btn, &QPushButton::released, this, &MainWindow::on_unary_btns_released);

    connect(ui->Equal_btn, &QPushButton::released, this, &MainWindow::on_equal_btn_released);

    connect(ui->Plus_btn, &QPushButton::released, this, &MainWindow::on_operator_btns_released);
    connect(ui->Subt_btn, &QPushButton::released, this, &MainWindow::on_operator_btns_released);
    connect(ui->Divid_btn, &QPushButton::released, this, &MainWindow::on_operator_btns_released);
    connect(ui->Multip_btn, &QPushButton::released, this, &MainWindow::on_operator_btns_released);

    ui->Plus_btn->setCheckable(true);
    ui->Subt_btn->setCheckable(true);
    ui->Divid_btn->setCheckable(true);
    ui->Multip_btn->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_press()
{
    QPushButton* button = (QPushButton*) sender();

    double numberLabel;
    QString newLabel;

    if((ui->Plus_btn->isChecked() || ui->Subt_btn->isChecked()
    || ui->Multip_btn->isChecked() || ui->Divid_btn->isChecked()) && !isTypingSecondNumber) {
        numberLabel = (button->text()).toDouble();
        newLabel = QString::number(numberLabel, 'g', 15);
    } else {
        if(ui->label->text().contains(".") && button->text() == "0") {
            newLabel = ui->label->text() + button->text();
        } else {
            numberLabel = (ui->label->text() + button->text()).toDouble();
            newLabel = QString::number(numberLabel, 'g', 15);
        }
    }

    ui->label->setText(newLabel);
}

void MainWindow::on_Decimal_btn_released()
{
    if(ui->label->text().contains(".")) return;
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::on_unary_btns_released()
{
    QPushButton* button = (QPushButton*) sender();
    double numberLabel;
    QString newLabel;

    if(button->text() == "+/-") {
        numberLabel = ui->label->text().toDouble();
        numberLabel = numberLabel * -1;
        newLabel = QString::number(numberLabel, 'g', 15);

        ui->label->setText(newLabel);
    }

    if(button->text() == "%") {
        numberLabel = ui->label->text().toDouble();
        numberLabel = numberLabel * 0.01;
        newLabel = QString::number(numberLabel, 'g', 15);

        ui->label->setText(newLabel);
    }
}

void MainWindow::on_operator_btns_released()
{
    QPushButton* button = (QPushButton*) sender();

    firstNumber = ui->label->text().toDouble();
    button->setChecked(true);
}

void MainWindow::on_equal_btn_released()
{
    double secondNumber = ui->label->text().toDouble();
    double result;
    QString newLabel;

    if(ui->Plus_btn->isChecked()) {
        result = firstNumber + secondNumber;
        newLabel = QString::number(result, 'g', 15);

        ui->label->setText(newLabel);
        ui->Plus_btn->setChecked(false);
    }

    else if(ui->Subt_btn->isChecked()) {
        result = firstNumber - secondNumber;
        newLabel = QString::number(result, 'g', 15);

        ui->label->setText(newLabel);
        ui->Subt_btn->setChecked(false);
    }

    else if(ui->Multip_btn->isChecked()) {
        result = firstNumber * secondNumber;
        newLabel = QString::number(result, 'g', 15);

        ui->label->setText(newLabel);
        ui->Multip_btn->setChecked(false);
    }

    else if(ui->Divid_btn->isChecked()) {
        result = firstNumber / secondNumber;
        newLabel = QString::number(result, 'g', 15);

        ui->label->setText(newLabel);
        ui->Divid_btn->setChecked(false);
    }

    isTypingSecondNumber = false;
}


void MainWindow::on_Clear_btn_released()
{
    ui->Plus_btn->setChecked(false);
    ui->Subt_btn->setChecked(false);
    ui->Divid_btn->setChecked(false);
    ui->Multip_btn->setChecked(false);

    isTypingSecondNumber = false;

    ui->label->setText("0");
}

