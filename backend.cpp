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

    connect(network.get(), SIGNAL(finished(QNetworkReply *)),
            this, SLOT(onRequestReply(QNetworkReply *)));
}

void Backend::logout() {
    qDebug() << "logout";
}

void Backend::onRequestReply(QNetworkReply *_reply) {
    qDebug() << "type: " << _reply->property("type");

    if(_reply->error())
        processError(_reply);
    else {
        if( _reply->property("type") == "login")
            loginSuccess(_reply);
        else
            registerSuccess(_reply);
    }
}

void Backend::registerSuccess(QNetworkReply *_reply) {
    QString answer = _reply->readAll();
    register_success = true;
    emit registerSuccessChanged();

    try {
        parser->fromString(answer);
        qDebug() << parser->getValue("id");
        qDebug() << parser->getValue("registerTime");
        qDebug() << parser->getValue("username");
    } catch ( std::exception & ex) {
        qDebug() << ex.what() << endl;
    }
}

void Backend::reg(QString _email, QString _password, QString _firstname, QString _lastname) {
    QUrl url("http://flashcat.io/register");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=UTF-8");

    QJsonObject obj;
    obj["username"] = _email;
    obj["password"] = _password;
    obj["firstname"] = _firstname;
    obj["lastname"] = _lastname;
    parser->fromObject(obj);
    QByteArray data = parser->toString().toUtf8();

    try {
        QNetworkReply * reply = network->post(request, data);
        reply->setProperty("type", "register");
    } catch(std::exception & ex) {
        qDebug() << ex.what() << endl;
    }
}


void Backend::processError(QNetworkReply *_reply) {
    if( _reply->property("type") == "login") {
        login_success = false;
        emit loginSuccessChanged();
    } else {
        register_success = false;
        emit registerSuccessChanged();
    }

    qDebug() << _reply->error();

    if (_reply->error() == QNetworkReply::NetworkError::AuthenticationRequiredError)
        qDebug() << "nieprawidlowe dane logowania";
    else
        qDebug() << _reply->errorString();
}

void Backend::loginSuccess(QNetworkReply * _reply) {
    QString answer = _reply->readAll();
    login_success = true;
    emit loginSuccessChanged();

    try {
        parser->fromString(answer);
        qDebug() << parser->getValue("id");
        qDebug() << parser->getValue("registerTime");
        qDebug() << parser->getValue("username");

        user->id = parser->getValue("id").toInt();
    } catch ( std::exception & ex) {
        qDebug() << ex.what() << endl;
    }
}

void Backend::login(QString _email, QString _password) {
    QUrl url("http://flashcat.io/login");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=UTF-8");
    request.setRawHeader("username", _email.toUtf8());
    request.setRawHeader("password", _password.toUtf8());
    QByteArray data;

    QNetworkReply * reply = network->post(request, data);
    reply->setProperty("type", "login");
}
