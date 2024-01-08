#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tile.h"
#include <QScreen>
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    TILE_WIDTH = 50;
    WIDTH_TILE_NUM = 9;
    HEIGHT_TILE_NUM = 9;
    MINE_NUM = 10;
    HUD_HEIGHT = 100;
    WINDOW_WIDTH = TILE_WIDTH * WIDTH_TILE_NUM;
    WINDOW_HEIGHT = TILE_WIDTH * HEIGHT_TILE_NUM + HUD_HEIGHT;

    start();
}

void MainWindow::start(){
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

    //set screen
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    for(int i = 0; i < HEIGHT_TILE_NUM; i++){
        for(int j = 0; j < WIDTH_TILE_NUM; j++){
            Tile *tile = new Tile(this, j, i);
            scene->addItem(tile);
        }
    }
    scene->addRect(QRect(0, 0, WINDOW_WIDTH, HUD_HEIGHT), QPen(HUD_COLOR), QBrush(HUD_COLOR));

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

