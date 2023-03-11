#include "fileprogressbar.h"
#include "ui_fileprogressbar.h"

FileProgressBar::FileProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileProgressBar)
{
    ui->setupUi(this);
}

FileProgressBar::~FileProgressBar()
{
    delete ui;
}
