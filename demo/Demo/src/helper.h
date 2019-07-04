#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <cenvironment.h>

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = 0);
    Q_INVOKABLE QString getWebRootPath();
    Q_INVOKABLE QString getDataRootPath();
    Q_INVOKABLE QString getExternStorageRootPath();
    Q_INVOKABLE QString getInnerStorageRootPath();

    Q_INVOKABLE QString downloadFile(QString url);

private:
    CEnvironment *env;
};

#endif // HELPER_H
