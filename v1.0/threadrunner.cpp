#include "threadrunner.h"

cThreadRunner::cThreadRunner(const QTime &_startTime, QObject *parent) :
    QThread(parent),
    isRun(false)
{
    id = QDateTime::currentDateTime().toMSecsSinceEpoch();//даем ид
    time = new QTime(_startTime);
}

cThreadRunner::cThreadRunner(const cThreadRunner &_cpyObj) :
    isRun(false)
{
    time = _cpyObj.time;
    id = _cpyObj.id;
}

cThreadRunner::~cThreadRunner()
{
    delete time;
    qDebug("cThreadRunner::~cThreadRunner");
}

qint64 cThreadRunner::getID() const
{
    return id;
}

bool cThreadRunner::getState() const
{
    return isRun;
}

void cThreadRunner::setID(qint64 _newid)
{
    id = _newid;
}

void cThreadRunner::setState(bool _state)
{
    isRun = _state;
}

bool cThreadRunner::operator ==(const cThreadRunner &rObj)
{
    if(this->id == rObj.id)
        return true;
    return false;
}

bool cThreadRunner::operator ==(const cThreadRunner *rObj)
{
    return this->operator == (*rObj);
}

bool cThreadRunner::operator !=(const cThreadRunner &rObj)
{
    return false;
}

bool cThreadRunner::operator !=(const cThreadRunner *rObj)
{
    return false;
}

void cThreadRunner::run()
{
    qDebug("cThreadRunner::run() started");
    setState(true);
    QTime _time;
    _time = *time;
    emit on_ThreadStarted(this,_time);
    while(isRun && _time.toString("hh:mm:ss") != "00:00:00"){
        _time = _time.addSecs(-1);
        this->sleep(1);
        emit on_ThreadProgress(this,_time);
    }
    qDebug("cThreadRunner::run() finished");
    emit on_ThreadFinished(this,_time);
}
