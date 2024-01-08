#include "tile.h"
#include <QDebug>
#include "mainwindow.h"

Tile::Tile(MainWindow *window, int x, int y){
    this->window = window;
    this->x = x;
    this->y = y;
    this->setRect(window->TILE_WIDTH * x, window->TILE_WIDTH * y, window->TILE_WIDTH, window->TILE_WIDTH);

}
void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "clicked";
}
