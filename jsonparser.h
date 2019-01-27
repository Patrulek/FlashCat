#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonDocument>

class JsonParser
{
public:
    JsonParser();
    void fromString(QString _string);
    void fromObject(QJsonObject _obj);
    QString toString();
    QJsonValue getObject(QString _key);
    QString getObjectValue(QJsonObject _obj, QString _key);
    QJsonDocument getDocument() { return doc; }

private:
    QJsonDocument doc;
    bool valid;
    QString str;
};

#endif // JSONPARSER_H
