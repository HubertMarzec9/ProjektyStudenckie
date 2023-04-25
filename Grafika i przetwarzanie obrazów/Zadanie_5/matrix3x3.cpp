#include "matrix3x3.h"
#include <cstdio>
#include <cstring>
#include <cmath>

Matrix3x3 Matrix3x3::inv() const{
    Matrix3x3 result;
    double determinant = 0;
    for(int i=0;i<3;i++)
        determinant += (arr[0][i]*(arr[1][(i+1)%3]*arr[2][(i+2)%3] - arr[1][(i+2)%3]*arr[2][(i+1)%3]));

    for(int i=0;i<3;i++){
       for(int j=0;j<3;j++)
            result.arr[j][i] = ((arr[(i+1)%3][(j+1)%3] * arr[(i+2)%3][(j+2)%3]) - (arr[(i+1)%3][(j+2)%3]*arr[(i+2)%3][(j+1)%3]))/ determinant;
    }
    return result;
}

Matrix3x3 Matrix3x3::multiply( Matrix3x3 matrix)
{
    Matrix3x3 result;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            result.arr[i][j] = 0;
            for(int k = 0; k < 3; k++)
            {
                result.arr[i][j] += arr[i][k] * matrix.arr[k][j];
            }
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::moveMatrix(float x, float y)
{
    Matrix3x3 matrix;
    matrix.arr[0][2]=x;
    matrix.arr[1][2]=y;
    return matrix;
}
Matrix3x3 Matrix3x3::scaleMatrix(float x, float y)
{
    Matrix3x3 matrix;
    matrix.arr[0][0]=x;
    matrix.arr[1][1]=y;
    return matrix;
}
Matrix3x3 Matrix3x3::rotationMatrix(float angle)
{
    Matrix3x3 matrix;
    matrix.arr[0][0]=cos(angle);
    matrix.arr[1][0]=sin(angle);
    matrix.arr[1][1]=cos(angle);
    matrix.arr[0][1]=-sin(angle);
    return matrix;
}

Matrix3x3 Matrix3x3::shearMatrix(float angleX,float angleY)
{
    Matrix3x3 matrix;
    matrix.arr[0][0]=1;
    matrix.arr[1][0]=angleX;
    matrix.arr[1][1]=1;
    matrix.arr[0][1]=angleY;
    return matrix;
}

Matrix3x3::Matrix3x3()
{
    memset(arr,0,sizeof(arr));
    arr[0][0]=arr[1][1]=arr[2][2]=1.;
}

QPointF Matrix3x3::operator*(const QPointF &point) const
{
    return QPointF(point.x()*arr[0][0]+point.y()*arr[0][1]+1.*arr[0][2],point.x()*arr[1][0]+point.y()*arr[1][1]+1.*arr[1][2]);
}
