#ifndef GAUSSIANDIALOG_H
#define GAUSSIANDIALOG_H

#include <QDialog>

#include "matrixfilterimageprocessor.h"

class GaussianDialog : public QDialog
{
    Q_OBJECT
public:
    GaussianDialog(MatrixFilterImageProcessor &processor, QWidget *parent = nullptr);

signals:
    void requestPreview();
};

#endif // GAUSSIANDIALOG_H
