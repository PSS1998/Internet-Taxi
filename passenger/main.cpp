#include "mainwindow.h"
#include <QApplication>

#include <string>
#include "client_socket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("passenger");
    std::string ip = "127.0.0.1";
    std::string port = "4000";
    ClientSocket socket_temp(ip, Tools::mystoi(port));
    w.socket = &socket_temp;

    w.show();

    return a.exec();
}
