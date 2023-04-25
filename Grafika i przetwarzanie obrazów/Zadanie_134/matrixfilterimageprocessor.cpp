#include "matrixfilterimageprocessor.h"
#include <iostream>
#include <iomanip>

void MatrixFilterImageProcessor::setValues(std::unique_ptr<std::vector<float>> &&matrix, int height, int width) {
    this->matrix = std::move(matrix);
    this->matHeight = height;
    this->matWidth = width;
    this->halfMatHeight = height/2;
    this->halfMatWidth = width/2;
    div = std::accumulate(this->matrix->begin(), this->matrix->end(), 0.0f);
}

void MatrixFilterImageProcessor::setGaussian(int kernel) {
    this-> n = kernel/2;
    this->matWidth=this->matHeight=kernel;
    this->halfMatHeight=this->halfMatWidth=kernel/2;
    this->matrix = std::make_unique<std::vector<float>> (kernel);
    for(int x=0;x<kernel;x++)
        (*matrix)[x] = 100.0*exp(-(pow(x-kernel/2,2)+pow(0,2))/((kernel/2.0)*5));
    div = std::accumulate(this->matrix->begin(), this->matrix->end(), 0.0f);
}

void MatrixFilterImageProcessor::setUnsharpMask(int alfa){
    this->alfa = alfa;
}

void MatrixFilterImageProcessor::conv2D_px(const QRgb* pixel_dst,QRgb& pixel_src,const std::unique_ptr<std::vector<float>> &mask,const int* mask_it,const int& mask_sum){
    int r = 0;
    int g = 0;
    int b = 0;
    for(size_t y=0; y<mask->size();y++){
        r += qRed(pixel_dst[mask_it[y]]) * mask->at(y);
        g += qGreen(pixel_dst[mask_it[y]]) * mask->at(y);
        b += qBlue(pixel_dst[mask_it[y]]) * mask->at(y);
    }
    pixel_src=qRgb(std::clamp(r/mask_sum,0,255),std::clamp(g/mask_sum,0,255),std::clamp(b/mask_sum,0,255));
}

void MatrixFilterImageProcessor::conv2D_sep(QImage &border_img, QImage& processedImage,const std::unique_ptr<std::vector<float>> &mask, int n){
    auto mask_sum=0;
    for(auto it=mask->begin();it!=mask->end();it++)
        mask_sum+=*it;
    if(mask_sum==0)mask_sum=1;
    auto* mask_it = new int[mask->size()];
    for(int y=0; y<n*2+1;y++){
        mask_it[y]=y*border_img.width();
    }

    QImage tmp_img = border_img.copy();

    for(int y=0; y<processedImage.height();y++){
        QRgb* pixel_src = (QRgb*)border_img.scanLine(y);
        QRgb* pixel_dst = (QRgb*)tmp_img.scanLine(y+n);
        for(int x=0; x<tmp_img.width();x++)
            conv2D_px(pixel_src+x,pixel_dst[x],mask,mask_it,mask_sum);
    }
    for(int y=0; y<n*2+1;y++){
        mask_it[y]=y;
    }


    for(int y=0; y<processedImage.height();y++){
        QRgb* pixel_src = (QRgb*)tmp_img.scanLine(y+n);
        QRgb* pixel_dst = (QRgb*)processedImage.scanLine(y);
        for(int x=0; x<processedImage.width();x++)
            conv2D_px(pixel_src+x,pixel_dst[x],mask,mask_it,mask_sum);
    }
    delete[]mask_it;
}

void MatrixFilterImageProcessor::border(const QImage& originalImage,QImage& border,int n)
{
    for(int y =0 ;y<originalImage.height();y++)
    {
        memcpy(border.scanLine(y+n)+n*4,originalImage.scanLine(y),originalImage.width()*4);
    }
    for(int y=0 ;y<n;y++){
        memcpy(border.scanLine(n-y-1)+n*4,originalImage.scanLine(y),originalImage.width()*4);
    }
    for(int y=originalImage.height()-1;y>=originalImage.height()-n;y--)
    {
        memcpy(border.scanLine(originalImage.height()*2-y+n-1)+n*4,originalImage.scanLine(y),originalImage.width()*4);
    }
    for(int y=0;y<originalImage.height()+2*n;y++){
        QRgb* pixel_b=(QRgb*)border.scanLine(y);
        QRgb* pixel=pixel_b;
        pixel=pixel+n*2;
        for(int i=0;i<n;i++)
        {
            pixel_b[i]=pixel[-i];
        }
        pixel_b=pixel_b+originalImage.width()+n*2-1;
        pixel=pixel_b-n*2+1;
        for(int i=0;i<n;i++)
        {
            pixel_b[-i]=pixel[i];
        }
    }
}

void MatrixFilterImageProcessor::pictureDiff(const QImage &src, QImage &dst){
    for(int y=0; y<dst.height();y++){
        QRgb* pixel_src = (QRgb*)src.scanLine(y);
        QRgb* pixel_dst = (QRgb*)dst.scanLine(y);
        for(int x=0; x<dst.width();x++)
        {
            pixel_dst[x]=qRgb(std::clamp(qRed(pixel_src[x])-qRed(pixel_dst[x]),0,255),std::clamp(qGreen(pixel_src[x])-qGreen(pixel_dst[x]),0,255),std::clamp(qBlue(pixel_src[x])-qBlue(pixel_dst[x]),0,255));
        }
    }
}

void MatrixFilterImageProcessor::pictureAdd(const QImage & src, QImage &dst,const float &alfa){
    for(int y=0; y<dst.height();y++){
        QRgb* pixel_src = (QRgb*)src.scanLine(y);
        QRgb* pixel_dst = (QRgb*)dst.scanLine(y);
        for(int x=0; x<dst.width();x++)
        {
            pixel_dst[x]=qRgb(std::clamp(qRed(pixel_src[x])+ (int)(alfa * qRed(pixel_dst[x])),0,255),std::clamp(qGreen(pixel_src[x])+ (int)(alfa * qRed(pixel_dst[x])),0,255), std::clamp(qBlue(pixel_src[x])+ (int)(alfa * qRed(pixel_dst[x])),0,255));
        }
    }
}

void MatrixFilterImageProcessor::process(const QImage &src, QImage &dst) {
    border_img = QImage(src.width()+2*n,src.height()+2*n,QImage::Format_ARGB32);
    border(src, border_img,n);
    conv2D_sep(border_img,dst,matrix,n);
    //pictureDiff(src,dst);
    //pictureAdd(src,dst,alfa);
}
