#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "tally.h"
#include "tallies.h"

using namespace FlashCat;
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    Tallies tallies;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("talls", &tallies);

    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
