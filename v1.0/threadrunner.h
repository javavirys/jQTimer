#ifndef THREADRUNNER_H
#define THREADRUNNER_H

#include <QThread>

#include <QTime>

class cThreadRunner : public QThread
{
    Q_OBJECT
public:
    cThreadRunner(const QTime &_startTime,QObject *parent = 0);
    cThreadRunner(const cThreadRunner &_cpyObj);
    ~cThreadRunner();
    qint64 getID()const;
    bool getState()const;
    void setID(qint64 _newid);
    void setState(bool _state);

    bool operator ==(const cThreadRunner &rObj);
    bool operator ==(const cThreadRunner *rObj);

    bool operator !=(const cThreadRunner &rObj);
    bool operator !=(const cThreadRunner *rObj);

protected:
    void run() Q_DECL_OVERRIDE;
private:
    QTime *time;
    bool isRun;
    qint64 id;
signals:
    void on_ThreadStarted(const cThreadRunner *_runner, const QTime & _time);
    void on_ThreadProgress(const cThreadRunner *_runner, const QTime & _time);
    void on_ThreadFinished(const cThreadRunner *_runner, const QTime & _time);
    void on_ThreadError(const cThreadRunner *_runner, const QString &_error);

};

#endif // THREADRUNNER_H
