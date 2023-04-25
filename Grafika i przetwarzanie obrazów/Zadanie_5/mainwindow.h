#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Canvas;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Canvas *canvas;

    void initializeToolbar();

    void clearCanvas();
    void showLoadDialog();
    void setMove();
    void setScale();
    void setRotate();
    void setShear();

public:
    MainWindow(QWidget *parent = nullptr);
};
#endif // MAINWINDOW_H
