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
        Tile(MainWindow *window, int x, int y, int type);

        void click();
        void setFlag();

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    private:
        QColor normal_color;
        QColor hover_color;
        QColor clicked_color;

        int x;
        int y;
        bool isFlag;
        bool hadClicked;
        int type;
        QGraphicsItem *image_flag;
        QGraphicsItem *image_type;
        MainWindow *window;
};

#endif // TILE_H
