#include "gamescene.h"
#include "loader.h"

#include <QJsonArray>

GameScene::GameScene(QTimer *parent) : QGraphicsScene(parent), frameCount(0)
{
    connect(&timer, &QTimer::timeout, this, &GameScene::animateBlocks);
}

void GameScene::setLevel(const QString &title)
{
    clear();
    goalCount = 0;
    auto level = Loader::getLevel(title);
    for (int y = 0; y < level.size(); ++y)
    {
        auto row = level[y].toString();
        grid.append(QVector<QStack<BlockPixmapItem *>>());
        for (int x = 0; x < row.size(); ++x)
        {
            grid[y].append(QStack<BlockPixmapItem *>());
            grid[y][x].push(new BlockPixmapItem({x, y}, BlockPixmapItem::isEmpty));
            addItem(grid[y][x].top());
            switch (row[x].toLatin1())
            {
                case '#':
                    grid[y][x].push(new BlockPixmapItem({x, y}, BlockPixmapItem::isWell));
                    break;
                case '$':
                    grid[y][x].push(new BlockPixmapItem({x, y}, BlockPixmapItem::isBoxLight));
                    break;
                case '.':
                    grid[y][x].push(new BlockPixmapItem({x, y}, BlockPixmapItem::isGoal));
                    goalCount++;
                    break;
                case '@':
                    grid[y][x].push(new BlockPixmapItem({x, y}, BlockPixmapItem::isPlayerDown0));
                    playerPos = {x, y};
                    break;
            }
            addItem(grid[y][x].top());
        }
    }
    if (parent())
    {
        dynamic_cast<QTimer *>(parent())->start();
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if (timer.isActive() || goalCount == 0)
    {
        return;
    }
    auto player = grid[playerPos.y()][playerPos.x()].top();
    switch (event->key())
    {
        case Qt::Key_Up:
            step = {0, -1};
            player->setModel(BlockPixmapItem::isPlayerUp0);
            break;
        case Qt::Key_Down:
            step = {0, 1};
            player->setModel(BlockPixmapItem::isPlayerDown0);
            break;
        case Qt::Key_Left:
            step = {-1, 0};
            player->setModel(BlockPixmapItem::isPlayerLeft0);
            break;
        case Qt::Key_Right:
            step = {1, 0};
            player->setModel(BlockPixmapItem::isPlayerRight0);
            break;
    }
    move();
}

void GameScene::move()
{
    auto nextPos = playerPos + step;
    grid[nextPos.y()][nextPos.x()].top();
    if (grid[nextPos.y()][nextPos.x()].top()->model() == BlockPixmapItem::isWell)
    {
        return;
    }
    if (grid[nextPos.y()][nextPos.x()].top()->model() <= BlockPixmapItem::isGoal)
    {
        return changePlayerPos();
    }
    auto nextBoxPos = nextPos + step;
    if (grid[nextBoxPos.y()][nextBoxPos.x()].top()->model() >= BlockPixmapItem::isWell)
    {
        return;
    }
    changeBoxPos();
    changePlayerPos();
}

void GameScene::changePlayerPos()
{
    auto nextPos = playerPos + step;
    grid[nextPos.y()][nextPos.x()].push(grid[playerPos.y()][playerPos.x()].pop());
    playerPos = nextPos;
    timer.start(50);
}

void GameScene::changeBoxPos()
{
    auto oldBoxPos = playerPos + step;
    auto nextBoxPos = oldBoxPos + step;
    auto box = grid[oldBoxPos.y()][oldBoxPos.x()].pop();
    if (grid[oldBoxPos.y()][oldBoxPos.x()].top()->model() == BlockPixmapItem::isGoal)
    {
        goalCount++;
        box->setModel(BlockPixmapItem::isBoxLight);
    }
    if (grid[nextBoxPos.y()][nextBoxPos.x()].top()->model() == BlockPixmapItem::isGoal)
    {
        goalCount--;
        box->setModel(BlockPixmapItem::isBoxDark);
    }
    grid[nextBoxPos.y()][nextBoxPos.x()].push(box);
    movementBoxPos = nextBoxPos;
    if (goalCount == 0 && parent())
    {
        dynamic_cast<QTimer *>(parent())->stop();
    }
}

void GameScene::animateBlocks()
{
    frameCount++;
    if (!movementBoxPos.isNull())
    {
        grid[movementBoxPos.y()][movementBoxPos.x()].top()->move(step);
    }
    auto player = grid[playerPos.y()][playerPos.x()].top();
    player->move(step);
    if (frameCount >= BlockPixmapItem::frameCount)
    {
        timer.stop();
        frameCount = 0;
        movementBoxPos = {};
        player->setModel(BlockPixmapItem::Model(player->model() - 2));
        return;
    }
    player->setModel(BlockPixmapItem::Model(player->model() + 1));
}
