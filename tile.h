#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class MainWindow;

class Tile : public QGraphicsRectItem{
    public:
        Tile(MainWindow *window, int x, int y);


    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

    private:
        int x;
        int y;
        MainWindow *window;
};

#endif // TILE_H
