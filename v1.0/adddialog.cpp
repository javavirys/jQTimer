#include "adddialog.h"
#include "ui_adddialog.h"

cAddDialog::cAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cAddDialog)
{
    ui->setupUi(this);
    wnd = static_cast<cMainWindow *> (parent);

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accepted()));
}

cAddDialog::~cAddDialog()
{
    delete ui;
}

void cAddDialog::accepted()
{
    qDebug("accept");

    emit on_Accepted(ui->timeTimeEdit->time());
}
