#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>

class Loader
{
public:
    explicit Loader() = delete;

    static QJsonArray getLevel(const QString &levelName);

    static QStringList getLevelTitles();

private:
    static QJsonArray getLevels();
};

#endif // LEVEL_H
