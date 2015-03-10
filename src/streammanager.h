#ifndef STREAMMANAGER_H
#define STREAMMANAGER_H
#include <QObject>
class StreamManager : public QObject
{
    Q_OBJECT
public:
    explicit StreamManager(QObject *parent = 0);
    Q_INVOKABLE void play();
};

#endif // STREAMMANAGER_H
