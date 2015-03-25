#include "streammanager.h"
#include <QMediaPlayer>
#include <QtMultimedia>
#include "soundmanager.h"

// to get the next played songs when playing a song:
//https://api-v2.soundcloud.com/tracks/188684387/related?anon_user_id=69157178&limit=3&offset=0&linked_partitioning=1&client_id=b45b1aa10f1ac2941910a7f0d10f8e28&app_version=4a3bcba
//when done playing these 3:
// limit = 3, offset =3
//then limit = 3, offset = 6

StreamManager::StreamManager(QObject *parent, SoundManager *myPlay): QObject(parent)
{
    soundy = myPlay;
	player = new QMediaPlayer;
    playlist = new QMediaPlaylist;
    player->setPlaylist(playlist);
    player->setVolume(100);
    searchManager = new QNetworkAccessManager(this);
    connect(searchManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(reactSearch(QNetworkReply*)));
    CLIENT_ID = "21dfb02f29743e4b6b2b27b3c9c3483b";
	BASE_ADDRESS = "http://api.soundcloud.com";
    BASE_ADDRESS_V2 = "https://api-v2.soundcloud.com";
}


void StreamManager::play()
{
	player->play();
}
void StreamManager::playSearchItem(int index)
{
    QString url = searchResults.takeAt(index).toObject()["stream_url"].toString();
    int trackNr = searchResults.takeAt(index).toObject()["id"].toInt();
    playlist->clear();
    playlist->addMedia(QUrl(url+"?client_id="+CLIENT_ID));

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
    if (searchString.size()==0){
        searchResults = QJsonDocument::fromJson("[]").array();
        emit searchDone();
        return;
    }
	QString client_id_param = "&client_id=" + CLIENT_ID;
    QString searchTracksPath = "/search/tracks?";
    QString url = BASE_ADDRESS_V2 + searchTracksPath;
    QString defaultParams = "&facet=genre&limit=10&offset=10";
    QString query = "q=" + searchString + client_id_param + defaultParams;
    searchManager->get(QNetworkRequest(QUrl(url+query)));
}
void StreamManager :: followRedirect(QNetworkReply *reply)
{
	QUrl newUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
	qDebug() << "redirected from " + reply->url().toString() + " to " + newUrl.toString();
	QNetworkRequest newRequest(newUrl);
    searchManager->get(newRequest);
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
//		searchResults = jsonResponse.array(); //in apiv1
        searchResults = jsonResponse.object()["collection"].toArray(); //apiv2
		emit searchDone();
		reply->deleteLater();
	}
	else
	{
        qDebug() << "We experienced an error searching.";
        qDebug() << "Statuscode: " << statusCode;
        qDebug() << reply->request().url().toString();
	}

	return;
}
QStringList StreamManager :: tracks()
{
    QStringList strList;
    if (searchResults.empty()){
        return strList;
    }
    for(int i=0; i<searchResults.size(); i++)
    {
        strList << searchResults.takeAt(i).toObject()["title"].toString();
    }
    return strList;
}
