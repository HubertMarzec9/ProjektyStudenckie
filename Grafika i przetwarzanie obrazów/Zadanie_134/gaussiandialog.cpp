#include "gaussiandialog.h"
#include <QLabel>
#include <QSlider>
#include <QGridLayout>

GaussianDialog::GaussianDialog(MatrixFilterImageProcessor &processor, QWidget *parent)
    : QDialog{parent}
{
    QLabel *kernelLabel = new QLabel(tr("Kernel size"), this);
    QSlider *kernelSlider = new QSlider(Qt::Horizontal, this);

    QLabel *unsharpLabel = new QLabel(tr("Unsharp Mask"), this);
    QSlider *unsharpSlider = new QSlider(Qt::Horizontal, this);
    unsharpSlider->setRange(0, 100);
    unsharpSlider->setMinimumWidth(200);
    kernelSlider->setRange(1, 11);
    kernelSlider->setMinimumWidth(200);

    QLabel *kernelValueLabel = new QLabel(0, this);
    kernelValueLabel->setFixedWidth(30);
    QLabel *unsharpValueLabel = new QLabel(0, this);
    unsharpValueLabel->setFixedWidth(30);
    QGridLayout *mainLayout = new QGridLayout(this);

    mainLayout->addWidget(kernelLabel,0,0,1,1);
    mainLayout->addWidget(kernelSlider,0,1,1,1);
    mainLayout->addWidget(kernelValueLabel,0,2,1,1);

    mainLayout->addWidget(unsharpLabel,1,0,1,1);
    mainLayout->addWidget(unsharpSlider,1,1,1,1);
    mainLayout->addWidget(unsharpValueLabel,1,2,1,1);


    connect(kernelSlider, &QSlider::valueChanged, this, [&processor, kernelLabel, kernelValueLabel, this](int value) {
        int k = value*2+1;
        processor.setGaussian(k);
        kernelValueLabel->setText(QString::number(k));
        emit requestPreview();
    });
    connect(unsharpSlider, &QSlider::valueChanged, this, [&processor, unsharpLabel, unsharpValueLabel, this](int value) {
        int k = value*2+1;
        processor.setUnsharpMask(k);
        unsharpValueLabel->setText(QString::number(k));
        emit requestPreview();
    });

}
