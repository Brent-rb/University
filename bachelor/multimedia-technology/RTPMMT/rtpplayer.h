#ifndef RTPPLAYER_H
#define RTPPLAYER_H
#include <QThread>
#include <mutex>
#include "RTPSyncer.h"
#include "mainwindow.h"

class RTPPlayer: public QThread
{
    Q_OBJECT
private:
    virtual void run();
public:
    RTPPlayer(MainWindow* window, RTPSyncer* syncer);
    void cancel();
    bool isCancelled();

private:
    MainWindow* $mainWindow;
    RTPSyncer* $syncer;
    QMutex $waitMutex;
    QWaitCondition $condition;

    bool $cancelled = false;
    std::mutex $mutex;

    qint64 $lastPlayTime = 0;

signals:
    void playFrame(QImage* image, uint8_t* data);

public slots:
    void wake();
};

#endif // RTPPLAYER_H
