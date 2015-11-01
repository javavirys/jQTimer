#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

#include "adddialog.h"

#include "listener.h"

#include "ui_cmainwindow.h"

namespace Ui {
class cMainWindow;
}

class cMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit cMainWindow(QWidget *parent = 0);
    ~cMainWindow();

    void closeEvent(QCloseEvent *event);
    void showAbout();


    Ui_cMainWindow *GetWidget();
    class cListener *listener;
private:
    Ui::cMainWindow *ui;
    class cAddDialog *add_dialog;
};

#endif // CMAINWINDOW_H
