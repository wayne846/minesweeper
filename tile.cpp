#include "tile.h"
#include <QDebug>
#include "mainwindow.h"
#include <QGraphicsItem>

Tile::Tile(MainWindow *window, int x, int y, int type){
    this->window = window;
    this->x = x;
    this->y = y;
    this->type = type;

    //set tile
    this->setRect(window->TILE_WIDTH * x, window->TILE_WIDTH * y + window->HUD_HEIGHT, window->TILE_WIDTH, window->TILE_WIDTH);
    if((x+y)%2 == 0){
        normal_color = window->TILE_EVEN_COLOR;
        clicked_color = window->TILE_CLICKED_EVEN_COLOR;
    }else{
        normal_color = window->TILE_ODD_COLOR;
        clicked_color = window->TILE_CLICKED_ODD_COLOR;
    }
    hover_color = window->TILE_HOVER_COLOR;
    this->setBrush(normal_color);
    this->setPen(normal_color);
    this->setAcceptHoverEvents(true);

    //set image_flag
    QPixmap pixmap = QPixmap(":/flag.png");
    pixmap = pixmap.scaled(QSize(window->TILE_WIDTH, window->TILE_WIDTH));
    this->image_flag = new QGraphicsPixmapItem(pixmap);
    this->image_flag->setPos(window->TILE_WIDTH * x, window->TILE_WIDTH * y + window->HUD_HEIGHT);
    this->image_flag->setZValue(1);
    this->image_flag->hide();
    window->scene->addItem(image_flag);

    //set image_type
    if(type == -1){
        pixmap.load(":/mine.png");
        pixmap = pixmap.scaled(QSize(window->TILE_WIDTH, window->TILE_WIDTH));
        this->image_type = new QGraphicsPixmapItem(pixmap);
        this->image_type->setPos(window->TILE_WIDTH * x, window->TILE_WIDTH * y + window->HUD_HEIGHT);
    }else{
        QGraphicsTextItem *text = new QGraphicsTextItem("");
        if(type != 0) text->setPlainText(QString::number(type));
        switch(type){
            case 0:
                break;
            case 1:
                text->setDefaultTextColor(window->ONE_COLOR);
                break;
            case 2:
                text->setDefaultTextColor(window->TWO_COLOR);
                break;
            case 3:
                text->setDefaultTextColor(window->THREE_COLOR);
                break;
            case 4:
                text->setDefaultTextColor(window->FOUR_COLOR);
                break;
            case 5:
                text->setDefaultTextColor(window->FIVE_COLOR);
                break;
            case 6:
                text->setDefaultTextColor(window->SIX_COLOR);
                break;
            case 7:
                text->setDefaultTextColor(window->SEVEN_COLOR);
                break;
            case 8:
                text->setDefaultTextColor(window->EIGHT_COLOR);
                break;
        }
        text->setFont(QFont("New Times Roman", window->TILE_WIDTH/50.0 * 27));
        text->setPos(window->TILE_WIDTH * x + window->TILE_WIDTH/2.0 - text->boundingRect().width()/2.0, window->TILE_WIDTH * y + window->TILE_WIDTH - text->boundingRect().height() + window->HUD_HEIGHT);
        this->image_type = text;
    }
    this->image_type->setZValue(1);
    this->image_type->hide();
    window->scene->addItem(image_type);

    //set other value
    this->isFlag = false;
    this->hadClicked = false;
}

void Tile::click(){
    qDebug() << "clicked " << "x:" << x << "  y: " << y;
    this->setBrush(clicked_color);
    this->setPen(clicked_color);
    this->setAcceptHoverEvents(false);
    image_type->show();
    hadClicked = true;
}

void Tile::setFlag(){
    if(isFlag){
        image_flag->hide();
        isFlag = false;
    }else{
        image_flag->show();
        isFlag = true;
    }
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event){
    switch(event->button()){
        case Qt::LeftButton:
            if(!isFlag && !hadClicked) click();
            break;
        case Qt::RightButton:
            if(!hadClicked) setFlag();
            break;
        default:
            break;
    }
}

void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    this->setBrush(hover_color);
    this->setPen(hover_color);
}
void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    this->setBrush(normal_color);
    this->setPen(normal_color);
}
