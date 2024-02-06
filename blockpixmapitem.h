#ifndef EMPTYVIEW_H
#define EMPTYVIEW_H

#include <QGraphicsPixmapItem>

class BlockPixmapItem : public QGraphicsPixmapItem
{
public:
    enum Model
    {
        isEmpty,
        isGoal,
        isWell,
        isBoxLight,
        isBoxDark,
        isPlayerUp0,
        isPlayerUp1,
        isPlayerUp2,
        isPlayerDown0,
        isPlayerDown1,
        isPlayerDown2,
        isPlayerLeft0,
        isPlayerLeft1,
        isPlayerLeft2,
        isPlayerRight0,
        isPlayerRight1,
        isPlayerRight2
    };

    explicit BlockPixmapItem(QPoint point, Model model, QGraphicsItem *parent = nullptr);

    Model model() const;

    void setModel(Model model);

    void move(const QPoint &step);

    static const int frameCount = 3;

    static const int gridSize = 45;

private:
    Model model_;
};

#endif // EMPTYVIEW_H
