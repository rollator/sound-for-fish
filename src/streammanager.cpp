#include "streammanager.h"
#include <QMediaPlayer>
#include <QtMultimedia>


StreamManager::StreamManager(QObject *parent): QObject(parent)
{
    player = new QMediaPlayer;
}

QMediaPlayer *player;

 void StreamManager::play()
{
    player->setMedia(QUrl("http://yp.shoutcast.com/sbin/tunein-station.m3u?id=914897"));
    player->setVolume(100);
    player->play();
}
 void StreamManager::pause()
{
    player->pause();
}
 void StreamManager::stop()
{
    player->stop();
}
