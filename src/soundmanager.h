#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QtMultimedia>
#include <QMediaPlayer>

class SoundManager : public QObject
{
    Q_OBJECT
public:
    explicit SoundManager(QObject *parent = 0);
public slots:
    void someFancyReactionSlot(QNetworkReply*);
private:
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *playlist;
    QString BASE_ADDRESS;
    QString BASE_ADDRESS_V2;
    QString BASE_QUERY;
    QNetworkAccessManager *infinitePlayManager;
    void initializePlayerAndPlayList();
    void initializeWebStuff();
    void followRedirect(QNetworkReply*);
    void play(QString, int);

signals:
    void pausing();
    void playing();
    void stopping();
};

#endif // PLAYER_H
