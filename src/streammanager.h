#ifndef STREAMMANAGER_H
#define STREAMMANAGER_H
#include <QObject>
#include <QtMultimedia>
#include <QMediaPlayer>


class StreamManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY (NOTIFY searchDone)
    QMediaPlayer *player;
    QString CLIENT_ID;
    QString BASE_ADDRESS;
    QString BASE_ADDRESS_V2;
    QJsonArray searchResults;
    QMediaPlaylist *playlist;
public:
    explicit StreamManager(QObject *parent = 0);
    Q_INVOKABLE QStringList tracks ();
    Q_INVOKABLE void playSearchItem(int index);
    Q_INVOKABLE void addQueueSearchItem(int index);
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void next();
    Q_INVOKABLE void search(const QString &searchString);
    Q_INVOKABLE bool paused();
public slots:
    void reactSearch (QNetworkReply*);
private:
    QString theList;
    QNetworkAccessManager* searchManager;
    void followRedirect(QNetworkReply*);

signals:
    void searchDone();
};

#endif // STREAMMANAGER_H
