#ifndef TALLYMODEL_H
#define TALLYMODEL_H

#include <QAbstractListModel>
#include "tally.h"

class TallyList;

class TallyModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TallyList * list READ list WRITE setlist)


public:
    explicit TallyModel::TallyModel(QObject *parent);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    TallyList *getTallies() const;
    void setTallies(TallyList *value);

private:
    TallyList * tallies;
};

#endif // TALLYMODEL_H
