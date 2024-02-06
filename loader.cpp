#include "loader.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QJsonArray Loader::getLevel(const QString &levelName)
{
    auto levels = getLevels();
    for (const auto &item: levels)
    {
        auto level = item.toObject();
        if (levelName == level["Id"].toString())
        {
            return level["L"].toArray();
        }
    }
    return QJsonArray();
}

QStringList Loader::getLevelTitles()
{
    QStringList levelTitles;
    auto levels = getLevels();
    for (const auto &item: levels)
    {
        auto level = item.toObject();
        auto name = level["Id"].toString();
        levelTitles.append(name);
    }
    return levelTitles;
}

QJsonArray Loader::getLevels()
{
    auto file = QFile(":/assets/Levels/23x11.json");
    if (!file.open(QIODevice::ReadOnly))
    {
        return QJsonArray();
    }
    auto bytes = file.readAll();

    file.close();

    auto document = QJsonDocument::fromJson(bytes);
    auto jsonObject = document.object();
    auto sokobanLevels = jsonObject["SokobanLevels"].toObject();
    auto levelCollection = sokobanLevels["LevelCollection"].toObject();

    return levelCollection["Level"].toArray();
}
