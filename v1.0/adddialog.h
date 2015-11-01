#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class cAddDialog;
}

class cAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit cAddDialog(QWidget *parent = 0);
    ~cAddDialog();

private:
    Ui::cAddDialog *ui;
    class cMainWindow *wnd;
public slots:

private slots:
    void accepted();
signals:
    void on_Accepted(const QTime &_time);
};

#endif // ADDDIALOG_H
