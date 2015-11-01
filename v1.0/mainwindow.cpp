#include "mainwindow.h"

#include <QDesktopServices>
#include <QMessageBox>


cMainWindow::cMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cMainWindow)
{
    ui->setupUi(this);
    listener = new cListener(this);

    add_dialog = new cAddDialog(this);
}

cMainWindow::~cMainWindow()
{
    delete add_dialog;
    delete listener;
    delete ui;
}

void cMainWindow::closeEvent(QCloseEvent *event)
{
    showAbout();
    event->accept();
}

Ui_cMainWindow *cMainWindow::GetWidget()
{
    return ui;
}

void cMainWindow::showAbout()
{
    QMessageBox about(this);
    about.setIcon(QMessageBox::Information);
    about.setText("jQTimer V1.0\nVendor: JAVAVIRYS\t\t");
    about.setInformativeText("http://java-virys.narod.ru");
    about.setStandardButtons(QMessageBox::Help | QMessageBox::Ok);
    about.setDefaultButton(QMessageBox::Help);
    int ret=about.exec();
    switch(ret)
    {
    case QMessageBox::Help:
            QDesktopServices::openUrl(QUrl("http://java-virys.narod.ru/"));
        break;
    }
}
