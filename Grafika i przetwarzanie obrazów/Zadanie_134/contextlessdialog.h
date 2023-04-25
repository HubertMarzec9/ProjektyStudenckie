#ifndef ContextlessDialog_H
#define ContextlessDialog_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QGridLayout>

#include "contextlessimageprocessor.h"

class ContextlessDialog : public QDialog
{
    Q_OBJECT

public:
    ContextlessDialog(ContextlessImageProcessor &contextlessImageProcessor, QWidget *parent = nullptr);

signals:
    void requestPreview();
};

#endif // ContextlessDialog_H
