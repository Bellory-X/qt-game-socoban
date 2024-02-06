#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "blockpixmapitem.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QStack>
#include <QListWidgetItem>
#include <QTimer>

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameScene(QTimer *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;

    void setLevel(const QString &title);

private:
    QVector<QVector<QStack<BlockPixmapItem *>>> grid;
    QPoint movementBoxPos;
    QPoint playerPos;
    QPoint step;
    QTimer timer;
    int goalCount;
    int frameCount;

    void move();
    void changePlayerPos();
    void changeBoxPos();

private slots:
    void animateBlocks();
};

#endif // GAMEMODEL_H
