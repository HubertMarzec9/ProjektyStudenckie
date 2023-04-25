#ifndef COLORSPACEIMAGEPROCESSOR_H
#define COLORSPACEIMAGEPROCESSOR_H

#include <QImage>
#include <QColor>
#include <functional>
#include <cmath>

class ColorspaceImageProcessor
{
    static QRgb rgbToHsl(QRgb);
    static QRgb hslToRgb(QRgb);
    static QRgb clabToRgb(QRgb);
    static QRgb rgbToClab(QRgb);
    QRgb processOffset(QRgb);
    QRgb processOfflab(QRgb val);
    int offset[3];
    int flaga = 0;
    std::function<QRgb(QRgb)> fromRGB, toRGB;

public:
    void setOffset(int c0, int c1, int c2);
    void process(const QImage &src, QImage &dst);
    static double clabFunction(double a);
    static double f_inverse(double t);
    static double funkcjaHelp(double k);
    static double hueToRgb(double p, double q, double t);
    void setRgbMode();
    void setHslMode();
    void setClabMode();
};

#endif // COLORSPACEIMAGEPROCESSOR_H
