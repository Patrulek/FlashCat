#ifndef CARD_H
#define CARD_H

#include <QVector>
#include <QString>
#include "answer.h"

namespace FlashCat {
    class Card {
        public:
            Card(int _id) : id(_id) {}
            Card() = default;

            int id;
            QString question;
            QVector<Answer> answers;
    };
}

#endif // CARD_H
