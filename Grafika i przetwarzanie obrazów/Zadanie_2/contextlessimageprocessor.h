#ifndef ContextlessImageProcessor_H
#define ContextlessImageProcessor_H

#include <QImage>
#include <QRgb>
#include <QObject>


class ContextlessImageProcessor {
    int brightness;

    uchar processBrightness(const uchar &src);
    uchar processChannel(uchar channel);

public:
    void setBrightness(int value);

    void process(const QImage &src, const QImage &dst);
};


#endif // ContextlessImageProcessor_H
