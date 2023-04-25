#include "histogramwidget.h"

#include <QVBoxLayout>
#include <QRgb>
#include <QPainter>

#include <iostream>

HistogramWidget::HistogramWidget(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(276);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    for(int i=0; i<4; i++) {
        histogramPixmaps[i] = QPixmap(QSize(256,100));
        histogramPixmaps[0].fill(Qt::black);
        histogramLabels[i] = new QLabel(this);
        histogramLabels[i]->setPixmap(histogramPixmaps[0]);
        mainLayout->addWidget(histogramLabels[i]);
    }
    mainLayout->addStretch(1);
}



void HistogramWidget::updateHistograms(const QImage &image) {

}

