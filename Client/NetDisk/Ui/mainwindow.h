#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ftpmainwindow.h>
#include<QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
namespace asio {
    class io_context;
}

class AsioThread:public QThread
{
    Q_OBJECT
public:
    AsioThread(asio::io_context& service)
        :service(service)
    {}
    void run() override;
    void end();
private:
    asio::io_context& service;
    bool isExit=false;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
     void closeEvent(QCloseEvent *event);
signals:
     void endAsioRunThread();
private:
    Ui::MainWindow *ui;
    FTPMainWindow* fileWindow;
    std::shared_ptr<FtpConnection> thisConnection;
};



#endif // MAINWINDOW_H
