#include "socketclient.h"

SocketClient::SocketClient(const QString &url, const int &port)
{

    this->create(url,port);
    this->getOrCreateTempPath();
}

SocketClient::~SocketClient(){

}

void SocketClient::create(const QString &url, const int &port){

    socketClient = new QTcpSocket();
    socketClient -> abort();
    socketClient->connectToHost(url, port);
    if(socketClient->waitForReadyRead(1000)){
        QByteArray s = socketClient->readAll();
        QString ss = QVariant(s).toString();
         qDebug();
        qDebug()<<Q_FUNC_INFO<<"waitForReadyRead:"<<ss;
        //this->data(s);
    }


    //绑定常用信号
    connect(socketClient, &QIODevice::readyRead,this, &SocketClient::data);
    connect(socketClient, &QTcpSocket::disconnected,this, &SocketClient::close);
    connect(socketClient, &QTcpSocket::connected,this, &SocketClient::connection);
    //connect(socketClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketError(QAbstractSocket::SocketError)));
    qDebug()<< "SocketClient create() 成功";

}


//void SocketClient::socketError(QAbstractSocket::SocketError error){
//    qDebug() <<"socketError";
//}

void SocketClient::close(){
    qDebug() <<"close";
}

void SocketClient::connection(){
    qDebug() <<"connection";
}



void SocketClient::data(){

    if(fileSize==0){
        QByteArray qba= socketClient->readAll(); //读取

        QString ss=QVariant(qba).toString();
        qDebug()<<Q_FUNC_INFO<<ss;
        QJsonDocument obj=QJsonDocument::fromJson(qba);
        QJsonObject dataContent= obj.object();
        QJsonObject subObj =dataContent.take("fileInfo").toObject();
        int uid=dataContent.take("uid").toInt();
        int hsize=dataContent.take("hsize").toInt();
        qDebug() <<"dataContent id:" << uid;
        fileSize=subObj["size"].toInt();
        fileName=subObj["name"].toString();

        zfilePath=tempPath+"/"+QString::number(uid)+"-"+fileName;
        QFile zfile(zfilePath);
        if(zfile.exists()){
            zfile.remove();
        }
        qDebug() <<"name-----:" << fileName;
        qDebug() <<"size-----:" << fileSize;
        qDebug() <<"zfilePath-----:" << zfilePath;
        QString fok="ok";
        socketClient->write(fok.toUtf8());

        //cosnt cdata=ss.split(hsize,ss.length());


    }else{

        // 通过formHex把十六进制的转换为QByteArray
        QByteArray fqba=QByteArray::fromHex(socketClient->readAll());

        //this->saveFile(fqba);

    }

}


//void SocketClient::saveFile( QByteArray &fqba){
//    hasSend=hasSend+fqba.length();
//    qDebug() <<"hasSend-----:"<<hasSend ;
//    //压缩的文件
//    QFile zfile(zfilePath);

//    zfile.open(QIODevice::WriteOnly|QIODevice::Append);
//    zfile.write(fqba);
//    //qDebug()<< hasSend<< (int)((hasSend / fileSize) * 100) << "%";
//    //qDebug() <<"hasSend-----:"<<hasSend << "fileSize:"<<fileSize;
//    //接受完成
//    if(hasSend >= fileSize){
//        zfile.close();
//        QString end="接受完成";
//        socketClient->write(end.toUtf8());
//        qDebug() <<"文件接受完成,文件大小"<<hasSend << "更新时间"<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//        this->initParams();
//        //发送更新成功信号
//        emit hot();
//    }
//}




void SocketClient::initParams(){
    fileSize=0;
    hasSend=0;
    uid=-1;
    fileName="";
    zfilePath="";
}

///**
// * @brief SocketClient::onDisconnected 断开链接slot
// */
//void SocketClient::disconnected(){
//    qDebug();
//    qDebug() <<"SocketClient 断开链接:";
//    //重连操作
//}

QString SocketClient::getOrCreateTempPath(){
    tempPath=Helper::instance()->getDataRootPath()+"/"+this->TEMP_PATH_NAME;

    QDir *temp=new QDir(tempPath);
    if(!temp->exists(tempPath)){
        temp->mkpath(tempPath);
        qDebug()<<"临时路径不存在:"<<tempPath <<"重新创建";
    }else{
        qDebug()<<"存在临时路径:"<<tempPath;

    }

    return tempPath;
}

