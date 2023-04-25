#include "contextlessdialog.h"

ContextlessDialog::ContextlessDialog(ContextlessImageProcessor &contextlessImageProcessor, QWidget *parent)
    : QDialog{parent}
{    
    this->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *brightnessLabel = new QLabel(tr("Brightness"), this);

    QSlider *brightnessSlider = new QSlider(Qt::Horizontal, this);
    brightnessSlider->setRange(-255, 255);

    QLabel *brightnessValueLabel = new QLabel(0, this);
    brightnessValueLabel->setFixedWidth(30);

    QGridLayout *mainLayout = new QGridLayout(this);

    mainLayout->addWidget(brightnessLabel,0,0,1,1);
    mainLayout->addWidget(brightnessSlider,0,1,1,1);
    mainLayout->addWidget(brightnessValueLabel,0,2,1,1);

    connect(brightnessSlider, &QSlider::valueChanged, this, [&contextlessImageProcessor, brightnessValueLabel, this](int value) {
        contextlessImageProcessor.setBrightness(value);
        brightnessValueLabel->setText(QString::number(value));
        emit requestPreview();
    });
}
