#include "backend.h"

#include <QObject>
#include <QNetworkReply>
#include <QDebug>
#include <QAuthenticator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlContext>


Backend::Backend(QQmlApplicationEngine & _engine)
    : engine(_engine)
{
    network = std::make_unique<QNetworkAccessManager>();
    parser = std::make_unique<JsonParser>();
    user = std::make_unique<User>();

    connect(network.get(), SIGNAL(finished(QNetworkReply *)),
            this, SLOT(onRequestReply(QNetworkReply *)));
}

void Backend::logout() {
    user.reset(new User());
    qDebug() << "logout";
}

void Backend::onRequestReply(QNetworkReply *_reply) {
    qDebug() << "type: " << _reply->property("type");

    if(_reply->error()) {
        processError(_reply);
        return;
    }

    if( _reply->property("type") == "login")
        loginSuccess(_reply);
    else if( _reply->property("type") == "register")
        registerSuccess(_reply);
    else if( _reply->property("type") == "tallies")
        getTalliesSuccess(_reply);
    else if( _reply->property("type") == "addtally")
        addTallySuccess(_reply);
    else if( _reply->property("type") == "gettallycards")
        getTallyCardsSuccess(_reply);
}

void Backend::addTallySuccess(QNetworkReply *_reply) {
    QString answer = _reply->readAll();

    try {
        parser->fromString(answer);

        auto obj = parser->getDocument().object();
        QString tally_name = parser->getObjectValue(obj, "name");
        int tally_id = parser->getObjectValue(obj, "id").toInt();
        user->tallies.addTally(tally_name, tally_id);
    } catch( std::exception & ex ) { qDebug() << ex.what() << endl; }
}


void Backend::getTallyCards(const FlashCat::Tally & _tally) {
    QUrl url("http://flashcat.io/api/tallies/" + QString::number(_tally.getId()) + "/cards/desc");
    QNetworkRequest request(url);
    request.setRawHeader("authorization", user->token.toUtf8());
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=UTF-8");

    try {
        QNetworkReply * reply = network->get(request);
        reply->setProperty("type", "gettallycards");
    } catch(std::exception & ex) {
        qDebug() << ex.what() << endl;
    }
}

void Backend::getTallyCardsSuccess(QNetworkReply *_reply) {
    QString answer = _reply->readAll();
    qDebug() << answer;

    try {
        parser->fromString(answer);
        auto arr = parser->getDocument().array();

        for( auto val : arr ) {
            auto obj = val.toObject();
            QString id = parser->getObjectValue(obj, "id");
            int tally_id = parser->getObjectValue(obj, "tallyId").toInt();

            auto tally = user->tallies.getTally(tally_id); // REF!!
            tally.addCard(id.toInt());
            qDebug() << id;
        }
        engine.rootContext()->setContextProperty("talls", &user->tallies);
    } catch( std::exception & ex ) { qDebug() << ex.what() << endl; user->tallies.clear(); }

    login_success = true;
    emit loginSuccessChanged();
}

void Backend::getTalliesSuccess(QNetworkReply * _reply) {
    QString answer = _reply->readAll();
    qDebug() << answer;

    try {
        parser->fromString(answer);
        auto arr = parser->getDocument().array();

        for( auto val : arr ) {
            auto obj = val.toObject();
            QString tally_name = parser->getObjectValue(obj, "name");
            int tally_id = parser->getObjectValue(obj, "id").toInt();
            qDebug() << tally_name;
            user->tallies.addTally(tally_name, tally_id);
        }
        engine.rootContext()->setContextProperty("talls", &user->tallies);
    } catch( std::exception & ex ) { qDebug() << ex.what() << endl; user->tallies.clear(); }

    login_success = true;
    emit loginSuccessChanged();
}

void Backend::registerSuccess(QNetworkReply *_reply) {
    QString answer = _reply->readAll();
    register_success = true;
    emit registerSuccessChanged();

    try {
        parser->fromString(answer);
        auto obj = parser->getDocument().object();
        qDebug() << parser->getObjectValue(obj, "id");
        qDebug() << parser->getObjectValue(obj, "registerTime");
        qDebug() << parser->getObjectValue(obj, "username");
    } catch ( std::exception & ex) {
        qDebug() << ex.what() << endl;
    }
}

void Backend::addTally(QString _name) {
    QUrl url("http://flashcat.io/api/tallies");
    QNetworkRequest request(url);
    request.setRawHeader("authorization", user->token.toUtf8());
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=UTF-8");

    QJsonObject obj;
    obj["name"] = _name;
    parser->fromObject(obj);
    QByteArray data = parser->toString().toUtf8();

    try {
        QNetworkReply * reply = network->post(request, data);
        reply->setProperty("type", "addtally");
    } catch(std::exception & ex) {
        qDebug() << ex.what() << endl;
    }
}

void Backend::getTallies() {
    QUrl url("http://flashcat.io/api/accounts/" + QString::number(user->id) + "/tallies");
    QNetworkRequest request(url);
    request.setRawHeader("authorization", user->token.toUtf8());
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=UTF-8");

    try {
        QNetworkReply * reply = network->get(request);
        reply->setProperty("type", "tallies");
    } catch(std::exception & ex) {
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
    last_error = _reply->error(); // TODO
    qDebug() << last_error;

    if (_reply->error() == QNetworkReply::NetworkError::AuthenticationRequiredError)
        status_error = "Invalid username/password";
    else if(_reply->error() == QNetworkReply::NetworkError::ConnectionRefusedError)
        status_error = "Connection refused";
    else if( _reply->error() == QNetworkReply::NetworkError::InternalServerError)
        status_error = "Server down";
    else if( _reply->error() == QNetworkReply::ContentNotFoundError)
        status_error = "Server error";
    else
        status_error = _reply->errorString();

    if( _reply->property("type") == "login" || _reply->property("type") == "tallies") {
        login_success = false;
        emit loginSuccessChanged();
    } else {
        register_success = false;
        emit registerSuccessChanged();
    }

}

void Backend::loginSuccess(QNetworkReply * _reply) {
    QString answer = _reply->readAll();

    try {
        parser->fromString(answer);
        auto obj = parser->getDocument().object();
        qDebug() << parser->getObjectValue(obj, "id");
        qDebug() << parser->getObjectValue(obj, "registerTime");
        qDebug() << parser->getObjectValue(obj, "username");

        user->id = parser->getObjectValue(obj, "id").toInt();
        user->token = _reply->rawHeader("authorization");

        qDebug() << user->token;

        getTallies();
    } catch ( std::exception & ex) {
        qDebug() << ex.what() << endl;
    }
}

void Backend::login(QString _email, QString _password) {
    QUrl url("http://flashcat.io/login");

    qDebug() << _password;

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json;charset=UTF-8");
    request.setRawHeader("username", _email.toUtf8());
    request.setRawHeader("password", _password.toUtf8());
    QByteArray data;

    QNetworkReply * reply = network->post(request, data);
    reply->setProperty("type", "login");
}
