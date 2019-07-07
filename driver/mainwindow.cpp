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
    ui->frame_10->hide();
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

void MainWindow::on_login_page_clicked()
{
    statusBar()->showMessage("");
    ui->frame->hide();
    ui->frame_3->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    statusBar()->showMessage("");
    QString username;
    username = ui->lineEdit->text();
    QString password;
    password = ui->lineEdit_2->text();
    QString spaceship_number;
    spaceship_number = ui->lineEdit_3->text();
    QString spaceship_model;
    spaceship_model = ui->lineEdit_8->text();
    QString production_year;
    production_year = ui->lineEdit_9->text();
    QString spaceship_color;
    spaceship_color = ui->lineEdit_10->text();
    bool VIP;
    if(ui->checkBox->isChecked()){
        VIP = true;
    }
    else{
        VIP = false;
    }
    std::string model = spaceship_model.toUtf8().constData();
    std::string year = production_year.toUtf8().constData();
    std::string color = spaceship_color.toUtf8().constData();
    std::string vehicle_num = spaceship_number.toUtf8().constData();
    std::string pass = password.toUtf8().constData();
    std::string line = username.toUtf8().constData();
    line += " ";
    line += "register_driver";
    line += " ";
    line += pass;
    line += " ";
    line += vehicle_num;
    line += " ";
    line += model;
    line += " ";
    line += year;
    line += " ";
    line += color;
    if(VIP){
        line += " ";
        line += "VIP";
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
    line += "show_trip_requests";
    socket->send(line);
    std::string receive = socket->receive();
    QString requests = QString::fromStdString(receive);
    ui->textBrowser->setText(requests);
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
    QString user;
    user = ui->lineEdit_6->text();
    std::string user_passenger = user.toUtf8().constData();
    std::string line = username;
    line += " ";
    line += "accept_trip_request";
    line += " ";
    line += user_passenger;
    socket->send(line);
    std::string receive = socket->receive();
    if(receive != ""){
        QString qstr = QString::fromStdString(receive);
        statusBar()->showMessage(qstr);
    }
    else{
        statusBar()->showMessage("accept trip request success");
        ui->frame_10->show();
        ui->frame_5->hide();
        update_fixed();
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
    ui->label_12->setText(request);
    ui->label_20->setText(request);
    ui->label_24->setText(request);
    QString user = QString::fromStdString(username);
    ui->label_4->setText(user);
    ui->label_6->setText(user);
    ui->label_9->setText(user);
    ui->label_11->setText(user);
    ui->label_17->setText(user);
    ui->label_19->setText(user);
    ui->label_23->setText(user);
}

void MainWindow::on_pushButton_16_clicked()
{
    statusBar()->showMessage("");
    ui->frame_4->show();
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
    line += "set_status";
    if(ui->checkBox_2->isChecked()){
        line += " ";
        line += "available";
        QString address;
        address = ui->lineEdit_11->text();
        std::string location = address.toUtf8().constData();
        line += " ";
        line += location;
    }
    else {
        line += " ";
        line += "unavailable";
    }
    socket->send(line);
    receive = socket->receive();
    if(receive != ""){
        update_fixed();
        statusBar()->showMessage("");
    }
}

void MainWindow::on_pushButton_22_clicked()
{
    statusBar()->showMessage("");
    std::string line = username;
    line += " ";
    line += "arrived";
    socket->send(line);
    std::string receive = socket->receive();
    ui->frame_12->show();
    ui->frame_10->hide();
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
    line += "end_trip";
    socket->send(line);
    std::string receive = socket->receive();
    ui->frame_4->show();
    ui->frame_12->hide();
    update_fixed();
}
