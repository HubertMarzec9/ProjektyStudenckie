#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QWidget>
#include <QLabel>

class HistogramWidget : public QWidget
{
    QLabel* histogramLabels[4];
    QPixmap histogramPixmaps[4];

public:
    HistogramWidget(QWidget *parent = nullptr);
    void updateHistograms(const QImage &image);


};

#endif // HISTOGRAMWIDGET_H
