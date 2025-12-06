#ifndef COMUNICACION_H
#define COMUNICACION_H

#include <QObject>

class Comunicacion : public QObject
{
    Q_OBJECT

private:
    QString strname;

public:
    explicit Comunicacion(QObject *parent = nullptr);
    void setNombre(const QString &nomb) {
        strname = nomb;
    }
    void converse(const QString &conversa);

signals:
    void sendMessage(QString);

public slots:
    void listen(const QString &str);
};

#endif // COMUNICACION_H
