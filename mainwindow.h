#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <vector>

using namespace std;

class Tile;

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
        const QColor TILE_CLICKED_EVEN_COLOR = QColor(228,194,162);
        const QColor TILE_CLICKED_ODD_COLOR = QColor(214,184,155);
        const QColor TILE_HOVER_COLOR = QColor(192,224,132);

        const QColor ONE_COLOR = QColor(56,126,199);
        const QColor TWO_COLOR = QColor(77,146,74);
        const QColor THREE_COLOR = QColor(212,83,78);
        const QColor FOUR_COLOR = QColor(129,48,158);
        const QColor FIVE_COLOR = QColor(242,155,67);
        const QColor SIX_COLOR = QColor(61,158,164);
        const QColor SEVEN_COLOR = QColor(93,88,83);
        const QColor EIGHT_COLOR = QColor(174,166,158);

        int TILE_WIDTH;
        int WIDTH_TILE_NUM;
        int HEIGHT_TILE_NUM;
        int MINE_NUM;
        int HUD_HEIGHT;
        int WINDOW_WIDTH;
        int WINDOW_HEIGHT;

        QGraphicsScene *scene;
        vector<vector<Tile*>> tileMap; //[y][x]

        bool hadFirstClick;
        bool isDead;
        bool isWin;

        void createMap(int startX, int startY);
        void die();
        void changeFlagCount(bool f); //true: flagCount++   false: flagCount--
        void safeClick(); //check if win

    private slots:
        void update();
        void dieAnimation();

        void on_actioneasy_triggered();

        void on_actionmiddle_triggered();

        void on_actionhard_triggered();

        void on_actionsize60_triggered();

        void on_actionsize80_triggered();

        void on_actionsize100_triggered();

        void on_actionsize120_triggered();

        void on_actionsize140_triggered();

    private:
        Ui::MainWindow *ui;

        QTimer *timer_dieAnimation;
        QTimer *timer_game;
        int gameTime;
        int flagCount;
        int safeTile_num;
        double sizePercent;
        int difficulty;

        QGraphicsTextItem *text_flagCount;
        QGraphicsTextItem *text_gameTime;

        void start();
        void setDifficulty(int n);
};
#endif // MAINWINDOW_H
