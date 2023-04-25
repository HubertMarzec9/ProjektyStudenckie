#include "contrastimageprocessor.h"

uchar ContrastImageProcessor::processChannel(uchar channel) {
    channel = processContrast(channel);
    return channel;
}

void ContrastImageProcessor::setValue(float value){
    this->value = value;
}

uchar ContrastImageProcessor::processContrast(const uchar &src) {
    if(src * value >= 255)
        return 255;
    else if(src * value <= 0)
        return 0;
    else
        return src * value;
}

void ContrastImageProcessor::process(const QImage &src, const QImage &dst) {
    if(this->value < 0)
    {
        for(int y=0; y<dst.height(); y++) {
            QRgb* pixel_dst = (QRgb*)dst.scanLine(y);
            QRgb* pixel_src = (QRgb*)src.scanLine(y);
            for(int x=0; x<dst.width(); x++) {
                int r = static_cast<unsigned char>(255 - pixel_src[x]);
                int g = static_cast<unsigned char>(255 - pixel_src[x]);
                int b = static_cast<unsigned char>(255 - pixel_src[x]);
                int a = qAlpha(pixel_src[x]);

                pixel_dst[x] = qRgba(r,g,b,a);
            }
        }
    }
    else{
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
}


