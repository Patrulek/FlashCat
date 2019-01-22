#ifndef TALLIES_H
#define TALLIES_H

#include <QStandardItemModel>
#include "tally.h"

class Tallies : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel * model READ model)
    Q_PROPERTY(QStringList str_model READ str_model)
    Q_DISABLE_COPY(Tallies)

public:
    explicit Tallies(QObject * parent = Q_NULLPTR)
        : QObject(parent) {
        m_model=new QStandardItemModel(this);
        m_model->insertColumn(0);
        fillDummyData();
    }

    Q_SLOT void addTally(const QString& name) {
            const int newRow= m_model->rowCount();
            const FlashCat::Tally newTally(name);

            m_model->insertRow(newRow);
            m_model->setData(m_model->index(newRow,0),QVariant::fromValue(newTally),Qt::EditRole);
        }
    QAbstractItemModel* model() const {return m_model;}
    QStringList str_model() const {
        QStringList str;

        for( int i = 0; i < m_model->rowCount(); ++i ) {
            const auto & idx = m_model->index(i, 0);
            auto tally = qvariant_cast<FlashCat::Tally>(idx.data());
            str.append(tally.getName());
        }

        return str;
    }

private:
    void fillDummyData(){
        addTally("tally1");
        addTally("tally2");
        addTally("tally3");
        addTally("tally4");
        addTally("tally5");
        addTally("tally6");
        addTally("tally7");
        addTally("tally8");
        addTally("tally9");
    }
    QAbstractItemModel* m_model;
};

#endif // TALLIES_H
