#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>
#include "client_socket.h"
#include "tools.h"
#include <sstream>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(500,700);
    ui->frame_2->hide();
    ui->frame_3->hide();
    ui->frame_4->hide();
    ui->frame_5->hide();
    ui->frame_6->hide();
    ui->frame_7->hide();
    ui->frame_8->hide();
    ui->frame_9->hide();
    ui->frame_10->hide();
    ui->frame_11->hide();
    ui->frame_12->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_register_page_clicked()
{
    statusBar()->showMessage("");
    ui->frame->hide();
    ui->frame_2->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    statusBar()->showMessage("");
    ui->frame->hide();
    ui->frame_3->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    statusBar()->showMessage("");
    QString discount_code;
    discount_code = ui->lineEdit->text();
    QString username;
    username = ui->lineEdit->text();
    QString password;
    password = ui->lineEdit_2->text();
    QString phone;
    phone = ui->lineEdit_3->text();
    std::string discount = discount_code.toUtf8().constData();
    std::string tele = phone.toUtf8().constData();
    std::string pass = password.toUtf8().constData();
    std::string line = username.toUtf8().constData();
    line += " ";
    line += "register_passenger";
    line += " ";
    line += pass;
    line += " ";
    line += tele;
    if(discount != ""){
        line += " ";
        line += discount;
    }
    socket->send(line);
    std::string receive = socket->receive();
    if(receive != ""){
        QString qstr = QString::fromStdString(receive);
        statusBar()->showMessage(qstr);
    }
    else{
        statusBar()->showMessage("register success");
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    statusBar()->showMessage("");
    QString username;
    username = ui->lineEdit_4->text();
    QString password;
    password = ui->lineEdit_5->text();
    std::string pass = password.toUtf8().constData();
    std::string line = username.toUtf8().constData();
    line += " ";
    line += "login";
    line += " ";
    line += pass;
    socket->send(line);
    std::string receive = socket->receive();
    if(receive != "1"){
        QString qstr = QString::fromStdString(receive);
        statusBar()->showMessage(qstr);
        if(receive == "0"){
            statusBar()->showMessage("wrong username or password!");
        }
    }
    else{
        statusBar()->showMessage("login success");
        MainWindow::username = username.toUtf8().constData();
        ui->frame_3->hide();
        ui->frame_4->show();
        update_fixed();
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    statusBar()->showMessage("");
    ui->frame->show();
    ui->frame_3->hide();
}

void MainWindow::on_pushButton_8_clicked()
{
    statusBar()->showMessage("");
    ui->frame->show();
    ui->frame_2->hide();
}

void MainWindow::on_pushButton_9_clicked()
{
    statusBar()->showMessage("");
    ui->frame_7->show();
    ui->frame_4->hide();
    update_fixed();
}

void MainWindow::on_pushButton_10_clicked()
{
    statusBar()->showMessage("");
    std::string line = username;
    line += " ";
    line += "get_discount_code";
    socket->send(line);
    std::string receive = socket->receive();
    std::vector <std::string> discount_code(2);
    std::vector <QString> Qdiscount_code(2);
    std::stringstream ss;
    ss.str(receive);
    ss >> discount_code[0];
    ss >> discount_code[1];
    Qdiscount_code[0] = QString::fromStdString(discount_code[0]);
    Qdiscount_code[1] = QString::fromStdString(discount_code[1]);
    ui->label->setText(Qdiscount_code[0]);
    ui->label_2->setText(Qdiscount_code[1]);
    ui->frame_6->show();
    ui->frame_4->hide();
    update_fixed();
}

void MainWindow::on_pushButton_11_clicked()
{
    statusBar()->showMessage("");
    ui->frame_5->show();
    ui->frame_4->hide();
    update_fixed();
}

void MainWindow::on_pushButton_12_clicked()
{
    statusBar()->showMessage("");
    std::string line = username;
    line += " ";
    line += "logout";
    socket->send(line);
    std::string receive = socket->receive();
    ui->frame->show();
    ui->frame_4->hide();
    update_fixed();
}

void MainWindow::on_pushButton_13_clicked()
{
    statusBar()->showMessage("");
    QString amount;
    amount = ui->lineEdit_6->text();
    std::string num_charge = amount.toUtf8().constData();
    std::string line = username;
    line += " ";
    line += "charge_account";
    line += " ";
    line += num_charge;
    socket->send(line);
    std::string receive = socket->receive();
    if(receive != ""){
        QString qstr = QString::fromStdString(receive);
        statusBar()->showMessage(qstr);
    }
    else{
        statusBar()->showMessage("charge success");
    }
    update_fixed();
}

void MainWindow::on_pushButton_14_clicked()
{
    statusBar()->showMessage("");
    ui->frame_4->show();
    ui->frame_5->hide();
    update_fixed();
}

void MainWindow::on_pushButton_15_clicked()
{
    statusBar()->showMessage("");
    ui->frame_4->show();
    ui->frame_6->hide();
    update_fixed();
}

void MainWindow::update_fixed()
{
    std::string line = username;
    line += " ";
    line += "system_time";
    socket->send(line);
    std::string receive = socket->receive();
    QString request = QString::fromStdString(receive);
    ui->label_3->setText(request);
    ui->label_7->setText(request);
    ui->label_10->setText(request);
    ui->label_19->setText(request);
    ui->label_22->setText(request);
    ui->label_25->setText(request);
    ui->label_28->setText(request);
    ui->label_31->setText(request);
    ui->label_34->setText(request);
    QString user = QString::fromStdString(username);
    ui->label_4->setText(user);
    ui->label_6->setText(user);
    ui->label_9->setText(user);
    ui->label_18->setText(user);
    ui->label_21->setText(user);
    ui->label_24->setText(user);
    ui->label_27->setText(user);
    ui->label_30->setText(user);
    ui->label_33->setText(user);
    std::string line2 = username;
    line2 += " ";
    line2 += "get_credit";
    socket->send(line2);
    receive = socket->receive();
    request = QString::fromStdString(receive);
    ui->label_5->setText(request);
    ui->label_8->setText(request);
    ui->label_11->setText(request);
    ui->label_17->setText(request);
    ui->label_20->setText(request);
    ui->label_23->setText(request);
    ui->label_26->setText(request);
    ui->label_29->setText(request);
    ui->label_32->setText(request);
}

void MainWindow::on_pushButton_16_clicked()
{
    statusBar()->showMessage("");
    ui->frame_4->show();
    ui->frame_7->hide();
    update_fixed();
}

void MainWindow::on_pushButton_20_clicked()
{
    statusBar()->showMessage("");
    QString address = ui->textEdit->toPlainText();
    source = address.toUtf8().constData();
    ui->frame_7->show();
    ui->frame_8->hide();
    update_fixed();
    estimate_trip();
}

void MainWindow::on_pushButton_21_clicked()
{
    statusBar()->showMessage("");
    QString address = ui->textEdit_2->toPlainText();
    destinations = address.toUtf8().constData();
    ui->frame_7->show();
    ui->frame_9->hide();
    update_fixed();
    estimate_trip();
}

void MainWindow::estimate_trip()
{
    std::vector<std::string> estimation(2);
    std::string receive;
    std::vector<QString> print(2);
    std::string line = username;
    line += " ";
    line += "estimate_trip";
    if(ui->checkBox->isChecked()){
        line += " ";
        line += "VIP";
    }
    line += " ";
    line += source;
    line += " ";
    line += destinations;
    socket->send(line);
    receive = socket->receive();
    if(receive != ""){
        std::stringstream ss;
        ss.str(receive);
        ss >> estimation[0];
        ss >> estimation[1];
        print[0] = QString::fromStdString(estimation[0]);
        print[1] = QString::fromStdString(estimation[1]);
        ui->label_12->setText(print[0]);
        ui->label_13->setText(print[1]);
        statusBar()->showMessage("");
    }
    else{
        statusBar()->showMessage("not an address!");
    }
}

void MainWindow::on_pushButton_17_clicked()
{
    statusBar()->showMessage("");
    ui->frame_8->show();
    ui->frame_7->hide();
    update_fixed();
}

void MainWindow::on_pushButton_18_clicked()
{
    statusBar()->showMessage("");
    ui->frame_9->show();
    ui->frame_7->hide();
    update_fixed();
}

void MainWindow::on_pushButton_19_clicked()
{
    statusBar()->showMessage("");
    update_fixed();
    std::vector<std::string> estimation(2);
    std::string receive;
    std::vector<QString> print(2);
    std::string line = username;
    line += " ";
    line += "request_trip";
    if(ui->checkBox->isChecked()){
        line += " ";
        line += "VIP";
    }
    line += " ";
    line += source;
    line += " ";
    line += destinations;
    socket->send(line);
    receive = socket->receive();
    if(receive != ""){
        ui->frame_10->show();
        ui->frame_7->hide();
        update_fixed();
        std::stringstream ss;
        ss.str(receive);
        ss >> estimation[0];
        ss >> estimation[1];
        print[0] = QString::fromStdString(estimation[0]);
        print[1] = QString::fromStdString(estimation[1]);
        ui->label_14->setText(print[0]);
        ui->label_15->setText(print[1]);
        statusBar()->showMessage("");
    }
    else{
        statusBar()->showMessage("not an address!");
    }
}

void MainWindow::on_pushButton_22_clicked()
{
    statusBar()->showMessage("");
    std::string line = username;
    line += " ";
    line += "must_rate";
    socket->send(line);
    std::string receive = socket->receive();
    if(receive == ""){
        std::string line = username;
        line += " ";
        line += "cancel_trip_request";
        socket->send(line);
        std::string receive = socket->receive();
        ui->frame_7->show();
        ui->frame_10->hide();
        update_fixed();
    }
    else{
        statusBar()->showMessage("you have to rate the driver first");
    }
}

void MainWindow::on_pushButton_23_clicked()
{
    statusBar()->showMessage("");
    std::string line = username;
    line += " ";
    line += "must_rate";
    socket->send(line);
    std::string receive = socket->receive();
    if(receive == ""){
        std::string line = username;
        line += " ";
        line += "trip_status";
        socket->send(line);
        std::string receive = socket->receive();
        QString print = QString::fromStdString(receive);
        ui->label_16->setText(print);
        ui->frame_11->show();
        ui->frame_10->hide();
        update_fixed();
    }
    else{
        statusBar()->showMessage("you have to rate the driver first");
    }
}

void MainWindow::on_pushButton_24_clicked()
{
    statusBar()->showMessage("");
    ui->frame_10->show();
    ui->frame_11->hide();
    update_fixed();
}

void MainWindow::on_pushButton_25_clicked()
{
    statusBar()->showMessage("");
    ui->frame_12->show();
    ui->frame_10->hide();
    update_fixed();
}

void MainWindow::on_pushButton_26_clicked()
{
    statusBar()->showMessage("");
    std::string line = username;
    line += " ";
    line += "rate_driver";
    line += " ";
    QString rate;
    rate = ui->lineEdit_7->text();
    std::string rating = rate.toUtf8().constData();
    if(rating == "1" || rating == "2" || rating == "3" || rating == "4" || rating == "5" || rating == "6" || rating == "7" || rating == "8" || rating == "9" || rating == "10"){
        line += rating;
        socket->send(line);
        std::string receive = socket->receive();
        ui->frame_4->show();
        ui->frame_12->hide();
        update_fixed();
    }
    else{
        statusBar()->showMessage("please rate between 1 to 10");
    }
}

void MainWindow::on_checkBox_clicked()
{
    update_fixed();
    estimate_trip();
}
