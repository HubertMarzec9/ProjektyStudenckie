#ifndef NONLINEARFILTERDIALOG_H
#define NONLINEARFILTERDIALOG_H

#include <QDialog>

#include "nonlinearfilterimageprocessor.h"


class NonlinearFilterDialog : public QDialog
{
    Q_OBJECT

    NonlinearFilterImageProcessor &processor;

public:
    NonlinearFilterDialog(NonlinearFilterImageProcessor &processor, QWidget *parent = nullptr);

signals:
    void requestPreview();
    void requestOrginalImage();
};

#endif // NonlINEARFILTERDIALOG_H
