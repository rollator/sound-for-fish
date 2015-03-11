#ifndef STREAMMANAGER_H
#define STREAMMANAGER_H
#include <QObject>
#include <QtMultimedia>
#include <QMediaPlayer>


class StreamManager : public QObject
{
    Q_OBJECT
    QMediaPlayer *player;

public:
    explicit StreamManager(QObject *parent = 0);
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();

};

#endif // STREAMMANAGER_H
