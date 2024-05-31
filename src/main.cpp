#include <QApplication>
#include <QQmlApplicationEngine>
#include "lineGeometry.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("./src/main.qml")));

    return app.exec();
}
