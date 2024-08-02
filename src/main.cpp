// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "lineGeometry.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlExtensionPlugin>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/PlotDemo/main.qml")));

    return app.exec();
}
