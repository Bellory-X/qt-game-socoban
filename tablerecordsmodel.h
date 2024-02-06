#ifndef TABLERECORDSMODEL_H
#define TABLERECORDSMODEL_H

#include "gamescene.h"

#include <QStandardItemModel>
#include <QListWidgetItem>
#include <QList>

class TableRecordsModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit TableRecordsModel(GameScene *parent = nullptr);

    QStringList titles() const;

public slots:
    void fill(QListWidgetItem *item = nullptr);
    void add(const QPair<QString, QString> &record);

private:
    QString curTitle;
    QStringList titles_;
    QMap<QString, QList<QPair<QString, QString>>> records;
};

#endif // TABLERECORDSMODEL_H
