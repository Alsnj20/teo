#include "comunicacion.h"
#include <QDebug>
Comunicacion::Comunicacion(QObject *parent)
    : QObject{parent}
{}


void Comunicacion::listen(const QString &str) {
    qDebug() << "I'm listening...." << str;
}

void Comunicacion::converse(const QString &conversa) {
    //emit the signal
    emit sendMessage(conversa);
}
