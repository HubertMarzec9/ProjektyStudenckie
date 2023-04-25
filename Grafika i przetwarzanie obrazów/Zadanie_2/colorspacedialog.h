#ifndef COLORSPACEDIALOG_H
#define COLORSPACEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSlider>

#include "colorspaceimageprocessor.h"

class ColorspaceDialog : public QDialog
{
    Q_OBJECT

    ColorspaceImageProcessor &processor;

    QLabel *channelLabels[3], *channelValueLabels[3];
    QSlider *channelSliders[3];

    void setRgb();
    void setHsl();
    void setClab();
    void updateValues();


public:
    explicit ColorspaceDialog(ColorspaceImageProcessor &processor, QWidget *parent = nullptr);

signals:
    void requestPreview();

};

#endif // COLORSPACEDIALOG_H
