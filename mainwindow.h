#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        int TILE_WIDTH;
        int WIDTH_TILE_NUM;
        int HEIGHT_TILE_NUM;
        int MINE_NUM;
        int WINDOW_WIDTH;
        int WINDOW_HEIGHT;

    private:
        Ui::MainWindow *ui;
        QGraphicsScene *scene;

        void start();
};
#endif // MAINWINDOW_H
