#include "ftpmainwindow.h"
#include "ui_ftpmainwindow.h"
#include "FtpConnection/FtpConnection.h"
#include<QDebug>
#include<QTcpSocket>
FTPMainWindow::FTPMainWindow(std::shared_ptr<FtpConnection> connection,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FTPMainWindow),
    connection(connection)
{
    ui->setupUi(this);
    this->setWindowTitle("文件管理");
    ui->filelist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->changeUser,&QPushButton::clicked,this,[this]{
        this->close();
        this->parentWidget()->show();
        this->deleteLater();
    });
    connect(ui->upload,&QPushButton::clicked,this,[this](bool){
        qDebug()<<"upload";
    });
}
FTPMainWindow::~FTPMainWindow()
{
    delete ui;
}
