// main.cpp
#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <algorithm> // std::count_if
#include <cstdlib>   // rand, srand
#include <ctime>

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    QVector<int> numeros;
    srand(time(nullptr));

    // Generamos 10 números aleatorios entre 0 y 50
    for (int i = 0; i < 10; ++i)
        numeros.append(rand() % 51);

    qDebug() << "Vector generado:" << numeros;

    int cantidad = std::count_if(numeros.begin(), numeros.end(),
                                 [](int n) { return (n % 2 != 0) && (n < 20); });

    qDebug() << "Cantidad de números impares menores de 20:" << cantidad;

    return 0;
}
