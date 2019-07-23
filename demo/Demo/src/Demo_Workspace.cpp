#include "Demo_Workspace.h"
#include "globalobject.h"
#include "helper.h"
#include "download.h"
#include <QQmlContext>
#include <QDebug>
#include <qqml.h>
#include <QQuickItem>
#include "extendedconfig.h"

Demo_Workspace::Demo_Workspace()
    : CWorkspace()
{
    ExtendedConfig *config = ExtendedConfig::instance();
    QVariant debug = config->get("debug");
    qDebug() << "$$$ debug:" << debug << debug.isValid() << endl;


    m_view = SYBEROS::SyberosGuiCache::qQuickView();
    QObject::connect(m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));


    GlobalObject *global = new GlobalObject(this);
    m_view->rootContext()->setContextProperty("global", global);

    Helper *helper = Helper::instance();
    m_view->rootContext()->setContextProperty("helper", helper);

    Download *download = Download::instance();
    m_view->rootContext()->setContextProperty("Download", download);

    m_view->setSource(QUrl("qrc:/qml/main.qml"));
    m_view->showFullScreen();

}

void Demo_Workspace::onLaunchComplete(Option option, const QStringList& params)
{
    qDebug() << "++++++++++1 \r\n";

    QQuickItem *it = m_view->rootObject();
    //CPageStackWindow_QMLTYPE_16(0x9ab2d78, name="pageStackWindow", parent=0x9a44860, geometry=0,0 720x1280)
    qDebug() << "++++++++++ " << it << " +++ \r\n";


    qDebug() << "++++++++++ " << it->property("initialPage") << " +++ \r\n";
    qDebug() << "++++++++++ " << it->children() << " +++ \r\n";

    qDebug() << "++++++++++ || \r\n";

    Q_UNUSED(params)

    switch (option) {
    case CWorkspace::HOME:
        qDebug()<< "Start by Home";
        break;
    case CWorkspace::URL:
        break;
    case CWorkspace::EVENT:
        break;
    case CWorkspace::DOCUMENT:
        break;
    default:
        break;
    }
}

