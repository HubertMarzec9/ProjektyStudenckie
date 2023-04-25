#include "colorspacedialog.h"

#include <QFrame>
#include <QGridLayout>
#include <QRadioButton>
#include <QHBoxLayout>

ColorspaceDialog::ColorspaceDialog(ColorspaceImageProcessor &processor, QWidget *parent) : QDialog{parent}, processor(processor) {

    QRadioButton *rgbButton = new QRadioButton(tr("RGB"),this);
    QRadioButton *hslButton = new QRadioButton(tr("HSL"),this);
    QRadioButton *clabButton = new QRadioButton(tr("CLAB"),this);

    QHBoxLayout *colorspaceOptionsLayout = new QHBoxLayout();
    colorspaceOptionsLayout->addWidget(rgbButton);
    colorspaceOptionsLayout->addWidget(hslButton);
    colorspaceOptionsLayout->addWidget(clabButton);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addLayout(colorspaceOptionsLayout,0,0,1,3);

    for(int i=0; i<3; i++) {
        channelLabels[i] = new QLabel(this);
        channelLabels[i]->setFixedWidth(20);

        channelValueLabels[i] = new QLabel(this);
        channelValueLabels[i]->setFixedWidth(30);

        channelSliders[i] = new QSlider(Qt::Horizontal, this);
        channelSliders[i]->setRange(-255,255);
        channelSliders[i]->setValue(0);

        mainLayout->addWidget(channelLabels[i], 1+i, 0, 1, 1);
        mainLayout->addWidget(channelSliders[i], 1+i, 1, 1, 1);
        mainLayout->addWidget(channelValueLabels[i], 1+i, 2, 1, 1);


        connect(channelSliders[i], &QSlider::valueChanged, this, &ColorspaceDialog::updateValues);
    }

    connect(rgbButton, &QRadioButton::clicked, this, &ColorspaceDialog::setRgb);
    connect(hslButton, &QRadioButton::clicked, this, &ColorspaceDialog::setHsl);
    connect(clabButton, &QRadioButton::clicked, this, &ColorspaceDialog::setClab);

    setRgb();
}

void ColorspaceDialog::updateValues() {
    for(int i=0; i<3; i++)
        channelValueLabels[i]->setText(QString::number(channelSliders[i]->value()));

    processor.setOffset(channelSliders[0]->value(), channelSliders[1]->value(), channelSliders[2]->value());
    emit requestPreview();
}

void ColorspaceDialog::setRgb() {
    channelLabels[0]->setText("R");
    channelLabels[1]->setText("G");
    channelLabels[2]->setText("B");
    processor.setRgbMode();
}

void ColorspaceDialog::setHsl() {
    channelLabels[0]->setText("H");
    channelLabels[1]->setText("S");
    channelLabels[2]->setText("L");
    processor.setHslMode();
}

void ColorspaceDialog::setClab(){
  channelLabels[0]->setText("L");
  channelLabels[1]->setText("A");
  channelLabels[2]->setText("B");
  processor.setClabMode();
}
