#include "httpclient.h"
#include <QNetworkAccessManager>
#include <QDebug>
#include "cenvironment.h"

HttpClient::HttpClient(QObject *parent) :
    QObject(parent) {
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &HttpClient::finished);
}

HttpClient::~HttpClient(){
    delete manager;
}

HttpClient* HttpClient::instance(){
    if(NULL==httpClient){
        httpClient = new HttpClient();
    }
    return httpClient;
}

void HttpClient::get(const QString &url){
    qDebug() << Q_FUNC_INFO << endl;
    manager->get(QNetworkRequest(QUrl(url)));
}

void HttpClient::finished(QNetworkReply *reply){
    qDebug() << Q_FUNC_INFO << endl;

    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug() << Q_FUNC_INFO << " statusCode: " << statusCode.toString() << endl;

}

