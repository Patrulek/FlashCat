#ifndef TALLYLIST_H
#define TALLYLIST_H

#include <QObject>
#include <QVector>
#include "tally.h"


class TallyList : public QObject
{
    Q_OBJECT
public:
    explicit TallyList(QObject *parent = nullptr);
    QVector<FlashCat::Tally> tallies;

    bool setItemAt(int _index, const FlashCat::Tally & _tally);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int _index);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeCompletedItems();
};

#endif // TALLYLIST_H
