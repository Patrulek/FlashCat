#include "backend.h"

#include <QObject>
#include <QNetworkReply>
#include <QDebug>
#include <QAuthenticator>
#include <QJsonDocument>
#include <QJsonObject>


Backend::Backend()
{
    network = std::make_unique<QNetworkAccessManager>();
    parser = std::make_unique<JsonParser>();
    user = std::make_unique<User>();

    QObject::connect(network.get(), &QNetworkAccessManager::finished,
            this, [=](QNetworkReply *reply) {

                if(reply->error())
                    processError(reply);
                else
                    loginSuccess(reply);
            }
        );
}

void Backend::processError(QNetworkReply *_reply) {
    if (_reply->error() == QNetworkReply::NetworkError::AuthenticationRequiredError)
        qDebug() << "nieprawidlowe dane logowania";
    else
        qDebug() << _reply->errorString();
}

void Backend::loginSuccess(QNetworkReply * _reply) {
    QString answer = _reply->readAll();

    try {
        parser->fromString(answer);
        qDebug() << parser->getValue("id");
        qDebug() << parser->getValue("registerTime");
        qDebug() << parser->getValue("username");
    } catch ( std::exception & ex) {
        qDebug() << ex.what() << endl;
    }
}

void Backend::login(QString _email, QString _password) {
    QUrl url("http://flashcat.io/login");

    QNetworkRequest request(url);
    request.setRawHeader("username", _email.toLocal8Bit());
    request.setRawHeader("password", _password.toLocal8Bit());
    QByteArray data;

    network->post(request, data);
}
