#ifndef MATRIXFILTERDIALOG_H
#define MATRIXFILTERDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include "matrixfilterimageprocessor.h"

class MatrixFilterDialog : public QDialog
{
    Q_OBJECT
    MatrixFilterImageProcessor &processor;
    void updateValues();

public:
    MatrixFilterDialog(MatrixFilterImageProcessor &processor, QWidget *parent = nullptr);

signals:
    void requestPreview();

};

#endif // MATRIXFILTERDIALOG_H
