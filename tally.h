#ifndef TALLY_H
#define TALLY_H

#include <QVector>
#include <QString>
#include <QObject>

#include "card.h"

namespace FlashCat {
    class Tally {
        Q_GADGET
        Q_PROPERTY(QString name READ getName WRITE setName)
        Q_PROPERTY(int size READ getSize)

        public:
            explicit Tally(const QString & _name)
                : name(_name) {}
            Tally() = default;

            void setName(const QString & _name) { name = _name; }

            QString getName() { return name; }
            QVector<Card> getCards() { return cards; }
            int getSize() { return cards.size(); }
        private:
            QString name;
            QVector<Card> cards;
    };
}

#endif // TALLY_H
