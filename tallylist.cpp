#include "tallylist.h"

using namespace FlashCat;

TallyList::TallyList(QObject *parent) : QObject(parent)
{

    Tally t1 {"Tally 1", QVector<Card>()};
    Tally t2 {"Tally 2", QVector<Card>()};
    Tally t3 {"Tally 3", QVector<Card>()};
    Tally t4 {"Tally 4", QVector<Card>()};
    Tally t5 {"Tally 5", QVector<Card>()};
}

bool TallyList::setItemAt(int _index, const FlashCat::Tally &_tally)
{
    if( _index < 0 || _index > tallies.size() )
        return false;

    const auto & old_item = tallies.at(_index);

    if( old_item.name == _tally.name )
        return false;

    tallies[_index] = _tally;
    return true;
}

void TallyList::appendItem()
{
    emit preItemAppended();

    FlashCat::Tally tally;
    tallies.append(tally);

    emit postItemAppended();
}
