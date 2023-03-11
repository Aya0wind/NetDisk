#ifndef FTPMAINWINDOW_H
#define FTPMAINWINDOW_H

#include <QMainWindow>
namespace Ui {
class FTPMainWindow;
}
class FtpConnection;
class FTPMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FTPMainWindow(std::shared_ptr<FtpConnection> connection,QWidget *parent = nullptr);
    ~FTPMainWindow();

private:
    Ui::FTPMainWindow *ui;
    std::shared_ptr<FtpConnection> connection;
};

#endif // FTPMAINWINDOW_H
