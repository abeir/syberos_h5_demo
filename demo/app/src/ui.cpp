#include "ui.h"
#include <QDebug>
//#include <cenvironment.h>
#include <qcompilerdetection.h>
#include <QQuickView>
#include <SyberosGuiCache>
#include "helper.h"

Ui::Ui(QObject *parent) : QObject(parent) {

}

void Ui::button(){
    qDebug() << Q_FUNC_INFO << endl;

    QQuickView *m_view = SYBEROS::SyberosGuiCache::qQuickView();

   QObject *v = m_view->findChild<QObject*>("webview");
   qDebug() << "++++++++++++++ " << v << endl;
   v->setProperty("color", "red");
}

