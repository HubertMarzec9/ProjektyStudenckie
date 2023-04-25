#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <QDebug>
#include <iostream>

Canvas::Canvas(QWidget *parent) : QWidget{parent} {

}

void Canvas::resize(const QSize &size) {
    transImage = QImage(size,QImage::Format_ARGB32);
    this->QWidget::resize(size);
}

void Canvas::updateImage()
{
    transImage.fill(0x00000000);
    for(int y=0;y<transImage.height();y++)
    {
        QRgb *transLine=reinterpret_cast<QRgb *> (transImage.scanLine(y));
        for(int x=0;x<transImage.width();x++)
        {
            // Oblicz odpowiadający piksel w obrazie źródłowym
            QPointF point=transformation*QPointF(x,y);
            if(point.x()>=0&&point.x()<srcImage.width()-1&&point.y()>=0&&point.y()<srcImage.height()-1)
            {
                // Oblicz współrzędne interpolacji
                float c=point.x()-floor(point.x()), d=ceil(point.x())-point.x();
                float a=point.y()-floor(point.y()), b=ceil(point.y())-point.y();

                // Pobierz kolory otaczających pikseli
                QRgb points[4] = {
                    srcImage.pixel(floor(point.x()),floor(point.y())),
                    srcImage.pixel(ceil(point.x()),floor(point.y())),
                    srcImage.pixel(floor(point.x()),ceil(point.y())),
                    srcImage.pixel(ceil(point.x()),ceil(point.y()))
                };

                // Sprawdź czy piksel jest na brzegu
                if(a==0&&c==0)
                {
                    transLine[x]=points[0];
                    continue;
                }
                if(a==0&&d==0)
                {
                    transLine[x]=points[1];
                    continue;
                }
                if(b==0&&c==0)
                {
                    transLine[x]=points[2];
                    continue;
                }
                if(b==0&&d==0)
                {
                    transLine[x]=points[3];
                    continue;
                }

                // Oblicz kolor piksela
                QRgb P02 = qRgba(
                            (int)(b*qRed(points[0])+a*qRed(points[2])),
                            (int)(b*qGreen(points[0])+a*qGreen(points[2])),
                            (int)(b*qBlue(points[0])+a*qBlue(points[2])),
                            (int)(b*qAlpha(points[0])+a*qAlpha(points[2]))
                            );
                QRgb P13 = qRgba(
                            (int)(b*qRed(points[1])+a*qRed(points[3])),
                            (int)(b*qGreen(points[1])+a*qGreen(points[3])),
                            (int)(b*qBlue(points[1])+a*qBlue(points[3])),
                            (int)(b*qAlpha(points[1])+a*qAlpha(points[3]))
                        );
                if(a==0)
                {
                    QRgb P01=qRgba(
                            (int)(c*qRed(points[1])+d*qRed(points[0])),
                            (int)(c*qGreen(points[1])+d*qGreen(points[0])),
                            (int)(c*qBlue(points[1])+d*qBlue(points[0])),
                            (int)(c*qAlpha(points[1])+d*qAlpha(points[0]))
                            );
                    transLine[x]=P01;
                    continue;
                }
                if(b==0)
                {
                    QRgb P23=qRgba(
                            (int)(c*qRed(points[3])+d*qRed(points[2])),
                            (int)(c*qGreen(points[3])+d*qGreen(points[2])),
                            (int)(c*qBlue(points[3])+d*qBlue(points[2])),
                            (int)(c*qAlpha(points[3])+d*qAlpha(points[2]))
                            );
                    transLine[x]=P23;
                    continue;
                }
                if(c==0)
                {
                    transLine[x]=P02;
                    continue;
                }
                if(d==0)
                {
                    transLine[x]=P13;
                    continue;
                }
                QRgb result=qRgba(
                            (int)(c*qRed(P13)+d*qRed(P02)),
                            (int)(c*qGreen(P13)+d*qGreen(P02)),
                            (int)(c*qBlue(P13)+d*qBlue(P02)),
                            (int)(c*qAlpha(P13)+d*qAlpha(P02))
                            );
                transLine[x]=result;
            }
        }
    }
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),0xFFFFFF);
    painter.drawImage(0,0,transImage);
}

void Canvas::loadImage(QString path)
{
    srcImage.load(path);
    this->update();
}


void Canvas::mousePressEvent(QMouseEvent *event)
{
    pointx=event->pos().x();
    pointy=event->pos().y();
    rotateMatrix.arr[0][2]=pointx+ startPointMatrix.arr[0][2];
    rotateMatrix.arr[1][2]=pointy+ startPointMatrix.arr[1][2];
    mouseMatrix.arr[0][2]=-pointx;
    mouseMatrix.arr[1][2]=-pointy;

}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    switch (mode) {
    case Move:
        startPointMatrix.arr[0][2]=-event->pos().x();
        startPointMatrix.arr[1][2]=-event->pos().y();
        transformation=Matrix3x3::moveMatrix(event->pos().x(),event->pos().y());
        transformation=transformation.inv();
        break;
    case Scale:
        transformation=Matrix3x3::scaleMatrix((float)event->pos().x()/srcImage.width(),(float)event->pos().y()/srcImage.height());
        transformation=transformation.inv();
        break;
    case Rotate:
        a=(double)(-event->pos().y()+pointy)/(double)(-event->pos().x()+pointx);
        b=(double)(pointy)-a*(double)(pointx);
        q1=(event->pos().y()-pointy);
        q2=(event->pos().x()-pointx);

        degrees = qRadiansToDegrees( atan(a));
        if (pointx == event->pos().x()||pointy == event->pos().y())
            degrees = 0;
        else if (pointx > event->pos().x()&&pointy < event->pos().y())
            degrees = -1 * degrees + 180;
        else if (pointx < event->pos().x()&&pointy < event->pos().y())
            degrees = 270 + 90 - degrees;
        else if (pointx < event->pos().x()&&pointy > event->pos().y())
            degrees = -1 * degrees ;
        else if (pointx > event->pos().x()&&pointy >  event->pos().y())
            degrees = 90 + 90 - degrees;

        transformation=Matrix3x3::rotationMatrix(qDegreesToRadians(degrees));
        transformation.arr[0][2]=rotateMatrix.arr[0][2];
        transformation.arr[1][2]=rotateMatrix.arr[1][2];

        transformation=transformation.multiply(mouseMatrix);

        updateImage();

        break;
    case Shear:
        transformation=Matrix3x3::shearMatrix(abs((float)event->pos().x()-pointx)/srcImage.width(),
                                              abs((float)event->pos().y()-pointy)/srcImage.height());
        transformation=transformation.multiply(startPointMatrix);
        break;
    default:
        break;
    }

    updateImage();
    this->update();
}


void Canvas::mouseReleaseEvent(QMouseEvent *event) {

}

void Canvas::setMode(Mode mode) {
    this->mode = mode;
}


