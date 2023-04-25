#ifndef NONLINEARFILTERIMAGEPROCESSOR_H
#define NONLINEARFILTERIMAGEPROCESSOR_H

#include "abstractimageprocessor.h"
#include <functional>

class NonlinearFilterImageProcessor : public AbstractImageProcessor
{
    QImage borderImg;
    int n;
    bool isMedianMode = false, isBilatrealMode = false;

public:

    void setMin();
    void setMax();
    void setMedian();
    void setBilateral();

    void setKernelSize(int size);

    void medianFilter(const QImage& srcWithBorder, QImage& dst, int r);
    void process(const QImage &src, QImage &dst) override;

    void border(const QImage &originalImage, QImage &border, int n);

    void bilateralFilter(QImage &src, QImage &dst, int kernel_size);
    double weight(int i, int j, int center_i, int center_j, double sigma_color, double sigma_space, QImage &src, int color_diff);
    void median(int r);
    QRgb filteredPixelValue(double sum_r, double weight_sum_r, double sum_g, double weight_sum_g, double sum_b, double weight_sum_b);
};

#endif // NONLINEARFILTERIMAGEPROCESSOR_H
