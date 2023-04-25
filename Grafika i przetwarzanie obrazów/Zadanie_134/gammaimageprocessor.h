#ifndef GammaImageProcessor_H
#define GammaImageProcessor_H

#include <QImage>
#include <QRgb>
#include <QObject>

#include <functional>

class GammaImageProcessor {
    float value;

    uchar processGamma(const uchar &src);
    uchar processChannel(uchar channel);

public:
    void setValue(float value);

    void process(const QImage &src, const QImage &dst);
};


#endif // GammaImageProcessor_H
