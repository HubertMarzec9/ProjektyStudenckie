#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <QPointF>

class Matrix3x3
{





public:
    double arr[3][3];
    Matrix3x3 inv() const;
    Matrix3x3 multiply(Matrix3x3 matrix);
    static Matrix3x3 moveMatrix(float x,float y);
    static Matrix3x3 scaleMatrix(float x,float y);
    static Matrix3x3 rotationMatrix(float angle);
    static Matrix3x3 shearMatrix(float angleX,float angleY);
    Matrix3x3();
    QPointF operator*( const QPointF & point) const;

};

#endif // MATRIX3X3_H
