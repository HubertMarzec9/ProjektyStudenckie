#include "mainwindow.h"
#include "canvas.h"

#include <QScrollArea>
#include <QToolBar>
#include <QFileDialog>
#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QScrollArea *scrollArea = new QScrollArea(this);
    canvas = new Canvas(this);

    this->resize(1500,900);


    scrollArea->setWidget(canvas);
    scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    this->setCentralWidget(scrollArea);

    initializeToolbar();

    clearCanvas();
    setMove();

}

void MainWindow::initializeToolbar() {
    QToolBar *toolbar = new QToolBar(this);
    this->addToolBar(Qt::LeftToolBarArea, toolbar);
    toolbar->setMovable(false);

    QAction *newAction = toolbar->addAction(tr("New"));
    QAction *loadAction = toolbar->addAction(tr("Load"));
    toolbar->addSeparator();
    QAction *moveAction = toolbar->addAction(tr("Move"));
    QAction *scaleAction = toolbar->addAction(tr("Scale"));
    QAction *rotateAction = toolbar->addAction(tr("Rotate"));
    QAction *shearAction = toolbar->addAction(tr("Shear"));

    moveAction->setCheckable(true);
    scaleAction->setCheckable(true);
    rotateAction->setCheckable(true);
    shearAction->setCheckable(true);

    QActionGroup *transformGroup = new QActionGroup(this);
    transformGroup->addAction(moveAction);
    transformGroup->addAction(scaleAction);
    transformGroup->addAction(rotateAction);
    transformGroup->addAction(shearAction);

    connect(newAction, &QAction::triggered, this, &MainWindow::clearCanvas);
    connect(loadAction, &QAction::triggered, this, &MainWindow::showLoadDialog);
    connect(moveAction, &QAction::triggered, this, &MainWindow::setMove);
    connect(scaleAction, &QAction::triggered, this, &MainWindow::setScale);
    connect(rotateAction, &QAction::triggered, this, &MainWindow::setRotate);
    connect(shearAction, &QAction::triggered, this, &MainWindow::setShear);
}

void MainWindow::clearCanvas() {
    canvas->resize(QSize(1500, 1000));
    canvas->update();
}


void MainWindow::showLoadDialog() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Images (*.png *.xpm *.jpg)"));
    if(!fileName.isNull()) {
        canvas->loadImage(fileName);
    }
}

void MainWindow::setMove() {
    canvas->setMode(Canvas::Move);
}

void MainWindow::setScale() {
    canvas->setMode(Canvas::Scale);
}

void MainWindow::setRotate() {
    canvas->setMode(Canvas::Rotate);
}

void MainWindow::setShear() {
    canvas->setMode(Canvas::Shear);
}
