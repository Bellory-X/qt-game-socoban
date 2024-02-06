#include "blockpixmapitem.h"

BlockPixmapItem::BlockPixmapItem(QPoint point, Model model, QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPos(point * gridSize);
    setModel(model);
}

BlockPixmapItem::Model BlockPixmapItem::model() const
{
    return model_;
}

void BlockPixmapItem::move(const QPoint &step)
{
    setPos(pos() + step * gridSize / frameCount);
}

void BlockPixmapItem::setModel(Model model)
{
    model_ = model;
    switch (model_)
    {
    case isEmpty:
        setPixmap(QPixmap(":/assets/Ground/ground_06.png").scaled(gridSize, gridSize));
        setZValue(0);
        break;
    case isGoal:
        setPixmap(QPixmap(":/assets/Environment/environment_05.png").scaled(gridSize, gridSize));
        setZValue(1);
        break;
    case isWell:
        setPixmap(QPixmap(":/assets/Blocks/block_01.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isBoxLight:
        setPixmap(QPixmap(":/assets/Crates/crate_02.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isBoxDark:
        setPixmap(QPixmap(":/assets/Crates/crate_12.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerUp0:
        setPixmap(QPixmap(":/assets/Player/player_up_00.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerUp1:
        setPixmap(QPixmap(":/assets/Player/player_up_01.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerUp2:
        setPixmap(QPixmap(":/assets/Player/player_up_02.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerDown0:
        setPixmap(QPixmap(":/assets/Player/player_down_00.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerDown1:
        setPixmap(QPixmap(":/assets/Player/player_down_01.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerDown2:
        setPixmap(QPixmap(":/assets/Player/player_down_02.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerLeft0:
        setPixmap(QPixmap(":/assets/Player/player_left_00.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerLeft1:
        setPixmap(QPixmap(":/assets/Player/player_left_01.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerLeft2:
        setPixmap(QPixmap(":/assets/Player/player_left_02.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerRight0:
        setPixmap(QPixmap(":/assets/Player/player_right_00.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerRight1:
        setPixmap(QPixmap(":/assets/Player/player_right_01.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    case isPlayerRight2:
        setPixmap(QPixmap(":/assets/Player/player_right_02.png").scaled(gridSize, gridSize));
        setZValue(2);
        break;
    }
}
