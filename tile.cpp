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
    this->hasClicked = false;
}

void Tile::click(){
    if(hasClicked) return;

    //qDebug() << "clicked " << "x:" << x << "  y: " << y;
    this->setBrush(clicked_color);
    this->setPen(clicked_color);
    this->setAcceptHoverEvents(false);
    image_type->show();
    if(isFlag) setFlag();
    hasClicked = true;
    if(type == 0) openBlank();
    if(type == -1) window->die();
}

void Tile::setFlag(){
    if(isFlag){
        image_flag->hide();
        isFlag = false;
        window->changeFlagCount(true);
    }else{
        image_flag->show();
        isFlag = true;
        window->changeFlagCount(false);
    }
}

void Tile::setType(int t){
    if(type == t) return;
    type = t;
    delete(image_type);
    if(type == -1){
        QPixmap pixmap = QPixmap();
        pixmap.load(":/mine.png");
        pixmap = pixmap.scaled(QSize(window->TILE_WIDTH, window->TILE_WIDTH));
        image_type = new QGraphicsPixmapItem(pixmap);
        image_type->setPos(window->TILE_WIDTH * x, window->TILE_WIDTH * y + window->HUD_HEIGHT);
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
        image_type = text;
    }
    image_type->setZValue(1);
    if(!hasClicked) image_type->hide();
    window->scene->addItem(image_type);
}

int Tile::getType(){
    return type;
}

bool Tile::getHasClicked(){
    return hasClicked;
}

bool Tile::getIsFlag(){
    return isFlag;
}

void Tile::openBlank(){
    if(type != 0) return;
    for(int i = y-1; i <= y+1; i++){
        for(int j = x-1; j <= x+1; j++){
            if(i >= 0 && i < window->HEIGHT_TILE_NUM &&
               j >= 0 && j < window->WIDTH_TILE_NUM &&
               window->tileMap[i][j]->getType() != -1){
                window->tileMap[i][j]->click();
            }
        }
    }
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(window->isDead) return;
    switch(event->button()){
        case Qt::LeftButton:
            if(!isFlag && !hasClicked){
                if(!window->hadFirstClick) window->createMap(x, y);
                click();
            }
            break;
        case Qt::RightButton:
            if(!hasClicked) setFlag();
            break;
        default:
            break;
    }
}

void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    if(window->isDead) return;
    this->setBrush(hover_color);
    this->setPen(hover_color);
}
void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    this->setBrush(normal_color);
    this->setPen(normal_color);
}

Tile::~Tile(){
    delete(image_flag);
    delete(image_type);
}
