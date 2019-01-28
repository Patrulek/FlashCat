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
            explicit Tally(const QString & _name, int _id)
                : name(_name), id(_id) {}
            Tally() = default;

            void setName(const QString & _name) { name = _name; }
            void addCard(int _id) { cards.push_back(Card(_id)); }

            QString getName() const { return name; }
            QVector<Card> getCards() const { return cards; }
            int getSize() const { return cards.size(); }
            int getId() const { return id; }
        private:
            QString name;
            int id;
            QVector<Card> cards;
    };
}

#endif // TALLY_H
