#ifndef TILE_H
#define TILE_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneEvent>
#include <QHoverEvent>

class MainWindow;

class Tile : public QGraphicsRectItem{
    public:
        Tile(MainWindow *window, int x, int y);


    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    private:
        QColor normal_color;
        QColor hover_color;

        int x;
        int y;
        QGraphicsItem *picture_flag;
        MainWindow *window;
};

#endif // TILE_H
