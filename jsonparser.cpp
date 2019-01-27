#include "jsonparser.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

JsonParser::JsonParser()
    : valid(false)
{

}

void JsonParser::fromObject(QJsonObject _obj) {
    doc.setObject(_obj);
    str = doc.toJson();
    valid = true;
}

QJsonValue JsonParser::getObject(QString _key) {
    if( !valid)
        throw std::runtime_error(("Invalid JSON:\n" + str).toStdString());

    QJsonObject obj = doc.object();

    return obj[_key];
}

QString JsonParser::toString() {
    if( !valid)
        throw std::runtime_error(("Invalid JSON:\n" + str).toStdString());

    return str;
}

QString JsonParser::getObjectValue(QJsonObject _obj, QString _key) {
    if( !valid)
        throw std::runtime_error(("Invalid JSON:\n" + str).toStdString());

    QJsonValue val = _obj[_key];

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
           if(!doc.isObject() && !doc.isArray()) {
               valid = false;
               throw std::runtime_error("Document is not an valid JSON object");
           }

           valid = true;
           return;
       }

       valid = false;
       throw std::runtime_error(("Invalid JSON:\n" + str).toStdString());
}
