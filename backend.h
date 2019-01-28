#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QNetworkAccessManager>
#include <memory>
#include <QObject>
#include <QNetworkReply>
#include <QQmlApplicationEngine>

#include "jsonparser.h"
#include "user.h"
#include "tally.h"

class Backend : public QObject
{

    Q_OBJECT
    Q_PROPERTY(bool login_success MEMBER login_success NOTIFY loginSuccessChanged)
    Q_PROPERTY(bool register_success MEMBER register_success NOTIFY registerSuccessChanged)
    Q_PROPERTY(QString status_error MEMBER status_error)
public:
    Backend(QQmlApplicationEngine & _engine);

    Q_SLOT void getTallies();
    Q_SLOT void login(QString _email, QString _password);
    Q_SLOT void reg(QString _email, QString _password, QString _firstname, QString _lastname);
    Q_SLOT void logout();
    Q_SLOT void addTally(QString _name);
    Q_SLOT void getTallyCards(const FlashCat::Tally & _tally);

    Q_SLOT void onRequestReply(QNetworkReply * _reply);
    void loginSuccess(QNetworkReply * _reply);
    void registerSuccess(QNetworkReply * _reply);
    void getTalliesSuccess(QNetworkReply * _reply);
    void addTallySuccess(QNetworkReply * _reply);
    void getTallyCardsSuccess(QNetworkReply * _reply);

    void processError(QNetworkReply * _reply);
    std::unique_ptr<QNetworkAccessManager> network;
    std::unique_ptr<JsonParser> parser;
    std::unique_ptr<User> user;

    Q_SIGNAL void loginSuccessChanged();
    Q_SIGNAL void registerSuccessChanged();

    QNetworkReply::NetworkError last_error;
    QString status_error;
private:
    bool login_success;
    bool register_success;
    QQmlApplicationEngine & engine;
};

#endif // BACKEND_H
