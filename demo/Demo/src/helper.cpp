#include "helper.h"
#include <cenvironment.h>
#include <QApplication>
#include <QDir>
#include <QDebug>
#include "httpclient.h"

Helper::Helper(QObject *parent) : QObject(parent) {
    env = new CEnvironment(this);
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

QString Helper::downloadFile(QString url){
    qDebug() << Q_FUNC_INFO << " url: " << url << endl;

    HttpClient::instance()->get(url);

    return env->dataPath();
}
