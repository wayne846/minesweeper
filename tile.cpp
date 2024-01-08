#include "tile.h"
#include <QDebug>
#include "mainwindow.h"
#include <QGraphicsPixmapItem>

Tile::Tile(MainWindow *window, int x, int y){
    this->window = window;
    this->x = x;
    this->y = y;
    this->setRect(window->TILE_WIDTH * x, window->TILE_WIDTH * y + window->HUD_HEIGHT, window->TILE_WIDTH, window->TILE_WIDTH);
    if((x+y)%2 == 0){
        normal_color = window->TILE_EVEN_COLOR;
    }else{
        normal_color = window->TILE_ODD_COLOR;
    }
    hover_color = window->TILE_HOVER_COLOR;
    this->setBrush(normal_color);
    this->setPen(normal_color);
    this->setAcceptHoverEvents(true);

    //set picture_flag
    QPixmap pixmap = QPixmap(":/flag.png");
    pixmap = pixmap.scaled(QSize(window->TILE_WIDTH, window->TILE_WIDTH));
    this->picture_flag = new QGraphicsPixmapItem(pixmap);
    this->picture_flag->setPos(window->TILE_WIDTH * x, window->TILE_WIDTH * y + window->HUD_HEIGHT);
    this->picture_flag->setZValue(1);
    this->picture_flag->hide();
    window->scene->addItem(picture_flag);

}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "clicked " << "x:" << x << "  y: " << y;
}

void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    this->setBrush(hover_color);
    this->setPen(hover_color);
}
void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    this->setBrush(normal_color);
    this->setPen(normal_color);
}
