#include "nonlinearfilterdialog.h"
#include <QRadioButton>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QHBoxLayout>
#include <qpushbutton.h>

NonlinearFilterDialog::NonlinearFilterDialog(NonlinearFilterImageProcessor &processor, QWidget *parent)
    : QDialog(parent), processor(processor) {

    //QRadioButton *minButton = new QRadioButton(tr("Minimum"),this);
    //QRadioButton *maxButton = new QRadioButton(tr("Maximum"),this);
    QRadioButton *medianButton = new QRadioButton(tr("Median"),this);
    QRadioButton *bilateralButton = new QRadioButton(tr("Bilateral"),this);

    QLabel *sizeLabel = new QLabel(tr("Kernel radius"), this);
    QSlider *sizeSlider = new QSlider(Qt::Horizontal, this);
    QLabel *sizeValueLabel = new QLabel(this);
    sizeValueLabel->setFixedHeight(30);

    sizeSlider->setRange(0, 15);

    QHBoxLayout *modeLayout = new QHBoxLayout();
    //modeLayout->addWidget(minButton);
    //modeLayout->addWidget(maxButton);
    modeLayout->addWidget(medianButton);
    modeLayout->addWidget(bilateralButton);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addLayout(modeLayout,0,0,1,3);
    mainLayout->addWidget(sizeLabel,1,0,1,1);
    mainLayout->addWidget(sizeSlider,1,1,1,1);
    mainLayout->addWidget(sizeValueLabel,1,2,1,1);
/*
    connect(minButton, &QRadioButton::clicked, this, [this, &processor]() {
        processor.setMin();
        emit requestPreview();
    });

    connect(maxButton, &QRadioButton::clicked, this, [this, &processor]() {
        processor.setMax();
        emit requestPreview();
    });
*/
    connect(medianButton, &QRadioButton::clicked, this, [this, &processor]() {
        processor.setMedian();
        emit requestPreview();
    });

    connect(bilateralButton, &QRadioButton::clicked, this, [this, &processor]() {
        processor.setBilateral();
        emit requestPreview();
    });

    auto updateSize = [this, &processor, sizeValueLabel](int value){
        sizeValueLabel->setText(QString::number(value*2+1));
        processor.setKernelSize(value*2+1);
        emit requestPreview();
    };

    connect(sizeSlider, &QSlider::valueChanged, this, updateSize);

    updateSize(0);
    processor.setMin();
    //minButton->setChecked(true);
}
