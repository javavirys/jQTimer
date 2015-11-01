#ifndef LISTENER_H
#define LISTENER_H

#include "mainwindow.h"
#include "threadrunner.h"

#include <QLabel>
#include <QTime>



class cListener : public QObject
{
    Q_OBJECT
public:
    explicit cListener(QObject *parent = 0);
    ~cListener();
private:
    class cMainWindow* wnd;
    class cAddDialog *dialog;
    QVector<cThreadRunner *> veTimers;
    QVector<QLabel *> veTimerLabels;
signals:

public slots:
    void menu_selected(QAction *action);


    void timer_start(const cThreadRunner *_runner, const QTime & _time);
    void timer_progress(const cThreadRunner *_runner, const QTime & _time);
    void timer_finish(const cThreadRunner *_runner, const QTime & _time);

    void dialog_accepted(const QTime &_time);

};

#endif // LISTENER_H
