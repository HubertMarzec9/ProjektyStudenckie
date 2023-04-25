#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>

#include <QScrollArea>
#include <QLabel>
#include <QMenu>

#include "contextlessimageprocessor.h"
#include "matrixfilterimageprocessor.h"
#include "nonlinearfilterimageprocessor.h"

#include "histogramwidget.h"
#include "gammaimageprocessor.h"
#include "contrastimageprocessor.h"

class AbstractImageProcessor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QLabel *imageLabel;

    QImage image, previewImage, orginalimage;

    ContextlessImageProcessor contextlessImageProcessor;
    GammaImageProcessor gammaImageProcessor;
    ContrastImageProcessor contrastImageProcessor;
    MatrixFilterImageProcessor matrixFilterImageProcessor;
    NonlinearFilterImageProcessor nonlinearFilterImageProcessor;

    HistogramWidget *histogramWidget;


    void initializeMenus();
    void showLoadDialog();
    void showContextlessDialog();
    void showContrastDialog();
    void showGammaDialog();
    void showMatrixFilterDialog();
    void showGaussianFilterDialog();
    void showNonlinearFilterDialog();

    void loadImage(QString fileName);

    void updateImage(AbstractImageProcessor *);

public:
    MainWindow(QWidget *parent = nullptr);
    void clickCancelbutton();
};
#endif // WIDGET_H
