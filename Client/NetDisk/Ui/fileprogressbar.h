#ifndef FILEPROGRESSBAR_H
#define FILEPROGRESSBAR_H

#include <QWidget>

namespace Ui {
class FileProgressBar;
}

class FileProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit FileProgressBar(QWidget *parent = nullptr);
    ~FileProgressBar();

private:
    Ui::FileProgressBar *ui;
};

#endif // FILEPROGRESSBAR_H
