#ifndef ContrastDialog_H
#define ContrastDialog_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QGridLayout>

#include "contrastimageprocessor.h"

class ContrastDialog : public QDialog
{
    Q_OBJECT

public:
    ContrastDialog(ContrastImageProcessor &contrastImageProcessor, QWidget *parent = nullptr);

signals:
    void requestPreview();
};

#endif //ContrastDialog_H
