#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include <QtNetwork>


class HttpClient : public QObject
{
    Q_OBJECT
public:
    static HttpClient* instance();
    ~HttpClient();

    void get(const QString &url);


private:
    explicit HttpClient(QObject *parent = 0);
    HttpClient(const HttpClient &) Q_DECL_EQ_DELETE;
    HttpClient& operator=(HttpClient client) Q_DECL_EQ_DELETE;

    QNetworkAccessManager *manager;
    static HttpClient *httpClient;
public slots:
    void finished(QNetworkReply *reply);
};

#endif // HTTPCLIENT_H
