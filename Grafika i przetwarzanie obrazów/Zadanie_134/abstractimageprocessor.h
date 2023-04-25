#ifndef ABSTRACTIMAGEPROCESSOR_H
#define ABSTRACTIMAGEPROCESSOR_H

#include <QImage>

class AbstractImageProcessor
{
public:
    virtual void process(const QImage &src, QImage &dst) = 0;

};

#endif // ABSTRACTIMAGEPROCESSOR_H
