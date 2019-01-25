#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonDocument>

class JsonParser
{
public:
    JsonParser();
    void fromString(QString _string);
    QJsonValue getObject(QString _key);
    QString getValue(QString _key);

private:
    QJsonDocument doc;
    bool valid;
    QString str;
};

#endif // JSONPARSER_H
