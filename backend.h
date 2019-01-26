#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QNetworkAccessManager>
#include <memory>
#include <QObject>

#include "jsonparser.h"
#include "user.h"

class Backend : public QObject
{

    Q_OBJECT
    Q_PROPERTY(bool login_success MEMBER login_success NOTIFY loginSuccessChanged)
    Q_PROPERTY(bool register_success MEMBER register_success NOTIFY registerSuccessChanged)
public:
    Backend();

    Q_SLOT void login(QString _email, QString _password);
    Q_SLOT void reg(QString _email, QString _password, QString _firstname, QString _lastname);
    Q_SLOT void logout();

    Q_SLOT void onRequestReply(QNetworkReply * _reply);
    void loginSuccess(QNetworkReply * _reply);
    void registerSuccess(QNetworkReply * _reply);

    void processError(QNetworkReply * _reply);
    std::unique_ptr<QNetworkAccessManager> network;
    std::unique_ptr<JsonParser> parser;
    std::unique_ptr<User> user;

    Q_SIGNAL void loginSuccessChanged();
    Q_SIGNAL void registerSuccessChanged();

private:
    bool login_success;
    bool register_success;
};

#endif // BACKEND_H
