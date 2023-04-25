#ifndef GammaDialog_H
#define GammaDialog_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QGridLayout>

#include "gammaimageprocessor.h"

class GammaDialog : public QDialog
{
    Q_OBJECT

public:
    GammaDialog(GammaImageProcessor &gammaImageProcessor, QWidget *parent = nullptr);

signals:
    void requestPreview();
};

#endif // GammaDialog_H
