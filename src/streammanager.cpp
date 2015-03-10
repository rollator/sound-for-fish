#include "streammanager.h"
#include <QMediaPlayer>

#include <QMediaPlayer>

StreamManager::StreamManager(QObject *parent): QObject(parent)
{

}
 void StreamManager::play()
{
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("http://37.48.81.130:9530/listen.pls"));
    player->setVolume(100);
    player->play();
}
