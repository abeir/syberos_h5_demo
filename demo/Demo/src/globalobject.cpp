#include "globalobject.h"
#include "helper.h"

GlobalObject::GlobalObject(QObject *parent) : QObject(parent) {
    helper = new Helper(this);
    ui = new Ui(this);
}

QObject* GlobalObject::getHelper(){
    return helper;
}

QObject* GlobalObject::getUi(){
    return ui;
}
