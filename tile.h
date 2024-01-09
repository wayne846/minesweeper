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
        ~Tile();

        void click();
        void setFlag();
        void setType(int t);
        int getType();
        bool getHasClicked();
        bool getIsFlag();

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
        bool hasClicked;
        int type;
        QGraphicsItem *image_flag;
        QGraphicsItem *image_type;
        MainWindow *window;

        void openBlank();
};

#endif // TILE_H
