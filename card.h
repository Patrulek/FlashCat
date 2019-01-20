#ifndef CARD_H
#define CARD_H

#include <QVector>
#include <QString>
#include "answer.h"

namespace FlashCat {
    class Card {
        public:
            QString question;
            QVector<Answer> answers;
    };
}

#endif // CARD_H
