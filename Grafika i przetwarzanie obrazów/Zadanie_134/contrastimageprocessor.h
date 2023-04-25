#ifndef ContrastImageProcessor_H
#define ContrastImageProcessor_H

#include <QImage>
#include <QRgb>
#include <QObject>

#include <functional>

class ContrastImageProcessor {
    float value;

    uchar processContrast(const uchar &src);
    uchar processChannel(uchar channel);

public:
    void setValue(float value);

    void process(const QImage &src, const QImage &dst);
};


#endif // ContrastImageProcessor_H
