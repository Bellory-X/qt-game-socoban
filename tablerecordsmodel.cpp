#include "tablerecordsmodel.h"
#include "loader.h"

TableRecordsModel::TableRecordsModel(GameScene *parent) : QStandardItemModel(0, 2, parent)
{
    setHeaderData(0, Qt::Horizontal, "Name");
    setHeaderData(1, Qt::Horizontal, "Time");
    titles_ = Loader::getLevelTitles();
    for (auto &title : titles_)
    {
        records.insert(title, {});
    }
}

QStringList TableRecordsModel::titles() const
{
    return titles_;
}

void TableRecordsModel::fill(QListWidgetItem *item)
{
    if (parent())
    {
        dynamic_cast<GameScene *>(parent())->setLevel(item->text());
    }
    if (curTitle == item->text())
    {
        return;
    }
    records[curTitle].clear();
    for (int i = 0; i < rowCount(); ++i)
    {
        auto row = takeRow(i);
        records[curTitle].append({row[0]->text(), row[1]->text()});
    }
    curTitle = item->text();
    removeRows(0, rowCount());
    for (auto &record : records[curTitle])
    {
        add(record);
    }
}

void TableRecordsModel::add(const QPair<QString, QString> &record)
{
    if (rowCount() == 10 && item(rowCount() - 1, 1)->text() > record.second)
    {
        item(rowCount() - 1, 0)->setText(record.first);
        item(rowCount() - 1, 1)->setText(record.second);
    }
    if (rowCount() < 10)
    {
        setItem(rowCount(), 0, new QStandardItem(record.first));
        setItem(rowCount() - 1, 1, new QStandardItem(record.second));
    }
    sort(1);
}
