#include "mainwindow.h"

#include <QMenuBar>
#include <QFileDialog>
#include <QApplication>
#include <QDockWidget>

#include "contextlessdialog.h"
#include "colorspacedialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(800,600);

    QScrollArea *scrollArea = new QScrollArea(this);
    this->setCentralWidget(scrollArea);

    imageLabel = new QLabel(this);
    scrollArea->setWidget(imageLabel);
    scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    histogramWidget = new HistogramWidget(this);

    //QDockWidget *dock = new QDockWidget(tr("Histogram"), this);
    //dock->setWidget(histogramWidget);
    //dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //addDockWidget(Qt::RightDockWidgetArea, dock);

    initializeMenus();
}

void MainWindow::initializeMenus() {
    QMenu *fileMenu = this->menuBar()->addMenu(tr("File"));
    this->menuBar()->addMenu(fileMenu);

    QAction *loadAction = fileMenu->addAction(tr("Load"));
    QAction *exitAction = fileMenu->addAction(tr("Exit"));


    QMenu *filterMenu = this->menuBar()->addMenu(tr("Filters"));
    QAction *colorspaceAction = filterMenu->addAction(tr("Colorspace"));

    connect(loadAction, &QAction::triggered, this, &MainWindow::showLoadDialog);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    connect(colorspaceAction, &QAction::triggered, this, &MainWindow::showColorspaceDialog);


}

void MainWindow::showLoadDialog() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Images (*.png *.xpm *.jpg)"));
    if(!fileName.isNull()) {
        image.load(fileName);
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->resize(image.size());
        previewImage = image.copy();
    }
}

void MainWindow::showColorspaceDialog() {
    ColorspaceDialog *dialog = new ColorspaceDialog(colorspaceImageProcessor, this);
    dialog->show();

    connect(dialog, &ColorspaceDialog::requestPreview, this, [this](){
        colorspaceImageProcessor.process(image, previewImage);
        imageLabel->setPixmap(QPixmap::fromImage(previewImage));
        histogramWidget->updateHistograms(previewImage);
    });


}




