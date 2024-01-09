#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tile.h"
#include <QScreen>
#include <QGraphicsPixmapItem>
#include <time.h>
#include <stdlib.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    //game value
    TILE_WIDTH = 50;
    WIDTH_TILE_NUM = 9;
    HEIGHT_TILE_NUM = 9;
    MINE_NUM = 10;
    HUD_HEIGHT = 70;
    WINDOW_WIDTH = TILE_WIDTH * WIDTH_TILE_NUM;
    WINDOW_HEIGHT = TILE_WIDTH * HEIGHT_TILE_NUM + HUD_HEIGHT;

    //timer
    timer_dieAnimation = new QTimer(this);
    connect(timer_dieAnimation, SIGNAL(timeout()), this, SLOT(dieAnimation()));
    timer_game = new QTimer(this);
    connect(timer_game, SIGNAL(timeout()), this, SLOT(update()));

    start();
}

void MainWindow::start(){
    //set some value
    hadFirstClick = false;
    isDead = false;
    flagCount = MINE_NUM;
    gameTime = 0;

    //set mainwindow
    this->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->setMaximumSize(this->size());
    this->setMinimumSize(this->size());
    QRect screenSize = this->screen()->geometry();
    this->move(screenSize.width()/2.0 - WINDOW_WIDTH/2.0, screenSize.height()/2.0 - WINDOW_HEIGHT/2.0);

    //set view
    ui->graphicsView->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //set scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    scene->addRect(QRect(0, 0, WINDOW_WIDTH, HUD_HEIGHT), QPen(HUD_COLOR), QBrush(HUD_COLOR));
    ui->graphicsView->setScene(scene);

    //set hud
    QPixmap pixmap1 = QPixmap(":/flag.png"); //flag image
    int ui_height = HUD_HEIGHT * 0.7;
    pixmap1 = pixmap1.scaled(QSize(ui_height, ui_height));
    QGraphicsPixmapItem *image1 = new QGraphicsPixmapItem(pixmap1);
    image1->setPos(WINDOW_WIDTH/2.0 - ui_height*2.1, HUD_HEIGHT/2.0 - ui_height/2.0);
    scene->addItem(image1);
    QPixmap pixmap2 = QPixmap(":/clock.png"); //clock image
    pixmap2 = pixmap2.scaled(QSize(ui_height, ui_height));
    QGraphicsPixmapItem *image2 = new QGraphicsPixmapItem(pixmap2);
    image2->setPos(WINDOW_WIDTH/2.0, HUD_HEIGHT/2.0 - ui_height/2.0);
    scene->addItem(image2);
    text_flagCount = new QGraphicsTextItem(QString::number(flagCount)); //text_flagCount
    text_flagCount->setDefaultTextColor(Qt::white);
    text_flagCount->setFont(QFont("Rockwell", ui_height/50.0 * 22));
    text_flagCount->setPos(WINDOW_WIDTH/2.0 - ui_height*1.1, HUD_HEIGHT/2.0 - text_flagCount->boundingRect().height()/2.0);
    scene->addItem(text_flagCount);
    text_gameTime = new QGraphicsTextItem(QString::number(gameTime)); //text_flagCount
    text_gameTime->setDefaultTextColor(Qt::white);
    text_gameTime->setFont(QFont("Rockwell", ui_height/50.0 * 22));
    text_gameTime->setPos(WINDOW_WIDTH/2.0 + ui_height*1.1, HUD_HEIGHT/2.0 - text_gameTime->boundingRect().height()/2.0);
    scene->addItem(text_gameTime);

    //init tileMap
    for(int i = 0; i < tileMap.size(); i++){
        for(int j = 0; j < tileMap[0].size(); j++){
            if(tileMap[i][j] != NULL) delete(tileMap[i][j]);
        }
    }
    tileMap.clear();
    for(int i = 0; i < HEIGHT_TILE_NUM; i++){
        vector<Tile*> v;
        for(int j = 0; j < WIDTH_TILE_NUM; j++){
            Tile *tile = new Tile(this, j, i, 0);
            scene->addItem(tile);
            v.push_back(tile);
        }
        tileMap.push_back(v);
    }

    //set timer
    timer_dieAnimation->stop();
    timer_game->stop();
}

void MainWindow::die(){
    isDead = true;
    if(!timer_dieAnimation->isActive()){
        timer_dieAnimation->start(130 + 1700 / MINE_NUM);
    }
}

void MainWindow::dieAnimation(){
    for(int i = 0; i < HEIGHT_TILE_NUM * WIDTH_TILE_NUM; i++){
        int x = i % WIDTH_TILE_NUM;
        int y = i / WIDTH_TILE_NUM;
        Tile *tile = tileMap[y][x];
        if(!tile->getHasClicked() && !tile->getIsFlag() && tile->getType() == -1){ //show mine which not be found
            tile->click();
            break;
        }
        if(!tile->getHasClicked() && tile->getIsFlag() && tile->getType() != -1){ //clear wrong answer
            tile->setFlag();
            break;
        }
    }
}

void MainWindow::update(){
    if(isDead) return;
    gameTime++;
    text_gameTime->setPlainText(QString::number(gameTime));
}

void MainWindow::changeFlagCount(bool f){
    if(f){
        flagCount++;
    }else{
        flagCount--;
    }
    text_flagCount->setPlainText(QString::number(flagCount));
}

void MainWindow::createMap(int startX, int startY){
    //qDebug() << "startX:" << startX << "  startY: " << startY;
    vector<vector<int>> typeMap;
    srand(time(NULL));
    //init typeMap
    for(int i = 0; i < HEIGHT_TILE_NUM; i++){
        vector<int> v;
        for(int j = 0; j < WIDTH_TILE_NUM; j++){
            v.push_back(0);
        }
        typeMap.push_back(v);
    }
    //make mine
    int n = 0;
    for(int i = 0; n < MINE_NUM && i < HEIGHT_TILE_NUM * WIDTH_TILE_NUM; i++){
        int x = i % WIDTH_TILE_NUM;
        int y = i / WIDTH_TILE_NUM;
        if(x >= startX-1 && x <= startX+1 && y >= startY-1 && y <= startY+1) continue;
        typeMap[y][x] = -1;
        n++;
    }
    //random
    for(int i = 0; i < HEIGHT_TILE_NUM; i++){
        for(int j = 0; j < WIDTH_TILE_NUM; j++){
            if(j >= startX-1 && j <= startX+1 && i >= startY-1 && i <= startY+1) continue;
            int x = rand() % WIDTH_TILE_NUM;
            int y = rand() % HEIGHT_TILE_NUM;
            while(x >= startX-1 && x <= startX+1 && y >= startY-1 && y <= startY+1){
                x = rand() % WIDTH_TILE_NUM;
                y = rand() % HEIGHT_TILE_NUM;
            }
            int t = typeMap[i][j];
            typeMap[i][j] = typeMap[y][x];
            typeMap[y][x] = t;
        }
    }
    //set number near mine
    for(int i = 0; i < HEIGHT_TILE_NUM; i++){
        for(int j = 0; j < WIDTH_TILE_NUM; j++){
            if(typeMap[i][j] != -1) continue;

            for(int k = i-1; k <= i+1; k++){
                for(int h = j-1; h <= j+1; h++){
                    if(k >= 0 && k < HEIGHT_TILE_NUM &&
                       h >= 0 && h < WIDTH_TILE_NUM &&
                       typeMap[k][h] != -1){
                        typeMap[k][h]++;
                    }
                }
            }
        }
    }
    //make it become real
    for(int i = 0; i < HEIGHT_TILE_NUM; i++){
        for(int j = 0; j < WIDTH_TILE_NUM; j++){
            tileMap[i][j]->setType(typeMap[i][j]);
        }
    }
    if(!timer_game->isActive()){
        timer_game->start(1000);
    }
    hadFirstClick = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

