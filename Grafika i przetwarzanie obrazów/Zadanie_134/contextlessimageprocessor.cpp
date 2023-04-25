#include "contextlessimageprocessor.h"

uchar ContextlessImageProcessor::processChannel(uchar channel) {
    channel = processBrightness(channel);
    return channel;
}

void ContextlessImageProcessor::setBrightness(int value){
    this->brightness = value;
}

uchar ContextlessImageProcessor::processBrightness(const uchar &src) {
    return std::clamp(src+brightness, 0, 255);
}

void ContextlessImageProcessor::process(const QImage &src, QImage &dst) {
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


