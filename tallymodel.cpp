#include "tallymodel.h"

#include "tallylist.h"

using namespace std;
using namespace FlashCat;

TallyModel::TallyModel(QObject *parent)
    : QAbstractListModel(parent), tallies(nullptr)
{
}

int TallyModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !tallies)
        return 0;

    return tallies->tallies.size();
}

QVariant TallyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !tallies)
        return QVariant();

    const Tally tally = tallies->tallies.at(index.row());
    return QVariant();
}

bool TallyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if( !tallies )
        return false;

    Tally tally = tallies->tallies.at(index.row());

    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags TallyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

TallyList *TallyModel::getTallies() const
{
    return tallies;
}

void TallyModel::setTallies(TallyList *value)
{
    beginResetModel();

    if( tallies )
        tallies->disconnect(this);

    tallies = value;

    if( tallies ) {
        connect(tallies, &TallyList::preItemAppended, this, [=]() {
            const int index = tallies->tallies.size();
            beginInsertRows(QModelIndex(), index, index);
        });

        connect(tallies, &TallyList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(tallies, &TallyList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(tallies, &TallyList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();

}
