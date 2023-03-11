#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QPushButton>
#include <QRegExp>
#include <iostream>
#include <QMessageBox>
#include "FtpConnection/FtpConnection.h"

asio::io_context service(1);
QString phraseIP(const QString& str)
{
    //检验IP是否是有效的正则
    QRegExp exp("((25[0-5])|(2[0-4]\\d)|(1\\d\\d)|([1-9]\\d)|\\"
    "d)(\\.((25[0-5])|(2[0-4]\\d)|(1\\d\\d)|([1-9]\\d)|\\d)){3}");

    auto trimmedStr=str.trimmed();
    if(exp.exactMatch(trimmedStr))
    {
        return trimmedStr;
    }
    else
        return QString();
}
QString phrasePort(const QString& str)

{
    bool ok;
    auto trimmedStr=str.trimmed();
    trimmedStr.toUShort(&ok);
    if(ok)
        return trimmedStr;
    else
        return QString();
}


MainWindow::MainWindow(QWidget* parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("网盘");


    //登录键按下
    connect(ui->login_b,&QPushButton::clicked,this,[this]{
        //检测IP和端口是否有效
        QString IP=phraseIP(ui->ip->text());
        QString port=phrasePort(ui->port->text());
        if(IP.isEmpty()||port.isEmpty())
        {
            QMessageBox::warning(this,"错误！","IP或端口格式不正确！请重新输入");
            return;
        }

        asio::ip::tcp::endpoint endpoint(asio::ip::make_address(IP.toStdString()),port.toUShort());

        //以IP和端口建立新的Ftp连接
        auto newConnection=new FtpConnection(service);

        //连接创建成功时调用
        connect(newConnection,&FtpConnection::connectOver,this,
                [this](const QString& msg,bool isSucess){
            if(!isSucess)
            {
               QMessageBox::warning(this,"提示",msg);
            }
            else
            {
                auto userName=ui->username->text().trimmed();
                auto passWord=ui->password->text().trimmed();
                this->thisConnection->login(userName,passWord);
            }
        });

        //登录完成时调用,新建一个用户窗口
        connect(newConnection,&FtpConnection::LoginOver,this,
                [this](const QString& msg,bool isSucess){
              QMessageBox::warning(this,"提示",msg);
              if(isSucess)
              {
                  this->fileWindow=new FTPMainWindow(this->thisConnection,this);
                  this->hide();
                  this->fileWindow->show();
              }
        });

        //设置下一个ftp连接
        thisConnection= std::shared_ptr<FtpConnection>(newConnection);

        //尝试连接服务器
        thisConnection->connect(endpoint);
    });


    //退出键按下
    connect(ui->exit_b,&QPushButton::clicked,this,[this]{
        this->close();
        QApplication::exit(0);
    });

    //创建ASIO事件循环线程
    AsioThread* thread=new AsioThread(service);
    thread->setParent(QApplication::instance());

    //连接退出程序时终止ASIO事件循环线程的信号
    connect(this,&MainWindow::endAsioRunThread,thread,[thread](){
        thread->end();
        thread->wait();
    });

    //开启ASIO事件循环线程
    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::closeEvent(QCloseEvent *)
{
    //关闭登录窗口时退出ASIO事件循环线程
    emit endAsioRunThread();
}

void AsioThread::run()
{
    //ASIO事件循环开启
    asio::io_service::work work(service);
    service.run();
}
void AsioThread::end()
{
     //ASIO事件循环停止
    this->service.stop();
}
