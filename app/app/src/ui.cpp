#include "ui.h"
#include <QDebug>
#include <QMessageBox>
//#include <cenvironment.h>
#include <qcompilerdetection.h>

Ui::Ui(QObject *parent) : QObject(parent) {

}

void Ui::alert(const QString &title, const QString &text){
    qDebug() << Q_FUNC_INFO << endl;

    QMessageBox *messageBox = new QMessageBox();
//    QIcon(":/images/alert-warning"), title, text
    messageBox->setIcon(QMessageBox::Warning);
    messageBox->setWindowTitle(title);
    messageBox->setText(text);
    messageBox->setAttribute(Qt::WA_DeleteOnClose);
    messageBox->show();
}

