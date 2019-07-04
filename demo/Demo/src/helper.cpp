#include "helper.h"
#include "httpclient.h"
#include <cenvironment.h>
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextCodec>

Helper::Helper(QObject *parent) : QObject(parent) {
    env = new CEnvironment(this);

    connect(HttpClient::instance(), SIGNAL(replyData(QString,QByteArray)), this, SLOT(saveDownloadFile(QString,QByteArray)));
    connect(HttpClient::instance(), SIGNAL(replyError(QNetworkReply::NetworkError,QString)), this, SLOT(downloadFileFailed(QNetworkReply::NetworkError,QString)));
}

Helper* Helper::instance(){
    static Helper helper;
    return &helper;
}


QString Helper::getWebRootPath(){
    QDir dir(qApp->applicationDirPath());
    dir.cdUp();
    dir.cd("www");
    return dir.absolutePath();
}

QString Helper::getDataRootPath(){
    return env->dataPath();
}

QString Helper::getExternStorageRootPath(){
    return env->externalStoragePath();
}

QString Helper::getInnerStorageRootPath(){
    return env->internalStoragePath();
}

void Helper::downloadFile(QString id, QString url){
    qDebug() << Q_FUNC_INFO << " id: " << id << " url: " << url << endl;

    HttpClient::instance()->get(url);

    urlIdMap[url] = id;
}

void Helper::saveDownloadFile(QString url, QByteArray bytes){
    qDebug() << Q_FUNC_INFO << " url: " << url << endl;

    QString path = getDataRootPath() + "/tmp.gif";
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(bytes);
    file.close();

    if(urlIdMap.contains(url)){

        QFile f(path);
        qDebug() << Q_FUNC_INFO << " path: " << path << "exists:" << f.exists() << endl;

        QString id = urlIdMap[url];
        emit success(id, "{\"path\":\"" + path + "\"}");
        urlIdMap.remove(url);
    }

}

void Helper::downloadFileFailed(QNetworkReply::NetworkError errorCode, QString errorMessage){
    qDebug() << Q_FUNC_INFO << endl;
}
