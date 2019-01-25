#include "jsonparser.h"

#include <QJsonObject>
#include <QDebug>

JsonParser::JsonParser()
    : valid(false)
{

}

QJsonValue JsonParser::getObject(QString _key) {
    if( !valid)
        throw std::runtime_error(("Invalid JSON:\n" + str).toStdString());

    QJsonObject obj = doc.object();

    return obj[_key];
}

QString JsonParser::getValue(QString _key) {
    if( !valid)
        throw std::runtime_error(("Invalid JSON:\n" + str).toStdString());

    QJsonObject obj = doc.object();
    QJsonValue val = obj[_key];

    switch(val.type()) {
        case QJsonValue::Type::String:
            return val.toString();
        case QJsonValue::Type::Double:
            return QString::number(val.toDouble());
        default:
            return val.toString(); // TODO
    }
}

void JsonParser::fromString(QString _string) {
    str = _string;
    doc = QJsonDocument::fromJson(str.toUtf8());

       if(!doc.isNull()) {
           if(!doc.isObject()) {
               valid = false;
               throw std::runtime_error("Document is not an object");
           }

           valid = true;
           return;
       }

       valid = false;
       throw std::runtime_error(("Invalid JSON:\n" + str).toStdString());
}
