#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>

#include <QScrollArea>
#include <QLabel>
#include <QMenu>

#include "contextlessimageprocessor.h"
#include "colorspaceimageprocessor.h"
#include "histogramwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QLabel *imageLabel;

    QImage image, previewImage;

    ColorspaceImageProcessor colorspaceImageProcessor;

    HistogramWidget *histogramWidget;


    void initializeMenus();
    void showLoadDialog();
    void showColorspaceDialog();
    void loadImage();

public:
    MainWindow(QWidget *parent = nullptr);
};
#endif // WIDGET_H
