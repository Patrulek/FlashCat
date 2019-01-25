#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QNetworkAccessManager>
#include <memory>

#include "jsonparser.h"
#include "user.h"

class Backend : public QObject
{

    Q_OBJECT

public:
    Backend();

    Q_SLOT void login(QString _email, QString _password);
    void loginSuccess(QNetworkReply * _reply);

    void processError(QNetworkReply * _reply);
    std::unique_ptr<QNetworkAccessManager> network;
    std::unique_ptr<JsonParser> parser;
    std::unique_ptr<User> user;
};

#endif // BACKEND_H
