#include "contrastdialog.h"

ContrastDialog::ContrastDialog(ContrastImageProcessor &contrastImageProcessor, QWidget *parent)
    : QDialog{parent}
{    
    this->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *contrastLabel = new QLabel(tr("Contrast"), this);

    QSlider *contrastSlider = new QSlider(Qt::Horizontal, this);
    contrastSlider->setRange(-1, 30);

    QLabel *contrastValueLabel = new QLabel(0, this);

    QGridLayout *mainLayout = new QGridLayout(this);

    mainLayout->addWidget(contrastLabel,0,0,1,1);
    mainLayout->addWidget(contrastSlider,0,1,1,1);
    mainLayout->addWidget(contrastValueLabel,0,2,1,1);

    connect(contrastSlider, &QSlider::valueChanged, this, [&contrastImageProcessor, contrastValueLabel, this](float value) {
        contrastImageProcessor.setValue(value/10);
        contrastValueLabel->setText(QString::number(((value/10) <= 0) ? -1 : value/10));
        emit requestPreview();
    });
}
