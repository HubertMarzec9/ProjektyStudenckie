#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>

#include "matrix3x3.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    enum Mode {Move, Scale, Rotate, Shear};

private:
    Mode mode;
    QImage srcImage,transImage;
    Matrix3x3 transformation, startPointMatrix, rotateMatrix, mouseMatrix;
    int pointx,pointy;
    double q1, q2, a, b, degrees;
    void updateImage();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public:
    Canvas(QWidget *parent = nullptr);
    void loadImage(QString path);
    void setMode(Mode);
    void resize(const QSize &size);


signals:

};

#endif // CANVAS_H
