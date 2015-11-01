#include "listener.h"

#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSound>

#include "adddialog.h"

cListener::cListener(QObject *parent) :
    QObject(parent)
{
    wnd = static_cast <cMainWindow* >(parent);

    dialog = new cAddDialog(wnd);
    dialog->setModal(true);

    QObject::connect(wnd->GetWidget()->menuFile,SIGNAL(triggered(QAction*)),this,
                     SLOT(menu_selected(QAction*)));
    QObject::connect(wnd->GetWidget()->menuHelp,SIGNAL(triggered(QAction*)),this,
                     SLOT(menu_selected(QAction*)));
    QObject::connect(dialog,SIGNAL(on_Accepted(QTime)),this,
                     SLOT(dialog_accepted(QTime)));

}

cListener::~cListener()
{
    delete dialog;
}

void cListener::menu_selected(QAction *action)
{
    if(action == wnd->GetWidget()->actionQuit)
    {
        wnd->close();
    }else if(action == wnd->GetWidget()->actionNew)
    {
        dialog->show();
    }else if(action == wnd->GetWidget()->actionClose)
    {
        if(wnd->GetWidget()->tabsWidget->currentIndex() == -1) //если нет выбранной вкладки
            return;                 //выходим
        if(veTimers[wnd->GetWidget()->tabsWidget->currentIndex()]->getState())
        {
            veTimers[wnd->GetWidget()->tabsWidget->currentIndex()]->setState(false);//просим поток остановится
            veTimers[wnd->GetWidget()->tabsWidget->currentIndex()]->wait();//ждем завершения выполнения потока
        }

        delete veTimerLabels[wnd->GetWidget()->tabsWidget->currentIndex()]; //удаляем
        veTimerLabels.remove(wnd->GetWidget()->tabsWidget->currentIndex()); //

        delete veTimers[wnd->GetWidget()->tabsWidget->currentIndex()];//освобождаем память под объект
        veTimers.remove(wnd->GetWidget()->tabsWidget->currentIndex());//удаляем с вектора пустой указатель
        wnd->GetWidget()->tabsWidget->removeTab(wnd->GetWidget()->
                                                tabsWidget->currentIndex());//удаляем вкладку

    }else if(action == wnd->GetWidget()->actionQT){
        QMessageBox::aboutQt(wnd,"jQTimer");
    }else if(action == wnd->GetWidget()->actionAbout)
    {
        wnd->showAbout();
    }
}

void cListener::timer_start(const cThreadRunner *_runner, const QTime &_time)
{
    qDebug("timer_start");
}

void cListener::timer_progress(const cThreadRunner *_runner, const QTime &_time)
{
    for(int i = 0; i < wnd->GetWidget()->tabsWidget->count(); i++)
    {
        if(*veTimers[i] == *_runner)
            veTimerLabels[i]->setText(_time.toString("hh:mm:ss"));
    }

    qDebug("timer_progress");
}

void cListener::timer_finish(const cThreadRunner *_runner, const QTime &_time)
{
    if( _time.toString("hh:mm:ss") != "00:00:00" )
    {
        qDebug("cListener::timer_finish:break");
        return;
    }
    qDebug("cListener::timer_finish:finish");

    //TODO Здесь находится оповещание о конце времени
    QSound::play(":sounds/vibrate");

    QMessageBox::about(wnd,"Timer","time is over!!!");
}

void cListener::dialog_accepted(const QTime &_time)
{

    QWidget *widget = new QWidget(wnd->GetWidget()->tabsWidget);
    QFormLayout *layout = new QFormLayout(widget);
    qDebug(_time.toString("hh:mm:ss").toStdString().c_str());
    QLabel *watch_timer = new QLabel(_time.toString("hh:mm:ss"));
    veTimerLabels.append(watch_timer);

    layout->addRow("Timer:",watch_timer);
    wnd->GetWidget()->tabsWidget->addTab(widget,
                                         QString("Timer %1").arg(wnd->GetWidget()->tabsWidget->count()));

    cThreadRunner *runner = new cThreadRunner(_time,widget);
    //connect(runner, &cThreadRunner::finished,
    //        runner, &QObject::deleteLater); //нужно для автоматического удаления
    connect(runner,&cThreadRunner::on_ThreadStarted,
            this,&cListener::timer_start);
    connect(runner,SIGNAL(on_ThreadProgress(const cThreadRunner*,QTime)),
            this,SLOT(timer_progress(const cThreadRunner*,QTime)));
    connect(runner,SIGNAL(on_ThreadFinished(const cThreadRunner*,QTime)),
            this,SLOT(timer_finish(const cThreadRunner*,QTime)));

    runner->start();
    veTimers.append(runner);
}
