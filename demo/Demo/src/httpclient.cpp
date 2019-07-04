#include "httpclient.h"
#include <QNetworkAccessManager>
#include <QDebug>
#include "cenvironment.h"

HttpClient::HttpClient(QObject *parent) :
    QObject(parent) {
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

HttpClient::~HttpClient(){
    delete manager;
}

HttpClient* HttpClient::instance(){
    static HttpClient client;
    return &client;
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

