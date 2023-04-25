#ifndef MATRIXFILTERIMAGEPROCESSOR_H
#define MATRIXFILTERIMAGEPROCESSOR_H

#include <memory>
#include <vector>
#include <QImage>

#include "abstractimageprocessor.h"

class MatrixFilterImageProcessor : public AbstractImageProcessor
{
    std::unique_ptr<std::vector<float>> matrix;
    QImage border_img;
    float alfa;
    int matWidth, matHeight, n;
    float div, halfMatWidth, halfMatHeight;

    QRgb processPixel(int cy, int cx, const QImage &src);

public:
    void setValues(std::unique_ptr<std::vector<float>> &&matrix, int height, int width);
    void setGaussian(int kernel);
    void setUnsharpMask(int kernel);
    void border(const QImage& src,QImage& border_img,int kernel);
    void conv2D_sep(QImage &border_img, QImage& processedImage,const std::unique_ptr<std::vector<float>> &mask, int n);
    void conv2D_px(const QRgb* pixel_dst,QRgb& pixel_src,const std::unique_ptr<std::vector<float>> &mask,const int* mask_it,const int& mask_sum);
    void pictureDiff(const QImage &src, QImage &dst);
    void pictureAdd(const QImage & src, QImage &dst,const float &alfa);
    void process(const QImage &src, QImage &dst) override;

};

#endif // MATRIXFILTERIMAGEPROCESSOR_H
