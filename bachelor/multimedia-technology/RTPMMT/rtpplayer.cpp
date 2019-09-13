#include "rtpplayer.h"
#include "RTPFrame.h"

RTPPlayer::RTPPlayer(MainWindow* window, RTPSyncer* syncer): $mainWindow(window), $syncer(syncer), QThread()
{

}

void RTPPlayer::cancel() {
    $mutex.lock();
    $cancelled = true;
    $mutex.unlock();
}

bool RTPPlayer::isCancelled() {
    bool toRet;

    $mutex.lock();
    toRet = $cancelled;
    $mutex.unlock();

    return toRet;
}

void RTPPlayer::run() {
    //qDebug() << "Running!";
    $cancelled = false;
    $lastPlayTime = 0;
    while(!isCancelled()) {
        //qDebug() << "Loop";
        RTPFrame* frame = $syncer->pop();
        //qDebug() << "After pop";
        if(frame != nullptr) {
            qint64 frameTime = frame->getPlayTime();

            qDebug() << frameTime << " < " << QDateTime::currentMSecsSinceEpoch();
            if(frameTime < QDateTime::currentMSecsSinceEpoch() && frameTime >= $lastPlayTime) {
                qDebug() << "Play Frame";
                uint32_t timestamp = frame->getTimestamp();
                uint8_t* data = frame->getRGB(320, 240);
                QImage* image = new QImage(data, 320, 240, QImage::Format::Format_RGB32);
                playFrame(image, data);
                $lastPlayTime = frameTime;
                $syncer->deleteFrame(frame);
                $syncer->removeUnreadyFrames(timestamp);
            }
            else if (frameTime < QDateTime::currentMSecsSinceEpoch() && frameTime < $lastPlayTime) {
                qDebug() << "Delete";
                $syncer->deleteFrame(frame);
            }
            else {
                $syncer->push(frame);
            }
        }

        $waitMutex.lock();
        //qDebug() << "Sleep";
        $condition.wait(&$waitMutex, 50);
        $waitMutex.unlock();
        //qDebug() << "After sleep";
    }
    qDebug() << "End";
}

void RTPPlayer::wake() {
    $condition.wakeAll();
}
