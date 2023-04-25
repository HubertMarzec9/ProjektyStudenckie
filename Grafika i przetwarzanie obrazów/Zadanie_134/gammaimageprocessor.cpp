#include "gammaimageprocessor.h"

uchar GammaImageProcessor::processChannel(uchar channel) {
    channel = processGamma(channel);
    return channel;
}

void GammaImageProcessor::setValue(float value){
    this->value = value;
}

uchar GammaImageProcessor::processGamma(const uchar &src) {
    if(std::pow(src / 255.0, value) * 255.0 >= 255)
        return 255;
    else if(std::pow(src / 255.0, value) * 255.0 <= 0)
        return 0;
    else
        return std::pow(src / 255.0, value) * 255.0;
}

void GammaImageProcessor::process(const QImage &src, const QImage &dst) {
    for(int y=0; y<dst.height(); y++) {
        QRgb* pixel_dst = (QRgb*)dst.scanLine(y);
        QRgb* pixel_src = (QRgb*)src.scanLine(y);
        for(int x=0; x<dst.width(); x++) {
            int r = processChannel(qRed(pixel_src[x]));
            int g = processChannel(qGreen(pixel_src[x]));
            int b = processChannel(qBlue(pixel_src[x]));
            int a = qAlpha(pixel_src[x]);

            pixel_dst[x] = qRgba(r,g,b,a);
        }
    }
}


