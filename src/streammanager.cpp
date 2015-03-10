#include "streammanager.h"

class StreamManager : public QObject{

    Q_OBJECT
public:
    Q_INVOKABLE play() const {
        QMediaPlayer *player = new QMediaPlayer;
        player->setMedia(QUrl("http://37.48.81.130:9530/listen.pls"));
        player->setVolume(100);
        player->play();
        return nullptr;
    }


};
