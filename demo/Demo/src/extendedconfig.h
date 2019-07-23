#ifndef EXTENDEDCONFIG_H
#define EXTENDEDCONFIG_H

#include <QObject>

class ExtendedConfig : public QObject
{
    Q_OBJECT
public:
    static ExtendedConfig* instance();

    QVariantMap* getConfig();

    QVariant get(const QString& key);

private:
    explicit ExtendedConfig(QObject *parent = 0);
    ExtendedConfig(const ExtendedConfig &) Q_DECL_EQ_DELETE;
    ExtendedConfig& operator=(ExtendedConfig config) Q_DECL_EQ_DELETE;

    void init();

    static ExtendedConfig* _instance;

    QVariantMap* config;
};

#endif // EXTENDEDCONFIG_H
