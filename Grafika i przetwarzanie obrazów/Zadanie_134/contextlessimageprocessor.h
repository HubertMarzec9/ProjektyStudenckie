#ifndef ContextlessImageProcessor_H
#define ContextlessImageProcessor_H

#include <QImage>
#include <QRgb>
#include <QObject>
#include "abstractimageprocessor.h"

class ContextlessImageProcessor : public AbstractImageProcessor{
    int brightness;

    uchar processBrightness(const uchar &src);
    uchar processChannel(uchar channel);

public:
    void setBrightness(int value);

    void process(const QImage &src, QImage &dst) override;
};


#endif // ContextlessImageProcessor_H
