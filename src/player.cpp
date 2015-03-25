#include "player.h"
#include <QObject>
#include <QtMultimedia>
#include <QMediaPlayer>

Player::Player(QObject *parent): QObject(parent)
{
    initializePlayerAndPlayList();
    initializeWebStuff();

}
void Player::initializePlayerAndPlayList()
{
    mediaPlayer = new QMediaPlayer;
    playlist = new QMediaPlaylist;
    mediaPlayer->setPlaylist(playlist);
    mediaPlayer->setVolume(100);
    return;
}
void Player::initializeWebStuff()
{
    BASE_ADDRESS = "http://api.soundcloud.com";
    BASE_ADDRESS_V2 = "https://api-v2.soundcloud.com";
    QString client_id = "21dfb02f29743e4b6b2b27b3c9c3483b";
    BASE_QUERY = "client_id="+client_id;
    infinitePlayManager = new QNetworkAccessManager(this);
    connect(infinitePlayManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(someFancyReactionSlot(QNetworkReply*)));
}
void Player::someFancyReactionSlot(QNetworkReply *reply)
{
    return;
}

void Player::play(QString url, int trackID)
{
    mediaPlayer->setMedia(QUrl(url+"?"+BASE_QUERY));
    playlist->clear();
    mediaPlayer->play();
    emit playing();
}
