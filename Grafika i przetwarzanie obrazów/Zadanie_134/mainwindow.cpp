#include "mainwindow.h"

#include <QMenuBar>
#include <QFileDialog>
#include <QApplication>
#include <QDockWidget>

#include "contextlessdialog.h"
#include "contrastdialog.h"
#include "gammadialog.h"
#include "matrixfilterdialog.h"
#include "gaussiandialog.h"
#include "nonlinearfilterdialog.h"

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

    /*
    QDockWidget *dock = new QDockWidget(tr("Histogram"), this);
    dock->setWidget(histogramWidget);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    */

    initializeMenus();

    loadImage(QDir::home().filePath("lena.png"));

}

void MainWindow::initializeMenus() {
    QMenu *fileMenu = this->menuBar()->addMenu(tr("File"));
    this->menuBar()->addMenu(fileMenu);

    QAction *loadAction = fileMenu->addAction(tr("Load"));
    QAction *exitAction = fileMenu->addAction(tr("Exit"));


    QMenu *filterMenu = this->menuBar()->addMenu(tr("Filters"));
    QAction *contextlessAction = filterMenu->addAction(tr("Contextless"));
    QAction *contrastAction = filterMenu->addAction(tr("Contrast"));
    QAction *gammaAction = filterMenu->addAction(tr("Gamma"));

    QMenu *contextMenu = filterMenu->addMenu(tr("Context filters"));
    QAction *matrixFilterAction = contextMenu->addAction(tr("Matrix"));
    QAction *gaussianFilterAction = contextMenu->addAction(tr("Gaussian"));
    QAction *nonlinearFilterAction = contextMenu->addAction(tr("Nonlinear"));

    connect(loadAction, &QAction::triggered, this, &MainWindow::showLoadDialog);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    connect(contextlessAction, &QAction::triggered, this, &MainWindow::showContextlessDialog);
    connect(contrastAction, &QAction::triggered, this, &MainWindow::showContrastDialog);
    connect(gammaAction, &QAction::triggered, this, &MainWindow::showGammaDialog);
    connect(matrixFilterAction, &QAction::triggered, this, &MainWindow::showMatrixFilterDialog);
    connect(gaussianFilterAction, &QAction::triggered, this, &MainWindow::showGaussianFilterDialog);
    connect(nonlinearFilterAction, &QAction::triggered, this, &MainWindow::showNonlinearFilterDialog);



}

void MainWindow::showLoadDialog() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Images (*.png *.xpm *.jpg)"));
    if(!fileName.isNull()) {
        loadImage(fileName);
    }
}

void MainWindow::loadImage(QString fileName) {
    image.load(fileName);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->resize(image.size());
    previewImage = image.copy();
}


void MainWindow::updateImage(AbstractImageProcessor *processor) {
    processor->process(image, previewImage);
    imageLabel->setPixmap(QPixmap::fromImage(previewImage));
    histogramWidget->updateHistograms(previewImage);
}

void MainWindow::showContextlessDialog() {
    ContextlessDialog *contextlessDialog = new ContextlessDialog(contextlessImageProcessor, this);
    contextlessDialog->show();
    connect(contextlessDialog, &ContextlessDialog::requestPreview, this, [this]() {
        updateImage(&contextlessImageProcessor);
    });
}

void MainWindow::showContrastDialog()
{
    ContrastDialog *contrastDialog = new ContrastDialog(contrastImageProcessor, this);
    contrastDialog->show();

    connect(contrastDialog, &ContrastDialog::requestPreview, this, [this](){
        contrastImageProcessor.process(image, previewImage);
        imageLabel->setPixmap(QPixmap::fromImage(previewImage));
    });
}

void MainWindow::showGammaDialog()
{
    GammaDialog *gammaDialog = new GammaDialog(gammaImageProcessor, this);
    gammaDialog->show();

    connect(gammaDialog, &GammaDialog::requestPreview, this, [this](){
        gammaImageProcessor.process(image, previewImage);
        imageLabel->setPixmap(QPixmap::fromImage(previewImage));
    });
}


void MainWindow::showMatrixFilterDialog() {
    MatrixFilterDialog *dialog = new MatrixFilterDialog(matrixFilterImageProcessor, this);
    dialog->show();
    connect(dialog, &MatrixFilterDialog::requestPreview, this,  [this]() {
        updateImage(&matrixFilterImageProcessor);
    });
}

void MainWindow::showGaussianFilterDialog() {
    GaussianDialog *dialog = new GaussianDialog(matrixFilterImageProcessor, this);
    dialog->show();
    connect(dialog, &GaussianDialog::requestPreview, this,  [this]() {
        updateImage(&matrixFilterImageProcessor);
    });
}

void MainWindow::clickCancelbutton(){
  previewImage = orginalimage.copy();
}


void MainWindow::showNonlinearFilterDialog() {
    NonlinearFilterDialog *dialog = new NonlinearFilterDialog(nonlinearFilterImageProcessor, this);
    dialog->show();
    connect(dialog, &NonlinearFilterDialog::requestPreview, this,  [this]() {
        updateImage(&nonlinearFilterImageProcessor);
    });

    connect(dialog, &NonlinearFilterDialog::requestOrginalImage, this, [this](){
        imageLabel->setPixmap(QPixmap::fromImage(orginalimage));
        clickCancelbutton();
      });
}

