#include "streamManager.h"
#include <QMediaPlayer>
#include <QtMultimedia>


StreamManager::StreamManager(QObject *parent): QObject(parent)
{
	player = new QMediaPlayer;
    playlist = new QMediaPlaylist;
    player->setPlaylist(playlist);
    player->setVolume(100);
    CLIENT_ID = "21dfb02f29743e4b6b2b27b3c9c3483b";
	BASE_ADDRESS = "http://api.soundcloud.com";
}


void StreamManager::play()
{
	player->play();
}
void StreamManager::playSearchItem(int index)
{
    QString url = searchResults.takeAt(index).toObject()["stream_url"].toString();
    player->setMedia(QUrl(url+"?client_id="+CLIENT_ID));
    playlist->clear();
    player->play();
}
void StreamManager :: addQueueSearchItem(int index)
{
    QString url = searchResults.takeAt(index).toObject()["stream_url"].toString();
    playlist->addMedia((QUrl(url+"?client_id="+CLIENT_ID)));
    player->play();
}

void StreamManager::next(){
    playlist->next();
}
bool StreamManager::paused(){
    //return (player->State == QMediaPlayer::PausedState);
    return true;
}

void StreamManager::pause()
{
	player->pause();
}
void StreamManager::stop()
{
	player->stop();
    playlist->clear();
}
void StreamManager :: search ( const QString &searchString)
{
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)),
	        this, SLOT(reactSearch(QNetworkReply*)));
	QString client_id_param = "&client_id=" + CLIENT_ID;
	manager->get(QNetworkRequest(QUrl(BASE_ADDRESS + "/tracks?q=" + searchString + client_id_param)));
}
void StreamManager :: followRedirect(QNetworkReply *reply)
{
	QUrl newUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
	qDebug() << "redirected from " + reply->url().toString() + " to " + newUrl.toString();
	QNetworkRequest newRequest(newUrl);
	manager->get(newRequest);
	return;
}

void StreamManager :: reactSearch (QNetworkReply *reply)
{
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (statusCode == 302)
	{
		followRedirect(reply);
		return;
	}
    if (statusCode==200)
	{
		QString strReply = reply->readAll();
		QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
		searchResults = jsonResponse.array(); //saved as QJsonArray
		emit searchDone();
		reply->deleteLater();
	}
	else
	{
        qDebug() << "We experienced an error searching.";
        qDebug() << "Statuscode: " << statusCode;
	}

	return;
}
QStringList StreamManager :: tracks()
{
    QStringList strList;
    for(int i=0; i<searchResults.size(); i++)
    {
        strList << searchResults.takeAt(i).toObject()["title"].toString();
    }
    return strList;
}
