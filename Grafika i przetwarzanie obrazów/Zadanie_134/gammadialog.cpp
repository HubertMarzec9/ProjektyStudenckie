#include "gammadialog.h"

GammaDialog::GammaDialog(GammaImageProcessor &gammaImageProcessor, QWidget *parent)
    : QDialog{parent}
{    
    this->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *gammaLabel = new QLabel(tr("Gamma"), this);

    QSlider *gammaSlider = new QSlider(Qt::Horizontal, this);
    gammaSlider->setRange(1, 100);

    QLabel *gammaValueLabel = new QLabel(0, this);

    QGridLayout *mainLayout = new QGridLayout(this);

    mainLayout->addWidget(gammaLabel,0,0,1,1);
    mainLayout->addWidget(gammaSlider,0,1,1,1);
    mainLayout->addWidget(gammaValueLabel,0,2,1,1);

    connect(gammaSlider, &QSlider::valueChanged, this, [&gammaImageProcessor, gammaValueLabel, this](float value) {
        gammaImageProcessor.setValue(value/10);
        gammaValueLabel->setText(QString::number(value/10));
        emit requestPreview();
    });
}
