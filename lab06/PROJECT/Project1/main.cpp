#include "comunicacion.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QObject>

class adulto: public QObject
{
private:
    QString name;
public:
    adulto(QObject *base = 0): QObject(base){}

    void setName(const QString &nam){
        name = nam;
    }
    QString getName() const {
        return name;
    }
    ~adulto(){
        qDebug() << "object broken";
    }
};

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    // QObject *person = new QObject;
    // Comunicacion *pepe = new Comunicacion (person);
    // Comunicacion *jose = new Comunicacion (person);

    // //set....
    // QObject::connect(pepe, SIGNAL (sendMessage(QString)), jose, SLOT (listen(QString)));
    // QObject::connect(jose, SIGNAL (sendMessage(QString)), pepe, SLOT (listen(QString)));
    // pepe->converse("buenos dias");
    // jose->converse("como vas?");

    // delete person;

    QTextStream inputStream(stdin);
    // QTextStream outputStream(stdout);

    qInfo() << "Enter your usename: ";
    // outputStream.flush();
    QString username = inputStream.readLine();

    qInfo() << "Hello "<< username;
    // outputStream.flush();


    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
