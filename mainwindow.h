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

        const QColor HUD_COLOR = QColor(76,116,50);
        const QColor TILE_EVEN_COLOR = QColor(171,214,93);
        const QColor TILE_ODD_COLOR = QColor(164,208,85);
        const QColor TILE_HOVER_COLOR = QColor(192,224,132);

        int TILE_WIDTH;
        int WIDTH_TILE_NUM;
        int HEIGHT_TILE_NUM;
        int MINE_NUM;
        int HUD_HEIGHT;
        int WINDOW_WIDTH;
        int WINDOW_HEIGHT;

        QGraphicsScene *scene;

    private:
        Ui::MainWindow *ui;

        void start();
};
#endif // MAINWINDOW_H
